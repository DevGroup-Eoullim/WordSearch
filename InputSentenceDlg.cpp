// InputSentenceDlg.cpp: 구현 파일
//

#include "pch.h"
#include "WordSearch.h"
#include "afxdialogex.h"
#include "InputSentenceDlg.h"


// InputSentenceDlg 대화 상자

IMPLEMENT_DYNAMIC(InputSentenceDlg, CDialogEx)

InputSentenceDlg::InputSentenceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT_SENTENCE, pParent)
{

}

InputSentenceDlg::~InputSentenceDlg()
{
}

void InputSentenceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUT_DLG_SENTENCE, edSentence);
}


BEGIN_MESSAGE_MAP(InputSentenceDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &InputSentenceDlg::OnBnClickedOk)
	ON_COMMAND(IDNO, &InputSentenceDlg::OnIdno)
	ON_EN_CHANGE(IDC_INPUT_DLG_SENTENCE,&InputSentenceDlg::OnEnChange)
END_MESSAGE_MAP()


// InputSentenceDlg 메시지 처리기


void InputSentenceDlg::OnBnClickedOk()
{
	edSentence.GetWindowTextW(sentence);
	//품사 검출 시작
	// 검출 결과 읽어오기
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void InputSentenceDlg::OnIdno()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//DestroyWindow();
	OnCancel();
}
void InputSentenceDlg::OnEnChange()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//DestroyWindow();
	printf("change\n");
	edSentence.HideSelection(true, false);
	edSentence.SetSel((long)0, edSentence.GetTextLength());
	edSentence.SetWordCharFormat(charStyle);
	edSentence.SetSel(-1, -1);
	edSentence.HideSelection(false, false);
}


BOOL InputSentenceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	
	ZeroMemory(&charStyle, sizeof(CHARFORMAT2));
	charStyle.cbSize = sizeof(CHARFORMAT2);
	charStyle.dwMask = CFM_SIZE | CFM_FACE | CFM_WEIGHT;
	wcscpy(charStyle.szFaceName, L"Cambria");
	charStyle.yHeight = 19 * 15; //19폰트?
	charStyle.wWeight = FW_MEDIUM;
	//charStyle.bCharSet = HANGEUL_CHARSET;

	edSentence.SetDefaultCharFormat(charStyle);

	edSentence.SetEventMask(edSentence.GetEventMask() | ENM_CHANGE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

CString InputSentenceDlg::getSentence() {
	return sentence;
}

void InputSentenceDlg::OnOK()
{
	// Do nothing to prevent the dialog from closing
}


BOOL InputSentenceDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//if (pMsg->message == WM_KEYDOWN)
	//{
	//	if (pMsg->wParam == VK_RETURN)
	//	{
	//		return TRUE; // Do not process further, prevents closing
	//	}
	//}
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL InputSentenceDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	/*switch (LOWORD(wParam)) {
	case IDC_INPUT_DLG_SENTENCE:
		switch (HIWORD(wParam)) {
		case EN_CHANGE:
			edSentence.SetSel((long)0, edSentence.GetTextLength());
			edSentence.SetWordCharFormat(charStyle);
			break;
		}
		break;
	}*/
	return CDialogEx::OnCommand(wParam, lParam);
}

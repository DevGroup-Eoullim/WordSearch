// InputBtPlatform.cpp: 구현 파일
//

#include "pch.h"
#include "WordSearch.h"
#include "afxdialogex.h"
#include "InputBtPlatform.h"
#include "InputSentenceDlg.h"


// InputBtPlatform 대화 상자

IMPLEMENT_DYNAMIC(InputBtPlatform, EditContainer)

InputBtPlatform::InputBtPlatform(CWnd* pParent /*=nullptr*/)
	: EditContainer(IDD_INPUTBTPLATFORM,TextStyle::style.pNowPointColor, pParent)
{
	bg = TextStyle::style.pNowPointColor;
}

InputBtPlatform::~InputBtPlatform()
{
}

void InputBtPlatform::DoDataExchange(CDataExchange* pDX)
{
	EditContainer::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, ctrl);
}


BEGIN_MESSAGE_MAP(InputBtPlatform, EditContainer)
	ON_WM_PAINT()
	ON_WM_SIZE()
//	ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BUTTON1, &InputBtPlatform::OnBnClickedButton1)
END_MESSAGE_MAP()


// InputBtPlatform 메시지 처리기


void InputBtPlatform::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 EditContainer::OnPaint()을(를) 호출하지 마십시오.
	Draw(&dc);
}


void InputBtPlatform::OnSize(UINT nType, int cx, int cy)
{
	EditContainer::OnSize(nType, cx, cy);
	Invalidate();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


BOOL InputBtPlatform::OnInitDialog()
{
	EditContainer::OnInitDialog();
	setPCtrl(&ctrl);

	ctrl.EnableWindowsTheming(FALSE);
	ctrl.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	ctrl.SetFaceColor(*bg);
	ctrl.SetTextColor(*txt);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


//HBRUSH InputBtPlatform::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = EditContainer::OnCtlColor(pDC, pWnd, nCtlColor);
//	if (nCtlColor == CTLCOLOR_BTN) {
//		pDC->SetBkColor(*bg);
//		static CBrush brush(*bg);
//		return (HBRUSH)brush;
//	}
	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
//	return hbr;
//}


void InputBtPlatform::OnBnClickedButton1()
{
	InputSentenceDlg dlg;
	int result = dlg.DoModal();
	if (result == IDOK) {
		CWnd* parent = GetParent();
		CString* str = new CString(dlg.getSentence());
		parent->SendMessage(WM_COMMAND, OPEN_INPUT_DLG, (LPARAM)str);
		/*edSentence.SetWindowTextW(dlg.getSentence());*/
		//CString str = dlg.getSentence();
		/*int textId = cp.ExtractPart(dlg.getSentence());
		if (textId != -1) {
			printf("success\n");
		}
		else {
			printf("fail\n");
		}
		edSentence->setTextId(textId);
		edSentence->setText(dlg.getSentence());*/
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

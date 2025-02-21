// WordPlatform.cpp: 구현 파일
//

#include "pch.h"
#include "WordSearch.h"
#include "afxdialogex.h"
#include "WordsPlatform.h"


// WordPlatform 대화 상자

IMPLEMENT_DYNAMIC(WordsPlatform, EditContainer)

WordsPlatform::WordsPlatform(CWnd* pParent /*=nullptr*/)
	: EditContainer(IDD_WORDSPLATFORM, TextStyle::style.pNowBorder2Color, pParent)
{

}

WordsPlatform::~WordsPlatform()
{
}

void WordsPlatform::DoDataExchange(CDataExchange* pDX)
{
	EditContainer::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ctrl);
}


BEGIN_MESSAGE_MAP(WordsPlatform, EditContainer)
	ON_WM_PAINT()
	ON_WM_SIZE()
//	ON_LBN_SELCHANGE(IDC_LIST1, &WordsPlatform::OnLbnSelchangeList)
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
	ON_LBN_SELCHANGE(IDC_LIST1, &WordsPlatform::OnSelchangeList)
END_MESSAGE_MAP()


// WordPlatform 메시지 처리기


void WordsPlatform::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	Draw(&dc);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 EditContainer::OnPaint()을(를) 호출하지 마십시오.
}


void WordsPlatform::OnSize(UINT nType, int cx, int cy)
{
	EditContainer::OnSize(nType, cx, cy);
	Invalidate();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


BOOL WordsPlatform::OnInitDialog()
{
	EditContainer::OnInitDialog();
	//ctrl.SetBackgroundColor(0, *bg);
	setPCtrl(&ctrl);
	ctrl.SetItemHeight(0, 30);
	
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


//void WordsPlatform::OnLbnSelchangeList()
//{
//	if (ctrl.GetCount() > 0) {
//		printf("sel\n");
		//printf("%d\n", ctrl.GetCurSel());
//		int sel = ctrl.GetCurSel();
//		if (sel == LB_ERR) {
//			return;
//		}
//		CString* word = new CString;
//		ctrl.GetText(ctrl.GetCurSel(), *word);
//		CWnd* parent = this->GetParent();
//		parent->SendMessage(WM_COMMAND, LIST_SEL_CHANGE, (LPARAM)word);
//	}
//	else {
		// 리스트 박스가 비어있는 경우의 처리
//		printf("list empty\n");
//	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}


HBRUSH WordsPlatform::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = EditContainer::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_LISTBOX)
	{
		if (pWnd->GetDlgCtrlID() == IDC_LIST1)
		{
			pDC->SetBkColor(*TextStyle::style.pNowBGColor); // 노란색 배경
			pDC->SetTextColor(*TextStyle::style.pNowTextColor);
			
			static CBrush brush(*TextStyle::style.pNowBGColor);
			return (HBRUSH)brush;
		}
	}
	return hbr;
}


void WordsPlatform::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDCtl == IDC_LIST1)
	{
		CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
		COLORREF crText, crBkgnd;
		crText = *txt;  // 흰색 텍스트
		if (lpDrawItemStruct->itemState & ODS_SELECTED)
		{
			crBkgnd = *TextStyle::style.pNowPointColor;  // 노란색 배경
		}
		else
		{
			crBkgnd = *bg;  // 흰색 배경
		}
		printf("bg: %x\n", crBkgnd);
		pDC->SetTextColor(crText);
		pDC->SetBkColor(crBkgnd);
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem, crBkgnd);

		CString strText;
		CListBox* lb = (CListBox*)GetDlgItem(nIDCtl);
		if (lb->GetCount() > 0) {
			lb->GetText(lpDrawItemStruct->itemID, strText);
			pDC->DrawTextW(strText, &lpDrawItemStruct->rcItem, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		}
	}
	else {
		EditContainer::OnDrawItem(nIDCtl, lpDrawItemStruct);
	}
}


void WordsPlatform::OnSelchangeList()
{
	if (ctrl.GetCount() > 0) {
		printf("sel\n");
		printf("%d\n", ctrl.GetCurSel());
		int sel = ctrl.GetCurSel();
		if (sel == LB_ERR) {
			return;
		}
		CString* word = new CString;
		ctrl.GetText(ctrl.GetCurSel(), *word);
		CWnd* parent = this->GetParent();
		parent->SendMessage(WM_COMMAND, LIST_SEL_CHANGE, (LPARAM)word);
	}
	else {
		printf("list empty\n");
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

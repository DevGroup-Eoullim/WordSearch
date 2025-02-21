// EditContainer.cpp: 구현 파일
//

#include "pch.h"
#include "WordSearch.h"
#include "afxdialogex.h"
#include "EditContainer.h"


// EditContainer 대화 상자

IMPLEMENT_DYNAMIC(EditContainer, CDialogEx)

EditContainer::EditContainer(UINT id, COLORREF* borderColor, CWnd* pParent /*=nullptr*/)
	: CDialogEx(id, pParent)
{
	arc = 10;
	border = borderColor;
	printf("%x\n", *border);
}

EditContainer::~EditContainer()
{
}

void EditContainer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EditContainer, CDialogEx)
END_MESSAGE_MAP()


// EditContainer 메시지 처리기


BOOL EditContainer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRgn rgn;

	GetClientRect(rect);
	rgn.CreateRoundRectRgn(rect.left, rect.top, rect.right, rect.bottom, arc, arc);

	::SetWindowRgn(this->m_hWnd, (HRGN)rgn, TRUE);
	
	return TRUE;
}

void EditContainer::Draw(CPaintDC* dc)
{
	CRgn rgn;
	CBrush bgBrush(*bg);

	dc->FillSolidRect(&rect, *border);

	rgn.CreateRoundRectRgn(rect.left+ padding, rect.top+ padding, rect.right- (padding), rect.bottom- (padding), arc, arc);
	dc->FillRgn(&rgn, &bgBrush);

	bgBrush.DeleteObject();
}
void EditContainer::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	GetClientRect(&rect);
	CRgn rgn;

	//GetClientRect(rect);
	//printf("%d %d %d %d\n", rect.left, rect.top, rect.right, rect.bottom);
	rgn.CreateRoundRectRgn(rect.left, rect.top, rect.right, rect.bottom, arc, arc);

	::SetWindowRgn(this->m_hWnd, (HRGN)rgn, TRUE);

	if (pCtrl) {
		int ctrlPadding = 6;
		pCtrl->MoveWindow(rect.left + ctrlPadding,
			rect.top + ctrlPadding,
			rect.Width() - (ctrlPadding * 2),
			rect.Height() - (ctrlPadding * 2));
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
void EditContainer::setPCtrl(CWnd* pCtrl) {
	this->pCtrl = pCtrl;
}

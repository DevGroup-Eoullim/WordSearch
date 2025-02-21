// TranslatePlatform.cpp: 구현 파일
//

#include "pch.h"
#include "WordSearch.h"
#include "afxdialogex.h"
#include "TranslatePlatform.h"


// TranslatePlatform 대화 상자

IMPLEMENT_DYNAMIC(TranslatePlatform, EditContainer)

TranslatePlatform::TranslatePlatform(CWnd* pParent /*=nullptr*/)
	: EditContainer(IDD_TRANSLATEPLATFORM, TextStyle::style.pNowBorder2Color, pParent)
{

}

TranslatePlatform::~TranslatePlatform()
{
}

void TranslatePlatform::DoDataExchange(CDataExchange* pDX)
{
	EditContainer::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, ctrl);
}


BEGIN_MESSAGE_MAP(TranslatePlatform, EditContainer)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// TranslatePlatform 메시지 처리기


void TranslatePlatform::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 EditContainer::OnPaint()을(를) 호출하지 마십시오.
	Draw(&dc);
}


void TranslatePlatform::OnSize(UINT nType, int cx, int cy)
{
	EditContainer::OnSize(nType, cx, cy);
	Invalidate();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


BOOL TranslatePlatform::OnInitDialog()
{
	EditContainer::OnInitDialog();
	ctrl.SetBackgroundColor(0, *bg);
	ctrl.HideCaret();
	setPCtrl(&ctrl);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

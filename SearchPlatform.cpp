// SearchPlatform.cpp: 구현 파일
//

#include "pch.h"
#include "WordSearch.h"
#include "afxdialogex.h"
#include "SearchPlatform.h"


// SearchPlatform 대화 상자

IMPLEMENT_DYNAMIC(SearchPlatform, EditContainer)

SearchPlatform::SearchPlatform(CWnd* pParent /*=nullptr*/)
	: EditContainer(IDD_SEARCHPLATFORM, TextStyle::style.pNowBorder1Color,  pParent)
{
}

SearchPlatform::~SearchPlatform()
{
}

void SearchPlatform::DoDataExchange(CDataExchange* pDX)
{
	EditContainer::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, edit);
}


BEGIN_MESSAGE_MAP(SearchPlatform, EditContainer)
//	ON_WM_PAINT()
ON_WM_PAINT()
ON_WM_SIZE()
END_MESSAGE_MAP()


// SearchPlatform 메시지 처리기


BOOL SearchPlatform::OnInitDialog()
{
	EditContainer::OnInitDialog();

	edit.Init(this->GetParent());
	edit.SetBackgroundColor(0,*bg);
	edit.HideCaret();
	setPCtrl(&edit);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//Invalidate();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


//void SearchPlatform::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 EditContainer::OnPaint()을(를) 호출하지 마십시오.
//}


void SearchPlatform::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 EditContainer::OnPaint()을(를) 호출하지 마십시오.
	printf("paint\n");
	Draw(&dc);
}


void SearchPlatform::OnSize(UINT nType, int cx, int cy)
{
	printf("move\n");
	EditContainer::OnSize(nType, cx, cy);
	//GetClientRect(&rect);
	//printf("%d %d %d %d\n", rect.left, rect.top, rect.right, rect.bottom);
	
	Invalidate();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

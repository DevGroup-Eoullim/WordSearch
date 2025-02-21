
// WordSearchDlg.cpp: 구현 파일
//

#include "framework.h"
#include "WordSearch.h"
#include "WordSearchDlg.h"
#include "afxdialogex.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "InputSentenceDlg.h"
#include "TextLoader.h"



// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWordSearchDlg 대화 상자



CWordSearchDlg::CWordSearchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WORDSEARCH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	globalDict.Load();
	
	
}

void CWordSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT_SENTENCE, edSentence);
	//DDX_Control(pDX, IDC_EDIT_DEFINITION, edDefinition);
	//  DDX_Control(pDX, IDC_LIST_WORDS, liWords);
	//  DDX_Control(pDX, IDC_LIST_WORDS, liWords);
	//DDX_Control(pDX, IDC_LIST_WORDS, liWords);
	//DDX_Control(pDX, IDC_EDIT_TRANSLATE, edTranslate);
	//DDX_Control(pDX, IDC_BT_OPEN_INPUT, btOpenInput);
}

BEGIN_MESSAGE_MAP(CWordSearchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_LBN_SELCHANGE(IDC_LIST_WORDS, &CWordSearchDlg::OnLbnSelchangeListWords)
	//ON_MESSAGE(SM_DONE, &CWordSearchDlg::OnMessage)
	//ON_WM_SETCURSOR()
	//ON_WM_SETFOCUS()
//	ON_BN_CLICKED(IDC_BT_OPEN_INPUT, &CWordSearchDlg::OnClickedBtOpenInput)
	//ON_COMMAND(IDD_WORDSEARCH_DIALOG, &CWordSearchDlg::OnIddWordsearchDialog)
	//ON_WM_MOUSEHOVER()
//	ON_WM_KEYUP()
ON_WM_SIZE()
ON_BN_CLICKED(IDC_BUTTON1, &CWordSearchDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CWordSearchDlg 메시지 처리기

BOOL CWordSearchDlg::OnInitDialog()
{
	printf("init\n");
	CDialogEx::OnInitDialog();

	
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	/*edSentence.Init(this,&searcher);
	edSentence.HideCaret();*/

	//SetItemsStyle();

	//searchPlatform->MoveWindow(10, 10, 500, 500);
	searchPlatform = new SearchPlatform;
	searchPlatform->Create(IDD_SEARCHPLATFORM, this);
	searchPlatform->ShowWindow(SW_SHOW);

	translatePlatform = new TranslatePlatform;
	translatePlatform->Create(IDD_TRANSLATEPLATFORM, this);
	translatePlatform->ShowWindow(SW_SHOW);

	dictPlatform = new DictPlatform;
	dictPlatform->Create(IDD_DICTPLATFORM, this);
	dictPlatform->ShowWindow(SW_SHOW);

	wordsPlatform = new WordsPlatform;
	wordsPlatform->Create(IDD_WORDSPLATFORM, this);
	wordsPlatform->ShowWindow(SW_SHOW);

	inputBtPlatform = new InputBtPlatform;
	inputBtPlatform->Create(IDD_INPUTBTPLATFORM, this);
	inputBtPlatform->ShowWindow(SW_SHOW);

	SendMessage(WM_SIZE, 0, 0);

	SetBackgroundColor(*TextStyle::style.pNowBGColor);

	edSentence = &searchPlatform->edit;
	edTranslate = &translatePlatform->ctrl;
	edDefinition = &dictPlatform->ctrl;
	liWords = &wordsPlatform->ctrl;
	btOpenInput = &inputBtPlatform->ctrl;


	CHARFORMAT2 style = TextStyle::style.getDefaultStyle();
	edSentence->SetDefaultCharFormat(style);
	edTranslate->SetDefaultCharFormat(style);
	edDefinition->SetDefaultCharFormat(style);
	liWords->SetFont(TextStyle::style.getMedium19());
	btOpenInput->SetFont(TextStyle::style.getBold19());
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CWordSearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CWordSearchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CWordSearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CWordSearchDlg::OnOK() {
	DestroyWindow();
}
void CWordSearchDlg::OnCancel() {
	DestroyWindow();
}

//void CWordSearchDlg::OnLbnSelchangeListWords()
//{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//printf("%d\n",liWords->GetCurSel());
	//CString* word;
	////liWords->GetText(liWords->GetCurSel(), word);

	//edDefinition->SetWindowText(L"");
	//edDefinition->SetWindowText(dictionary.GetDictionaryString(word));
	//edDefinition->LineScroll(0, 0);
	//edDefinition->SendMessage(WM_VSCROLL, SB_TOP, 0);
	//wprintf(L"%s\n", word);
//}

Dictionary* CWordSearchDlg::getDictionary() {
	return &dictionary;
}



void CWordSearchDlg::SetItemsStyle() {
	//font.CreatePointFont(8 * 15, L"Courier New");

	//liWords->SetFont(&font);

	//edDefinition->SetBackgroundColor(false, RGB(240, 240, 240));
	//edDefinition->InitStyle();

	//edSentence.InitStyle();
}



//BOOL CWordSearchDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
//{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

//	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
//}


//void CWordSearchDlg::OnSetFocus(CWnd* pOldWnd)
//{
//	CDialogEx::OnSetFocus(pOldWnd);
//
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//}


//void CWordSearchDlg::OnClickedBtOpenInput()
//{
//	InputSentenceDlg dlg;
//	int result = dlg.DoModal();
//	if (result == IDOK) {
//		/*edSentence.SetWindowTextW(dlg.getSentence());*/
		//CString str = dlg.getSentence();
//		int textId = cp.ExtractPart(dlg.getSentence());
//		if (textId!=-1) {
//			printf("success\n");
//		}
//		else {
//			printf("fail\n");
//		}
//		edSentence->setTextId(textId);
//		edSentence->setText(dlg.getSentence());
//	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}


//void CWordSearchDlg::OnIddWordsearchDialog()
//{
//	
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//}


BOOL CWordSearchDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	switch (wParam) {
	case SM_DONE: {
		DictionaryData* dictData = (DictionaryData*)lParam;
		//dictData->Save();
		dictionary.Append(dictData);
		
		edDefinition->SetWindowText(L"");
		edDefinition->SetWindowText(dictData->GetDictionaryString());

		/*edDefinition->ReStyle();
		edDefinition->SetSel(0, 0);*/
		/*edDefinition->LineScroll(0, 0);
		edDefinition->SendMessage(WM_VSCROLL, SB_TOP, 0);*/
		liWords->AddString(dictData->getWord());
		//LBN_SELCHANGE
		return 1;
	}
	case SM_ERROR:{
		CString msg;
		msg.Format(L"\"%s\"를 검색할 수 없습니다.", (LPCWSTR)lParam);
		edDefinition->SetWindowText(msg);
		//edDefinition->ReStyle();
		return 1;
	}
	case SM_TRANSLATE: {
		CString* str = (CString*)lParam;
		CString result;
		cp.Translate(*str, result);
		delete str;
		//wprintf(L"%s\n", result);
		edTranslate->SetWindowTextW(result);
		//AfxMessageBox(result);
		return 1;
	}
	case LIST_SEL_CHANGE: {
		CString* word=(CString*)lParam;
		//liWords->GetText(liWords->GetCurSel(), word);
		edDefinition->SetWindowText(L"");
		edDefinition->SetWindowText(dictionary.GetDictionaryString(*word));
		edDefinition->LineScroll(0, 0);
		edDefinition->SendMessage(WM_VSCROLL, SB_TOP, 0);
		delete word;
		return 1;
	}
	case OPEN_INPUT_DLG: {
		CString* str = (CString*)lParam;
		int textId = cp.ExtractPart(*str);
		if (textId != -1) {
			printf("success\n");
		}
		else {
			printf("fail\n");
		}
		edSentence->setTextId(textId);
		edSentence->setText(*str);
		delete str;
		return 1;
	}
	}
	return CDialogEx::OnCommand(wParam, lParam);
}

//afx_msg LRESULT CWordSearchDlg::OnMessage(WPARAM wParam, LPARAM lParam) {
//	DictionaryData* dictData = (DictionaryData*)wParam;
//	dictionary.Append(dictData);
//
//	edDefinition->SetWindowText(dictData->GetDictionaryString());
//	edDefinition->ReStyle();
//	liWords->AddString(dictData->getWord());
//	//liWords->InsertItem(0, dictData->getWord());
//	//printf("%d\n",liWords->InsertColumn(0, utf8Word.GetString()));
//
//	return false;
//}


//void CWordSearchDlg::OnMouseHover(UINT nFlags, CPoint point)
//{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

//	CDialogEx::OnMouseHover(nFlags, point);
//}



//void CWordSearchDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

//	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
//}


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CWordSearchDlg::OnSize(UINT nType, int cx, int cy)
{
	//printf("size\n");
	CDialogEx::OnSize(nType, cx, cy);
	CRect clRect;
	GetClientRect(&clRect);
	int wPadding = 70;
	int hPadding = 50;
	int margin = 20;

	POINT inputButtonSize = { 150,40 }; //w,h
	/*POINT inputButtonOrigin = {
		clRect.left + padding,
		clRect.top + padding,
	};*/
	CRect inputBtPlatformRect(
		clRect.left + wPadding,
		clRect.top + hPadding,
		clRect.left + wPadding + inputButtonSize.x,
		clRect.top + hPadding + inputButtonSize.y
	);

	POINT translatePlatformSize = {
		//clRect.right - wPadding - margin - searchPlatformRect.right,
		700,
		150
	};

	POINT searchPlatformSize = {
		//(clRect.right - (wPadding * 2)) / 30*11,
		(clRect.right - (wPadding * 2))- translatePlatformSize.x,
		clRect.bottom - (hPadding * 2) - inputButtonSize.y - margin
	};
	/*POINT searchPlatformOrigin = {
		inputButtonOrigin.x,
		inputButtonOrigin.y + margin,
	};*/
	CRect searchPlatformRect(
		inputBtPlatformRect.left,
		inputBtPlatformRect.bottom + margin,
		inputBtPlatformRect.left + searchPlatformSize.x,
		inputBtPlatformRect.bottom + margin + searchPlatformSize.y
	);

	
	//printf("translatePlatformSize: %d\n", translatePlatformSize.x);
	/*POINT translatePlatformSize = {
		clRect.right - wPadding - margin - searchPlatformRect.right,
		150
	};*/
	CRect translatePlatformRect(
		searchPlatformRect.right + margin,
		searchPlatformRect.top,
		searchPlatformRect.right + margin + translatePlatformSize.x,
		searchPlatformRect.top + translatePlatformSize.y
	);

	POINT wordsPlatformSize = {
		150,
		clRect.bottom - margin - translatePlatformRect.bottom - hPadding
	};

	POINT dictPlatformSize = {
		//clRect.right - wPadding - wordsPlatformSize.x - margin - margin - searchPlatformRect.right,
		translatePlatformSize.x - margin - wordsPlatformSize.x,
		clRect.bottom - hPadding - margin - translatePlatformRect.bottom
	};
	CRect dictPlatformRect(
		searchPlatformRect.right + margin,
		translatePlatformRect.bottom + margin,
		searchPlatformRect.right + margin + dictPlatformSize.x,
		translatePlatformRect.bottom + margin + dictPlatformSize.y
	);

	CRect wordsPlatformRect(
		dictPlatformRect.right + margin,
		dictPlatformRect.top,
		dictPlatformRect.right + margin + wordsPlatformSize.x,
		dictPlatformRect.top + wordsPlatformSize.y
	);

	if (inputBtPlatform) {
		if (inputBtPlatform->m_hWnd) {
			inputBtPlatform->MoveWindow(&inputBtPlatformRect);
		}
	}
	if (searchPlatform) {
		if (searchPlatform->m_hWnd) {
			searchPlatform->MoveWindow(&searchPlatformRect);
		}
	}
	if (translatePlatform) {
		if (translatePlatform->m_hWnd) {
			translatePlatform->MoveWindow(&translatePlatformRect);
		}
	}
	
	if (wordsPlatform) {
		if (wordsPlatform->m_hWnd) {
			wordsPlatform->MoveWindow(&wordsPlatformRect);
		}
	}
	if (dictPlatform) {
		if (dictPlatform->m_hWnd) {
			dictPlatform->MoveWindow(&dictPlatformRect);
		}
	}
	Invalidate();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CWordSearchDlg::OnBnClickedButton1()
{
	TextLoader tl;
	tl.Load();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

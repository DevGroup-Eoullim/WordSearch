
// WordSearch.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//
#include "pch.h"
#include "framework.h"
#include "WordSearch.h"
//#include <io.h>
//#include <fcntl.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWordSearchApp

BEGIN_MESSAGE_MAP(CWordSearchApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWordSearchApp 생성

CWordSearchApp::CWordSearchApp()
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CWordSearchApp 개체입니다.

CWordSearchApp theApp;


// CWordSearchApp 초기화
ULONG_PTR gdiplusToken;

BOOL CWordSearchApp::InitInstance()
{


	//_setmode(_fileno(stdout), _O_U16TEXT);
// TODO: richedit2 라이브러리를 초기화하려면 AfxInitRichEdit2()을(를) 호출합니다.\n"	// 애플리케이션 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	//// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	//// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	AfxInitRichEdit2();
	CWinApp::InitInstance();
	/*GdiplusStartupInput gdiplusStartupInput;
	if (::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL) != Ok) {
		AfxMessageBox(_T("GDI+ 라이브러리의 초기화에 실패하였습니다!"));
		return FALSE;
	}*/

	//AfxEnableControlContainer();

	////// 대화 상자에 셸 트리 뷰 또는
	////// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	//CShellManager *pShellManager = new CShellManager;

	////// MFC 컨트롤의 테마를 사용하기 위해 "Windows 원형" 비주얼 관리자 활성화
	//CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	mainDlg = new CWordSearchDlg;
	m_pMainWnd = mainDlg;
	mainDlg->Create(IDD_WORDSEARCH_DIALOG, this->GetMainWnd());

	return TRUE;
}


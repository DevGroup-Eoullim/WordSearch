
// WordSearchDlg.h: 헤더 파일
//

#pragma once
#include "SentenceEdit.h"
#include "DefinitionEdit.h"
#include "searcher.h"
#include "dictionary.h"
#include "SearchPlatform.h"
#include "TranslatePlatform.h"
#include "DictPlatform.h"
#include "WordsPlatform.h"
#include "InputBtPlatform.h"

// CWordSearchDlg 대화 상자
class CWordSearchDlg : public CDialogEx
{
// 생성입니다.
public:
	CWordSearchDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORDSEARCH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
private:
	Searcher searcher;
	DefinitionEdit* edDefinition;
	Dictionary dictionary;
	Dictionary globalDict;
	//CFont font;
	ChildProcess cp;
	SentenceEdit* edSentence;
	CRichEditCtrl* edTranslate;
	CListBox* liWords;
	CButton* btOpenInput;


	SearchPlatform* searchPlatform=0;
	TranslatePlatform* translatePlatform = 0;
	DictPlatform* dictPlatform = 0;
	WordsPlatform* wordsPlatform = 0;
	InputBtPlatform* inputBtPlatform = 0;

	void SetItemsStyle();
public:
	//afx_msg LRESULT OnMessage(WPARAM wParam, LPARAM lParam);
//	CListBox liWords;

	Dictionary* getDictionary();
	//afx_msg void OnEnChangeEditDefinition();
//	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
//	afx_msg void OnSetFocus(CWnd* pOldWnd);
//	CListCtrl liWords;
//	afx_msg void OnLbnSelchangeListWords();
	
//	afx_msg void OnClickedBtOpenInput();
//	afx_msg void OnIddWordsearchDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
//	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
//	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnBnClickedButton1();
};

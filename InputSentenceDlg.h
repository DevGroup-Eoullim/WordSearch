#pragma once
#include "afxdialogex.h"


// InputSentenceDlg 대화 상자

class InputSentenceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InputSentenceDlg)

public:
	InputSentenceDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~InputSentenceDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT_SENTENCE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnIdno();
	afx_msg void OnEnChange();
	CRichEditCtrl edSentence;
	virtual BOOL OnInitDialog();

	CString getSentence();
private:
	CString sentence;
	CHARFORMAT2 charStyle;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};

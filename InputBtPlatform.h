#pragma once
#include "afxdialogex.h"
#include "EditContainer.h"
//#include "Style.h"

// InputBtPlatform 대화 상자

class InputBtPlatform : public EditContainer
{
	DECLARE_DYNAMIC(InputBtPlatform)

public:
	InputBtPlatform(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~InputBtPlatform();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUTBTPLATFORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CMFCButton ctrl;
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
};

#pragma once
#include "afxdialogex.h"

#include "EditContainer.h"

// TranslatePlatform 대화 상자

class TranslatePlatform : public EditContainer
{
	DECLARE_DYNAMIC(TranslatePlatform)

public:
	TranslatePlatform(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TranslatePlatform();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANSLATEPLATFORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl ctrl;
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
};

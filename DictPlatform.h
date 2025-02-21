#pragma once
#include "afxdialogex.h"
#include "EditContainer.h"

// DictPlatform 대화 상자

class DictPlatform : public EditContainer
{
	DECLARE_DYNAMIC(DictPlatform)

public:
	DictPlatform(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DictPlatform();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DICTPLATFORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	DefinitionEdit ctrl;
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
};

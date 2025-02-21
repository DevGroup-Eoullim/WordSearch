#pragma once
#include "afxdialogex.h"
#include "EditContainer.h"


// SearchPlatform 대화 상자

class SearchPlatform : public EditContainer
{
	DECLARE_DYNAMIC(SearchPlatform)

public:
	SearchPlatform(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SearchPlatform();
private:
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCHPLATFORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	SentenceEdit edit;
	virtual BOOL OnInitDialog();
//	afx_msg void OnPaint();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

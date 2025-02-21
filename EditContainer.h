#pragma once
#include "afxdialogex.h"
#include "Style.h"


// EditContainer 대화 상자

class EditContainer : public CDialogEx
{
	DECLARE_DYNAMIC(EditContainer)

public:
	EditContainer(UINT id, COLORREF* borderColor, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~EditContainer();
	void Draw(CPaintDC* dc);
private:
	int arc;
	CWnd* pCtrl=0;
	int padding = 2;
protected:
	COLORREF* bg = TextStyle::style.pNowBGColor;
	COLORREF* border = 0;//0x625f58
	COLORREF* txt = TextStyle::style.pNowTextColor;

	CRect rect;
	void setPCtrl(CWnd* pCtrl);
	

// 대화 상자 데이터입니다.
//#ifdef AFX_DESIGN_TIME
//	enum { IDD = IDD_EDITCONTAINER_DIALOG };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

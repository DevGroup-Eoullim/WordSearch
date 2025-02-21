#pragma once
//#include <afxrich.h>
#include "framework.h"
#include "searcher.h"
#include "CRichEditBase.h"
#include <thread>
#include "ChildProcess.h"

class SentenceEdit : public CRichEditCtrl //: public CRichEditBase
{
public:
    SentenceEdit();
    virtual ~SentenceEdit();

    void Init(CWnd* parent);
    CHARFORMAT2& getSelCharStyle();

    void setText(CString str);
    void setTextId(int textId);
protected:
 /*   afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);*/
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    DECLARE_MESSAGE_MAP()
private :
    bool lctrlDown;
    Searcher searcher;
    CWnd* parent;
    FINDTEXTEX textToFind;
    CHARFORMAT2 selCharStyle;
    CHARFORMAT2 charStyle;
    CHARRANGE targetRange = { -1,-1 };
    int selectionMode;
    int textId=-1;
    bool reDraw = false;
    

    void SearchWordThread(CString str);
    CHARRANGE GetWord(long origin);
    CHARRANGE GetSentence(long origin);
    void CallOnMouseMove();
public:
//    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//    afx_msg void OnSetFocus(CWnd* pOldWnd);
//    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
//    afx_msg void OnMouseHover(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
//    afx_msg void OnNcPaint();
};
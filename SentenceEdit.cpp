
//#include "pch.h"

#include "framework.h"
#include "SentenceEdit.h"
#include "curl/curl.h"
#include <iostream>
#include "resource.h"
#include "dictionary.h"
#include <thread>
#include "InputSentenceDlg.h"
#include <richedit.h>
#include "Database.h"
#include "Style.h"


#define SELECT_WORD 1
#define SELECT_SENTENCE 2

void FindTextThread(SentenceEdit* ed, CString text, int textId) {
    WDVec wordDataVec;
    dbManager.GetWordAll(textId, text, &wordDataVec);

    for (WDVec::iterator iter = wordDataVec.begin(); iter != wordDataVec.end(); iter++) {
        NS_DB::WordData wd = *iter;
        CHARFORMAT2 style = TextStyle::style.getPosStyle(wd.pos);

        ed->SetSel(wd.start, wd.end);

        TextStyle::style.AddSelect(wd.start, style);
        style = TextStyle::style.GetWordTopStyle(wd.start);
        ed->SetSelectionCharFormat(style);
    }
}
void SentenceEdit::SearchWordThread(CString str) {
    DictionaryData* dictData;
    dictData = searcher.SearchWord(str);
    if (!dictData) {
        parent->SendMessage(WM_COMMAND, SM_ERROR, (WPARAM)str.GetString());
        printf("error\n");
        return;
    }
    parent->SendMessage(WM_COMMAND, SM_DONE, (WPARAM)dictData);
}



SentenceEdit::SentenceEdit() {
    lctrlDown = false;
    CHARRANGE chrg(0, -1);
    textToFind.chrg = chrg;

    selectionMode = SELECT_WORD;
}
SentenceEdit::~SentenceEdit() {}

BEGIN_MESSAGE_MAP(SentenceEdit, CRichEditCtrl)
    ON_WM_KEYDOWN()
    ON_WM_SETFOCUS()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_KEYUP()
//    ON_WM_NCPAINT()
END_MESSAGE_MAP()

void SentenceEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // 예: Enter 키를 눌렀을 때 커스텀 동작 수행
    CString result;
    
    switch (nChar) {
    case VK_CONTROL:
        if (selectionMode != SELECT_SENTENCE) {
            reDraw = true;
            selectionMode = SELECT_SENTENCE;
            CallOnMouseMove();
        }
        break;
    default:
        CRichEditCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
        break;
    }
    
}
void SentenceEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    switch (nChar) {
    case VK_CONTROL:
        if (selectionMode != SELECT_WORD) {
            reDraw = true;
            selectionMode = SELECT_WORD;
            CallOnMouseMove();
        }
        break;
    }
    CRichEditCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}


void SentenceEdit::Init(CWnd* parent) {

    this->parent = parent;
    //this->searcher = searcher;


    SendMessage(EM_SETTEXTMODE, TM_RICHTEXT);
    SendMessage(EM_SETWORDWRAPMODE, 1);

    /*CRect rect;
    CRgn rgn;

    GetClientRect(rect);
    rgn.CreateRoundRectRgn(rect.left, rect.top, rect.right, rect.bottom, 50,50);

    ::SetWindowRgn(this->m_hWnd, (HRGN)rgn, TRUE);*/

    CHARFORMAT2 style = TextStyle::style.getDefaultStyle();
    SetDefaultCharFormat(style);

    SetReadOnly(1);
}

CHARFORMAT2& SentenceEdit::getSelCharStyle() {
    return selCharStyle;
}

void SentenceEdit::OnSetFocus(CWnd* pOldWnd)
{
    ::HideCaret(pOldWnd->GetSafeHwnd());
}

void SentenceEdit::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    if (GetFocus()->GetSafeHwnd() != GetSafeHwnd()) {
        SetFocus();
    }
    if (textId == -1) {
        CRichEditCtrl::OnMouseMove(nFlags, point);
        return;
    }
    
    static CHARRANGE oldWordRange = { -1,-1 };
    int idx=CharFromPos(point);

    static CHARFORMAT2 origin;
    CHARFORMAT2 highlight = TextStyle::style.getHighlightStyle();

    if ((idx <= targetRange.cpMin) || (idx >= targetRange.cpMax) || reDraw) {
        reDraw = false;
        CHARRANGE oldRange = targetRange;
        CHARFORMAT2 style;
        CHARFORMAT2 origin;
        origin.cbSize = sizeof(CHARFORMAT);

        SetSel(targetRange);
        GetSelectionCharFormat(origin);
        TextStyle::style.RemoveHighlight(&origin);
        SetSelectionCharFormat(origin);

        switch (selectionMode) {
        case SELECT_WORD:
            targetRange = GetWord(idx);
            break;
        case SELECT_SENTENCE:
            targetRange = GetSentence(idx);
            break;
        }
        SetSel(targetRange);
        GetSelectionCharFormat(origin);
        TextStyle::style.AddHighlight(&origin);
        SetSelectionCharFormat(origin);
    }

    CRichEditCtrl::OnMouseMove(nFlags, point);
}


void SentenceEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    //CRichEditCtrl::OnLButtonDown(nFlags, point);
}


void SentenceEdit::OnLButtonUp(UINT nFlags, CPoint point)
{
    CString* pStr=new CString;
    *pStr = GetSelText();

    CString str = *pStr;
    DictionaryData* dictData;

    SetSel(targetRange);

    
    switch (selectionMode) {
    case SELECT_WORD:
        if (str.GetLength()) {
            std::thread hSearchThread(&SentenceEdit::SearchWordThread, this, str);
            hSearchThread.detach();

            std::thread hFindThread(FindTextThread, this, str, textId);//(SentenceEdit*)(parent->GetDlgItem(IDC_EDIT_SENTENCE))
            hFindThread.detach();
        }
        break;
    case SELECT_SENTENCE:
        parent->SendMessage(WM_COMMAND, SM_TRANSLATE, (LPARAM)pStr);
        break;
    }
    CRichEditCtrl::OnLButtonUp(nFlags, point);
}
CHARRANGE SentenceEdit::GetWord(long origin) {
    long start, end=0;
    CHARRANGE result;

    HideSelection(true, false);

    start = origin;
    dbManager.GetWord(textId, &start, &end);

    result.cpMax = end;
    result.cpMin = start;

    return result;
}
CHARRANGE SentenceEdit::GetSentence(long origin) {
    /*long start, end;
    wchar_t startCh = 'a';
    wchar_t endCh = 'a';
    bool startDone = false, endDone = false;
    CHARRANGE result;

    HideSelection(true, false);*/

    long start, end = 0;
    CHARRANGE result;

    HideSelection(true, false);

    start = origin;
    dbManager.GetSentence(textId, &start, &end);
    printf("start: %d end: %d\n", start, end);

    //for (start = origin, end = origin; !(startDone && endDone);) {
    //    if (!startDone) {
    //        SetSel(start - 1, start);
    //        startCh = GetSelText().GetAt(0);
    //        start--;
    //        if ((startCh == '.') || (startCh == '?') || (startCh == '!')) {
    //            //printf("%d\n", start);
    //            start++;
    //            startDone = true;
    //        }
    //        if (start < 0) {
    //            start = 0;
    //            startDone = true;
    //        }
    //    }
    //    if (!endDone) {
    //        SetSel(end, end + 1);
    //        endCh = GetSelText().GetAt(0);
    //        end++;
    //        if ((endCh == '.') || (endCh == '?') || (endCh == '!')) {
    //            //printf("%d\n", end);
    //            //end--;
    //            endDone = true;
    //        }
    //        if (end > GetTextLength()) {
    //            end = 0;
    //            endDone = true;
    //        }
    //    }
    //}

    result.cpMax = end;
    result.cpMin = start;

    return result;
}

void SentenceEdit::setText(CString str) {
    SetWindowText(str);
    //HideSelection(true, true);
    SetSel(0, GetTextLength());
    CHARFORMAT2W style = TextStyle::style.getDefaultStyle();
    SetSelectionCharFormat(style);
}

void SentenceEdit::setTextId(int textId) {
    this->textId = textId;
}

void SentenceEdit::CallOnMouseMove() {
    CPoint point;
    GetCursorPos(&point);
    ScreenToClient(&point);

    UINT nFlags = 0;
    if (GetKeyState(VK_LBUTTON) < 0) nFlags |= MK_LBUTTON;
    if (GetKeyState(VK_RBUTTON) < 0) nFlags |= MK_RBUTTON;
    if (GetKeyState(VK_MBUTTON) < 0) nFlags |= MK_MBUTTON;
    if (GetKeyState(VK_CONTROL) < 0) nFlags |= MK_CONTROL;
    if (GetKeyState(VK_SHIFT) < 0) nFlags |= MK_SHIFT;

    OnMouseMove(nFlags, point);
}

//void SentenceEdit::OnNcPaint()
//{
    // TODO: 여기에 메시지 처리기 코드를 추가합니다.
    // 그리기 메시지에 대해서는 CRichEditCtrl::OnNcPaint()을(를) 호출하지 마십시오.
//    CRect rcWindow;
//    GetWindowRect(&rcWindow);
//    rcWindow.OffsetRect(-rcWindow.left, -rcWindow.top);
//
//    int nX = 0;
//    int nY = 0;
//    LONG lStyle = ::GetWindowLong(this->GetSafeHwnd(), GWL_STYLE);
    // WS_BORDER 속성이 적용되어 있느냐 없느냐에 따라 두께 계산
//    if (lStyle & WS_BORDER)
//    {
//        nX = GetSystemMetrics(SM_CXSIZEFRAME);
//        nY = GetSystemMetrics(SM_CYSIZEFRAME);
//    }
//    else
//    {
//        nX = GetSystemMetrics(SM_CXSIZEFRAME) - GetSystemMetrics(SM_CXBORDER);
//        nY = GetSystemMetrics(SM_CYSIZEFRAME) - GetSystemMetrics(SM_CYBORDER);
//    }
//
//    CDC* pDC = GetWindowDC();
    // 테두리 영역만을 위해 가운데 영역 제외
//    pDC->ExcludeClipRect(nX, nY, rcWindow.right - nX, rcWindow.bottom - nY);
//    {
        // 테두리에 그릴 내용
//        pDC->FillSolidRect(&rcWindow, RGB(255, 0, 0));
//    }
//    ReleaseDC(pDC);
//}

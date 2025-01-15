
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


#define SELECT_WORD 1
#define SELECT_SENTENCE 2


void FindTextThread(SentenceEdit* ed, CString text, long origin) {
//void FindTextThread(){
    FINDTEXTEXW ft;
    ZeroMemory(&ft, sizeof(FINDTEXTEXW));
    ft.chrg.cpMin = 0;
    ft.chrg.cpMax = -1;// ed->GetWindowTextLengthW();
    ft.lpstrText = text;
    //ed->HideSelection(true, true);
    while (ed->FindTextW(FR_DOWN| FR_WHOLEWORD, &ft) != -1) {
        printf("start: %d\n", ft.chrg.cpMin);

        ed->SetSel(ft.chrgText);
        ed->SetSelectionCharFormat(ed->getSelCharStyle());
        ft.chrg.cpMin = ft.chrgText.cpMax;
    }
    ed->SetSel(origin, origin);
}
void SentenceEdit::SearchWordThread(CString str) {
    DictionaryData* dictData;
    dictData = searcher->SearchWord(str);
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

    WORD r = 255, g = 200, b = 200;
    //WORD r = 100, g = 120, b = 150;

    ZeroMemory(&selCharStyle, sizeof(CHARFORMAT));
    selCharStyle.cbSize = sizeof(CHARFORMAT);
    selCharStyle.dwMask = CFM_BACKCOLOR|CFM_COLOR;
    selCharStyle.crBackColor = RGB(r,g,b);
    selCharStyle.crTextColor = RGB(255 - r, 255 - g, 255 - b);

    selectionMode = SELECT_WORD;
    
    //SetReadOnly();
}
SentenceEdit::~SentenceEdit() {}

BEGIN_MESSAGE_MAP(SentenceEdit, CRichEditCtrl)
    ON_WM_KEYDOWN()
//    ON_WM_LBUTTONDOWN()
//    ON_WM_SETCURSOR()
    ON_WM_SETFOCUS()
    //ON_WM_MOUSEHOVER()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
//    ON_WM_KEYUP()
ON_WM_KEYUP()
END_MESSAGE_MAP()

void SentenceEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // 예: Enter 키를 눌렀을 때 커스텀 동작 수행
    CString result;
    
    switch (nChar) {
    case 'S':
        
        if (GetKeyState(VK_LCONTROL)&0x8000) {
            CString str;
            DictionaryData* dictData;
            CHARRANGE cr = { 0 };

            GetSel(cr);
            if (cr.cpMin == cr.cpMax) {
                return;
            }
            str = GetSelText();
            //printf("replace return: %d\n", str.Replace(L" ", L""));
            str.Replace(L" ", L"");
            str.Replace(L"\r\n", L"");
            cr.cpMax = cr.cpMin + str.GetLength();
            //printf("start: %d\n", cr.cpMin);
            SetSel(cr);

            textToFind.lpstrText = str;

            dictData = searcher->SearchWord(str);
            if (!dictData) {
                parent->SendMessage(WM_COMMAND, SM_ERROR, (WPARAM)str.GetString());
                printf("error\n");
                return;
            }
            parent->SendMessage(WM_COMMAND,SM_DONE, (WPARAM)dictData);

            //FindText(FR_WHOLEWORD, &textToFind);
            SetSelectionCharFormat(selCharStyle);
            
            std::thread hFindThread(FindTextThread, (SentenceEdit*)(parent->GetDlgItem(IDC_EDIT_SENTENCE)), dictData->getWord(), cr.cpMax);
            hFindThread.detach();
            printf("done\n");
        }
        break;
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


void SentenceEdit::Init(CWnd* parent, Searcher* searcher) {

    this->parent = parent;
    this->searcher = searcher;

    SendMessage(EM_SETTEXTMODE, TM_RICHTEXT);
    SendMessage(EM_SETWORDWRAPMODE, 1);

    ZeroMemory(&charStyle, sizeof(CHARFORMAT2));
    charStyle.cbSize = sizeof(CHARFORMAT2);
    charStyle.dwMask = CFM_SIZE | CFM_FACE | CFM_WEIGHT;
    wcscpy(charStyle.szFaceName, L"Cambria");
    charStyle.yHeight = 19 * 15; //19폰트?
    charStyle.wWeight = FW_MEDIUM;
    //charStyle.bCharSet = HANGEUL_CHARSET;

    SetDefaultCharFormat(charStyle);

    SetReadOnly(1);
}

CHARFORMAT2& SentenceEdit::getSelCharStyle() {
    return selCharStyle;
}



//void SentenceEdit::OnLButtonDown(UINT nFlags, CPoint point)
//{
//    if (GetKeyState(VK_LCONTROL) & 0x8000) {
//        InputSentenceDlg dlg;
//        int result=dlg.DoModal();
//        if (result == IDOK) {
//            SetWindowTextW(dlg.getSentence());
//        }
//    }
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    // 문장 입력 대화상자 열기
    
//    CRichEditCtrl::OnLButtonDown(nFlags, point);
//}


//BOOL SentenceEdit::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
//{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//    SetCursor(NULL);
//    return TRUE;
//}


void SentenceEdit::OnSetFocus(CWnd* pOldWnd)
{
    
    //SetReadOnly(1);
    /*HideSelection(true, false);
    CRichEditCtrl::OnSetFocus(pOldWnd);*/
    //CRichEditCtrl::OnSetFocus(pOldWnd);
    ::HideCaret(pOldWnd->GetSafeHwnd());
    // TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


//void SentenceEdit::OnMouseHover(UINT nFlags, CPoint point)
//{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//    printf("%d, %d\n", point.x, point.y);
//    CRichEditCtrl::OnMouseHover(nFlags, point);
//}


void SentenceEdit::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    if (GetFocus()->GetSafeHwnd() != GetSafeHwnd()) {
        SetFocus();
    }
    
    //static CHARRANGE targetRange = { -1,-1 };
    static CHARRANGE oldWordRange = { -1,-1 };
    int idx=CharFromPos(point);
    
    CHARFORMAT2 cf;
    ZeroMemory(&cf, sizeof(CHARFORMAT2));
    cf.cbSize = sizeof(CHARFORMAT2);
    cf.dwMask = CFM_UNDERLINE;
    cf.dwEffects = CFE_UNDERLINE;

    CHARFORMAT2 originStyle;
    ZeroMemory(&originStyle, sizeof(CHARFORMAT2));
    originStyle.cbSize = sizeof(CHARFORMAT2);
    originStyle.dwMask = CFM_ALL;
    wcscpy(originStyle.szFaceName, L"Cambria");
    originStyle.yHeight = 19 * 15; //19폰트?
    originStyle.wWeight = FW_MEDIUM;
    originStyle.dwEffects = 0;
    
    if ((idx <= targetRange.cpMin) || (idx >= targetRange.cpMax) || reDraw) {
        reDraw = false;
        SetSel(targetRange);
        SetSelectionCharFormat(originStyle);

        switch (selectionMode) {
        case SELECT_WORD:
            targetRange = GetWord(idx);
            break;
        case SELECT_SENTENCE:
            targetRange = GetSentence(idx);
            break;
        }
        SetSel(targetRange);
        SetSelectionCharFormat(cf);
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
    //CHARRANGE origin,wordRange;
    CString* pStr=new CString;
    *pStr = GetSelText();

    CString str = *pStr;
    DictionaryData* dictData;

    /*GetSel(origin);
    wordRange=GetWord(origin.cpMin);*/
    SetSel(targetRange);

    
    switch (selectionMode) {
    case SELECT_WORD:
        if (str.GetLength()) {
            //SetSelectionCharFormat(selCharStyle);

            std::thread hSearchThread(&SentenceEdit::SearchWordThread, this, str);
            hSearchThread.detach();

            std::thread hFindThread(FindTextThread, (SentenceEdit*)(parent->GetDlgItem(IDC_EDIT_SENTENCE)), str, targetRange.cpMax);
            hFindThread.detach();
        }
        break;
    case SELECT_SENTENCE:
        parent->SendMessage(WM_COMMAND, SM_TRANSLATE, (LPARAM)pStr);
        /*CStringA str2(str);
        printf("%s\n", str2);*/
        break;
    }
    
    //printf("replace return: %d\n", str.Replace(L" ", L""));

   /* dictData = searcher->SearchWord(str);
    if (!dictData) {
        parent->SendMessage(WM_COMMAND, SM_ERROR, (WPARAM)str.GetString());
        printf("error\n");
        return;
    }
    parent->SendMessage(WM_COMMAND, SM_DONE, (WPARAM)dictData);*/

    //FindText(FR_WHOLEWORD, &textToFind);
    

    //printf("%d\n",origin.cpMin);
    CRichEditCtrl::OnLButtonUp(nFlags, point);
}
CHARRANGE SentenceEdit::GetWord(long origin) {
    long start, end;
    wchar_t startCh='a';
    wchar_t endCh = 'a';
    bool startDone = false, endDone = false;
    CHARRANGE result;

    HideSelection(true, false);

    for (start = origin, end = origin; !(startDone && endDone);) {
        if (!startDone) {
            SetSel(start - 1, start);
            startCh = GetSelText().GetAt(0);
            start--;
            if (!((startCh >= 'A') && (startCh <= 'Z') || (startCh >= 'a') && (startCh <= 'z'))) {
                //printf("%d\n", start);
                start++;
                startDone = true;
            }
        }
        if (!endDone) {
            SetSel(end, end + 1);
            endCh = GetSelText().GetAt(0);
            end++;
            if (!((endCh >= 'A') && (endCh <= 'Z') || (endCh >= 'a') && (endCh <= 'z'))) {
                //printf("%d\n", end);
                end--;
                endDone = true;
            }
        }
        
    }
    //for (end = origin; end < GetTextLength(); end++) {
    //    SetSel(end, end + 1);
    //    endCh = GetSelText().GetAt(0);
    //    //wprintf(L"%s(%d)\n", endCh, endCh.Compare(L" "));
    //    if (!((endCh >= 'A') && (endCh <= 'Z') || (endCh >= 'a') && (endCh <= 'z'))) {
    //        //printf("%d\n", end);
    //        break;
    //    }
    //}

    //for (start = origin; start >= 0; start--) {
    //    SetSel(start - 1, start);
    //    startCh = GetSelText().GetAt(0);
    //    //wprintf(L"%s(%d)\n", startCh, startCh.Compare(L" "));
    //    if (!((startCh >= 'A') && (startCh <= 'Z') || (startCh >= 'a') && (startCh <= 'z'))) {
    //        //printf("%d\n", start);
    //        break;
    //    }
    //}
    //for (end = origin; end < GetTextLength(); end++) {
    //    SetSel(end, end + 1);
    //    endCh = GetSelText().GetAt(0);
    //    //wprintf(L"%s(%d)\n", endCh, endCh.Compare(L" "));
    //    if (!((endCh >= 'A') && (endCh <= 'Z') || (endCh >= 'a') && (endCh <= 'z'))) {
    //        //printf("%d\n", end);
    //        break;
    //    }
    //}

    //HideSelection(false, true);

    result.cpMax = end;
    result.cpMin = start;

    return result;
}
CHARRANGE SentenceEdit::GetSentence(long origin) {
    long start, end;
    wchar_t startCh = 'a';
    wchar_t endCh = 'a';
    bool startDone = false, endDone = false;
    CHARRANGE result;

    HideSelection(true, false);

    for (start = origin, end = origin; !(startDone && endDone);) {
        if (!startDone) {
            SetSel(start - 1, start);
            startCh = GetSelText().GetAt(0);
            start--;
            if ((startCh == '.') || (startCh == '?') || (startCh == '!')) {
                //printf("%d\n", start);
                start++;
                startDone = true;
            }
            if (start < 0) {
                start = 0;
                startDone = true;
            }
        }
        if (!endDone) {
            SetSel(end, end + 1);
            endCh = GetSelText().GetAt(0);
            end++;
            if ((endCh == '.') || (endCh == '?') || (endCh == '!')) {
                //printf("%d\n", end);
                //end--;
                endDone = true;
            }
            if (end > GetTextLength()) {
                end = 0;
                endDone = true;
            }
        }
    }
    
    //for (start = origin; start >= 0; start--) {
    //    SetSel(start - 1, start);
    //    ch = GetSelText().GetAt(0);
    //    //wprintf(L"%s(%d)\n", ch, ch.Compare(L" "));
    //    if ((ch == '.')||(ch == '?')||(ch == '!')) {
    //        //printf("%d\n", start);
    //        start++;
    //        break;
    //    }
    //}
    //for (end = origin; end < GetTextLength(); end++) {
    //    SetSel(end, end + 1);
    //    ch = GetSelText().GetAt(0);
    //    //wprintf(L"%s(%d)\n", ch, ch.Compare(L" "));
    //        if ((ch == '.') || (ch == '!') || (ch == '?')) {
    //        //printf("%d\n", end);
    //        break;
    //    }
    //}

    //HideSelection(false, true);

    result.cpMax = end;
    result.cpMin = start;

    return result;
}

void SentenceEdit::SetText(CString str) {
    SetWindowText(str);
    //HideSelection(true, true);
    SetSel(0, GetTextLength());
    SetSelectionCharFormat(charStyle);
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
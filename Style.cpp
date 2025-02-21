#include "Style.h"


namespace TextStyle {
    CHARFORMAT2 Style::getHighlightStyle() {
        CHARFORMAT2 style;

        WORD r = 255, g = 200, b = 200;
        ZeroMemory(&style, sizeof(CHARFORMAT));
        style.cbSize = sizeof(CHARFORMAT);
        style.dwMask = CFE_BOLD;
        //style.dwMask = CFM_BACKCOLOR | CFM_COLOR;
        //style.crBackColor = RGB(r, g, b);
        //style.crTextColor = RGB(255 - r, 255 - g, 255 - b);
        style.yHeight = yHeight; //19폰트?

        return style;
    }

    CHARFORMAT2 Style::getDefaultStyle() {
        CHARFORMAT2 style;

        WORD r = 255, g = 200, b = 200;
        ZeroMemory(&style, sizeof(CHARFORMAT2));
        style.cbSize = sizeof(CHARFORMAT2);
        style.dwMask = CFM_SIZE | CFM_FACE | CFM_WEIGHT | CFM_COLOR;
        wcscpy(style.szFaceName, font);
        style.yHeight = yHeight; //19폰트?
        style.crTextColor = *pNowTextColor;
        style.wWeight = FW_MEDIUM;

        return style;
    }

    CHARFORMAT2 Style::getPosStyle(int pos) {
        CHARFORMAT2 style;

        ZeroMemory(&style, sizeof(CHARFORMAT));
        style.cbSize = sizeof(CHARFORMAT);
        style.dwMask = CFM_BACKCOLOR;
        style.crBackColor = posStyle[pos];
        //style.crTextColor = RGB(255 - r, 255 - g, 255 - b);
        style.yHeight = yHeight; //19폰트?

        return style;
    }

    CHARFORMAT2 Style::getBaseStyle() {
        CHARFORMAT2 style;

        ZeroMemory(&style, sizeof(CHARFORMAT2));
        style.cbSize = sizeof(CHARFORMAT2);
        style.dwMask = CFM_UNDERLINE;
        style.dwEffects = CFE_UNDERLINE;

        return style;
    }

    CHARFORMAT2 Style::getOriginStyle() {
        CHARFORMAT2 style;

        ZeroMemory(&style, sizeof(CHARFORMAT2));
        style.cbSize = sizeof(CHARFORMAT2);
        style.dwMask = CFM_ALL| CFM_BACKCOLOR;
        wcscpy(style.szFaceName, font);
        style.crBackColor = RGB(255,255,255);
        style.yHeight = yHeight; //19폰트?
        style.wWeight = FW_MEDIUM;
        style.dwEffects = 0;

        return style;
    }
    CFont* Style::getMedium19() {
        return &medium19;
    }
    CFont* Style::getBold19() {
        return &bold19;
    }

    void Style::RemoveHighlight(CHARFORMAT2* style) {
        //style->dwMask &= ~CFM_COLOR;
        style->crTextColor = *pNowTextColor;
        //style->dwEffects &= ~CFE_BOLD;

    }
    void Style::AddHighlight(CHARFORMAT2* style) {
        //style->dwEffects |= CFE_BOLD;
        //style->dwMask |= CFM_COLOR;
        style->crTextColor = *pNowHiligherColor;
    }

    void Style::RemoveHighlight(int start) {
        if (!wordStyleLayer.contains(start)) {
            return;
        }
        if (wordStyleLayer[start].highlight) {
            delete wordStyleLayer[start].highlight;
            wordStyleLayer[start].highlight = 0;
        }
    }
    void Style::AddHighlight(int start, CHARFORMAT2 style) {
        if (!wordStyleLayer.contains(start)) {
            wordStyleLayer.insert({ start,{nullptr,nullptr} });
        }
        if (wordStyleLayer.at(start).highlight) {
            delete wordStyleLayer.at(start).highlight;
            wordStyleLayer.at(start).highlight = nullptr;
        }
        wordStyleLayer.at(start).highlight = new CHARFORMAT2(style);
    }
    void Style::RemoveSelect(int start) {
        if (!wordStyleLayer.contains(start)) {
            return;
        }
        CHARFORMAT2* pStyle = wordStyleLayer[start].select;
        if (pStyle) {
            delete pStyle;
            pStyle = 0;
        }
    }
    void Style::AddSelect(int start, CHARFORMAT2 style) {
        if (!wordStyleLayer.contains(start)) {
            wordStyleLayer.insert({ start,{0,0} });
        }
        CHARFORMAT2** pStyle = &wordStyleLayer.at(start).select;
        if (*pStyle) {
            delete *pStyle;
            *pStyle = 0;
        }
        *pStyle = new CHARFORMAT2(style);
    }

    CHARFORMAT2 Style::GetWordTopStyle(int start) {
        CHARFORMAT2* select = wordStyleLayer[start].select;
        CHARFORMAT2* highlight = wordStyleLayer[start].highlight;

        if (wordStyleLayer.contains(start)) {
            if (highlight) {
                return *highlight;
            }
            if (select) {
                return *select;
            }
        }
        return getOriginStyle();
    }


    void Style::AddSentenceOrigin(int start, CHARFORMAT2 style) {
        if (!sentenceStyleLayer.contains(start)) {
            sentenceStyleLayer.insert({ start,{0,0} });
            return;
        }
        if (!wordStyleLayer[start].select) {
            wordStyleLayer[start].select = new CHARFORMAT2(style);
        }
        *wordStyleLayer[start].highlight = style;
    }
    void Style::AddSentenceHighlight(int start, CHARFORMAT2 style) {
        if (!sentenceStyleLayer.contains(start)) {
            sentenceStyleLayer.insert({ start,{0,0} });
            return;
        }
        if (!wordStyleLayer[start].highlight) {
            wordStyleLayer[start].highlight = new CHARFORMAT2(style);
        }
    }
    void Style::RemoveSentenceHighlight(int start) {
        if (!wordStyleLayer.contains(start)) {
            return;
        }
        if (wordStyleLayer[start].highlight) {
            delete wordStyleLayer[start].highlight;
            wordStyleLayer[start].highlight = 0;
        }
    }

    CHARFORMAT2 Style::GetSentenceTopStyle(int start) {
        CHARFORMAT2* select = wordStyleLayer[start].select;
        CHARFORMAT2* highlight = wordStyleLayer[start].highlight;

        if (wordStyleLayer.contains(start)) {
            if (highlight) {
                return *highlight;
            }
            if (select) {
                return *select;
            }
        }
        return getOriginStyle();
    }
    Style::Style() {
        AddFontResource(L"font/Pretendard-Medium.ttf");
        AddFontResource(L"font/Pretendard-Bold.ttf");

        LOGFONT lf;
        ZeroMemory(&lf, sizeof(LOGFONT));
        lf.lfHeight = 19;
        wcscpy(lf.lfFaceName, L"Pretendard Medium");

        medium19.CreateFontIndirectW(&lf);

        wcscpy(lf.lfFaceName, L"Pretendard");
        bold19.CreateFontIndirectW(&lf);
    }

    Style style;
}

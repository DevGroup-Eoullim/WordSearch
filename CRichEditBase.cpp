#include "CRichEditBase.h"

void CRichEditBase::InitStyle() {
    TCHAR className[256];
    GetClassName(GetSafeHwnd(), className, 256);
    wprintf(L"%s\n", className);

	ZeroMemory(&charStyle, sizeof(CHARFORMAT));
	charStyle.cbSize = sizeof(CHARFORMAT);
	charStyle.dwMask = CFM_SIZE | CFM_FACE | CFM_WEIGHT | CFM_CHARSET;
	charStyle.yHeight = 19 * 15; //19폰트?
	charStyle.wWeight = FW_MEDIUM;
	charStyle.bCharSet = DEFAULT_CHARSET;
	wcscpy(charStyle.szFaceName, L"consolas");

    SetDefaultCharFormat(charStyle);

	//font.CreatePointFont(9 * 15, L"함초롬바탕");

    int nHeight = 20; // 19 포인트
    int nWeight = FW_MEDIUM; // 중간 두께
    BYTE bItalic = FALSE; // 이탤릭체 여부
    BYTE bUnderline = FALSE; // 밑줄 여부
    BYTE cStrikeOut = 0; // 취소선 여부
    BYTE nCharSet = DEFAULT_CHARSET; // 한글 문자 집합
    BYTE nOutPrecision = OUT_DEFAULT_PRECIS; // 출력 정밀도
    BYTE nClipPrecision = CLIP_DEFAULT_PRECIS; // 클리핑 정밀도
    BYTE nQuality = DEFAULT_QUALITY; // 품질
    BYTE nPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE; // 피치 및 패밀리

    // 폰트 이름
    LPCWSTR lpszFaceName = L"함초롬바탕";

    // CFont 객체 생성
    font.CreateFontW(nHeight, 0, 0, 0, nWeight, bItalic, bUnderline,
        cStrikeOut, nCharSet, nOutPrecision,
        nClipPrecision, nQuality, nPitchAndFamily,
        lpszFaceName);
}
#include "CRichEditBase.h"

void CRichEditBase::InitStyle() {
    TCHAR className[256];
    GetClassName(GetSafeHwnd(), className, 256);
    wprintf(L"%s\n", className);

	ZeroMemory(&charStyle, sizeof(CHARFORMAT));
	charStyle.cbSize = sizeof(CHARFORMAT);
	charStyle.dwMask = CFM_SIZE | CFM_FACE | CFM_WEIGHT | CFM_CHARSET;
	charStyle.yHeight = 19 * 15; //19��Ʈ?
	charStyle.wWeight = FW_MEDIUM;
	charStyle.bCharSet = DEFAULT_CHARSET;
	wcscpy(charStyle.szFaceName, L"consolas");

    SetDefaultCharFormat(charStyle);

	//font.CreatePointFont(9 * 15, L"���ʷҹ���");

    int nHeight = 20; // 19 ����Ʈ
    int nWeight = FW_MEDIUM; // �߰� �β�
    BYTE bItalic = FALSE; // ���Ÿ�ü ����
    BYTE bUnderline = FALSE; // ���� ����
    BYTE cStrikeOut = 0; // ��Ҽ� ����
    BYTE nCharSet = DEFAULT_CHARSET; // �ѱ� ���� ����
    BYTE nOutPrecision = OUT_DEFAULT_PRECIS; // ��� ���е�
    BYTE nClipPrecision = CLIP_DEFAULT_PRECIS; // Ŭ���� ���е�
    BYTE nQuality = DEFAULT_QUALITY; // ǰ��
    BYTE nPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE; // ��ġ �� �йи�

    // ��Ʈ �̸�
    LPCWSTR lpszFaceName = L"���ʷҹ���";

    // CFont ��ü ����
    font.CreateFontW(nHeight, 0, 0, 0, nWeight, bItalic, bUnderline,
        cStrikeOut, nCharSet, nOutPrecision,
        nClipPrecision, nQuality, nPitchAndFamily,
        lpszFaceName);
}
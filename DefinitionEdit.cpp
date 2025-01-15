#include "DefinitionEdit.h"
#include "resource.h"

void DefinitionEdit::ReStyle() {
	CHARRANGE cr;
	CHARFORMAT2 charStyle;

	ZeroMemory(&charStyle, sizeof(CHARFORMAT2));
	charStyle.cbSize = sizeof(CHARFORMAT2);
	charStyle.dwMask = CFM_SIZE | CFM_FACE | CFM_WEIGHT;
	wcscpy(charStyle.szFaceName, L"Cambria");
	charStyle.yHeight = 19 * 15; //19ÆùÆ®?
	charStyle.wWeight = FW_MEDIUM;

	cr.cpMin = 0;
	cr.cpMax = GetTextLength();
	SetSel(cr);
	SetFont(&font, 1);
	//printf("%d\n", SetWordCharFormat(charStyle));
}

BEGIN_MESSAGE_MAP(DefinitionEdit, CRichEditBase)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

void DefinitionEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	printf("%d\n", nChar);
	SetSel(1, 4);
	CString str;
	str = GetSelText();
	wprintf(_T("%s\n"), str);
}
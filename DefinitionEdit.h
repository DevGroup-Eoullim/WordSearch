#pragma once

#include "CRichEditBase.h"

class DefinitionEdit : public CRichEditBase
{
protected:
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    DECLARE_MESSAGE_MAP()
public:
    void ReStyle();
};
#pragma once

#include "framework.h"

class CRichEditBase : public CRichEditCtrl
{
protected:
	CHARFORMAT2 charStyle;
	CFont font;
public:
	void InitStyle();
};


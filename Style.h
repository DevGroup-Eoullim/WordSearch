#pragma once
#include "framework.h"
#include <map>
#include <vector>

namespace TextStyle {
	struct StyleLayer {
		CHARFORMAT2* highlight;
		CHARFORMAT2* select;
	};
	struct ColorGroup {
		COLORREF bgColor;
		COLORREF hiligherColor;
		COLORREF textColor;
		COLORREF pointColor;
		COLORREF border1Color;
		COLORREF border2Color;
	};

	typedef std::map<int, TextStyle::StyleLayer> StyleLayerType;

	class Style {
	private:
		long yHeight = 19 * 15;
		const WCHAR* font = L"Pretendard Medium";
	public:
		StyleLayerType wordStyleLayer;
		StyleLayerType sentenceStyleLayer;
		COLORREF posStyle[36] = {
			RGB(255, 82, 82),
			RGB(255, 152, 0),
			RGB(255, 235, 59),
			RGB(139, 195, 74),
			RGB(76, 175, 80),
			RGB(0, 230, 118),
			RGB(0, 188, 212),
			RGB(3, 169, 244),
			RGB(63, 81, 181),
			RGB(103, 58, 183),
			RGB(156, 39, 176),
			RGB(233, 30, 99),
			RGB(255, 64, 129),
			RGB(255, 215, 64),
			RGB(118, 255, 3),
			RGB(244, 67, 54),
			RGB(179, 136, 255)
			/*RGB(255, 223, 186),
			RGB(186, 225, 255),
			RGB(198, 255, 198),
			RGB(255, 198, 255),
			RGB(255, 246, 186),
			RGB(224, 255, 255),
			RGB(255, 192, 192),
			RGB(186, 255, 238),
			RGB(255, 223, 255),
			RGB(255, 231, 186),
			RGB(210, 210, 255),
			RGB(186, 255, 186),
			RGB(245, 245, 245),
			RGB(186, 201, 255),
			RGB(224, 255, 224),
			RGB(255, 210, 210),
			RGB(224, 224, 224)*/
		};
		COLORREF tagStyle[36] = {
			RGB(255, 204, 204),
			RGB(255, 229, 204),
			RGB(255, 255, 204),
			RGB(230, 255, 204),
			RGB(204, 255, 204),
			RGB(204, 255, 230),
			RGB(204, 255, 255),
			RGB(204, 229, 255),
			RGB(204, 204, 255),
			RGB(229, 204, 255),
			RGB(255, 204, 255),
			RGB(255, 204, 229),
			RGB(255, 217, 204),
			RGB(255, 255, 230),
			RGB(230, 255, 230),
			RGB(204, 255, 230),
			RGB(204, 230, 255),
			RGB(217, 204, 255),
			RGB(255, 204, 230),
			RGB(255, 204, 204),
			RGB(255, 204, 153),
			RGB(255, 230, 204),
			RGB(255, 255, 153),
			RGB(230, 255, 153),
			RGB(204, 255, 153),
			RGB(153, 255, 204),
			RGB(153, 255, 255),
			RGB(153, 204, 255),
			RGB(153, 153, 255),
			RGB(204, 153, 255),
			RGB(255, 153, 255),
			RGB(255, 153, 204),
			RGB(255, 153, 153),
			RGB(255, 230, 153),
			RGB(255, 255, 204),
			RGB(230, 255, 204)
		};

		ColorGroup dark = {
			0x1c1517,
			0x81888b,
			0xd9eaf3,
			//0xfe4622,
			0x2246fe,
			0x585f62,
			0x323740
		};
		ColorGroup light = {
			0x17151c,
			0x8b8881,
			0xf3ead9,
			0xfe4622,
			0x625f58,
			0x403732
		};
		ColorGroup now = dark;
		/*COLORREF nowBGColor = 0x17151c;
		COLORREF nowHiligherColor = 0x8b8881;
		COLORREF nowTextColor = 0xf3ead9;
		COLORREF nowPointColor = 0xfe4622;*/

		COLORREF* pNowBGColor = &now.bgColor;
		COLORREF* pNowHiligherColor = &now.hiligherColor;
		COLORREF* pNowTextColor = &now.textColor;
		COLORREF* pNowPointColor = &now.pointColor;
		COLORREF* pNowBorder1Color = &now.border1Color; 
		COLORREF* pNowBorder2Color = &now.border2Color;

		CFont medium19;
		CFont bold19;

		/*COLORREF defaultTxtColor = 0xf3ead9;
		COLORREF highlightTxtColor = 0x8b8881;*/

		CHARFORMAT2 getDefaultStyle();
		CHARFORMAT2 getHighlightStyle();
		CHARFORMAT2 getBaseStyle();
		CHARFORMAT2 getPosStyle(int pos);
		CHARFORMAT2 getOriginStyle();
		CFont* getMedium19();
		CFont* getBold19();

		void RemoveHighlight(CHARFORMAT2* style);
		void AddHighlight(CHARFORMAT2* style);

		void RemoveHighlight(int start);
		void AddHighlight(int start, CHARFORMAT2 style);
		void RemoveSelect(int start);
		void AddSelect(int start, CHARFORMAT2 style);
		CHARFORMAT2 GetWordTopStyle(int start);

		void AddSentenceOrigin(int start, CHARFORMAT2 style);
		void AddSentenceHighlight(int start, CHARFORMAT2 style);
		void RemoveSentenceHighlight(int start);
		CHARFORMAT2 GetSentenceTopStyle(int start);

		Style();
	};
	extern Style style;
}

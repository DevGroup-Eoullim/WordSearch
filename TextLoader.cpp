#include "TextLoader.h"


void TextLoader::Load() {
	dbManager.GetTexts(&bundle);

	for (TextBundleVec::iterator iter = bundle.begin(); iter != bundle.end(); iter++) {
		CStringA str(iter->text);
		printf("%d: %s\n", iter->id, str);
	}
}
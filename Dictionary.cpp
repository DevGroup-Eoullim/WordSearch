#include "dictionary.h"



CString Dictionary::GetDictionaryString(CString word) {
	try {
		return dict[word]->GetDictionaryString();
	}
	catch (int e) {
		printf("get dictionary error: %d\n", e);
		return 0;
	}
}
void Dictionary::Append(DictionaryData* dictData) {
	CString word = dictData->getWord();
	MeaningMap* pMeaingMap = dictData->getPMeadningMap();

	dict.insert({ dictData->getWord(),dictData });

	for (MeaningMapIter iter = pMeaingMap->begin(); iter != pMeaingMap->end(); iter++) {
		//Meaning* mean = (Meaning*)*iter;
		dbManager.SaveDef(word, iter->first, iter->second);
	}
}
void Dictionary::Load() {
	dbManager.GetDef(&dict);

	for (DictMap::iterator iter = dict.begin(); iter != dict.end(); iter++) {
		DictionaryData* dictData = iter->second;
		dictData->PrintData();
	}
}
#pragma once

#include "framework.h"
#include <cjson/cJSON.h>
#include <vector>
#include <map>

struct Meaning {
	CString word;
	CString partOfSpeech;
	//std::vector<CString> examples; //예문
	CString definitions;
	//std::vector<CString> synonyms; //동의어
	//std::vector<CString> antonyms; //반어
};

typedef std::vector<CString> DefVec;
typedef DefVec::iterator DefVecIter;

typedef std::map<CString, DefVec> MeaningMap;
typedef MeaningMap::iterator MeaningMapIter;
class DictionaryData {
private:
	CString word;
	//std::vector<Meaning*> meanings;
	MeaningMap meanings; //pos, def
public:
	DictionaryData(CString word);
	DictionaryData(cJSON* json);
	void AppendDef(CString pos, CString def);
	CString GetDictionaryString();
	CString getWord();
	MeaningMap* getPMeadningMap();
	//void Save();

	void PrintData();
};

typedef std::map<CString, DictionaryData*> DictMap;
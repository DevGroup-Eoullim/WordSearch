#pragma once

#include "framework.h"
#include "database.h"
#include <cjson/cJSON.h>
#include <vector>
#include <map>

//map으로 할까봐

//struct Meaning {
//	CString partOfSpeech;
//	//std::vector<CString> examples; //예문
//	std::vector<CString> definitions;
//	//std::vector<CString> synonyms; //동의어
//	//std::vector<CString> antonyms; //반어
//};

class Dictionary:public Database {
private:
	DictMap dict;
public:
	CString GetDictionaryString(CString word);
	void Append(DictionaryData* dictData);
	void Load();
};

CStringW ConvertUTF8ToCStringW(const CStringA& utf8String);
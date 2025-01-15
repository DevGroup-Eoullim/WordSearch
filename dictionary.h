#pragma once

#include "framework.h"
#include <cjson/cJSON.h>
#include <vector>
#include <map>

struct Meaning {
	CString partOfSpeech;
	//std::vector<CString> examples; //예문
	std::vector<CString> definitions;
	std::vector<CString> synonyms; //동의어
	std::vector<CString> antonyms; //반어
};

class DictionaryData {
private:
	CString word;
	std::vector<Meaning*> meanings;
public:
	DictionaryData(cJSON* json);
	CString GetDictionaryString();
	CString getWord();
};

class Dictionary {
private:
	std::map<CString, DictionaryData*> dict;
public:
	CString GetDictionaryString(CString word);
	void Append(DictionaryData* dictData);
};

CStringW ConvertUTF8ToCStringW(const CStringA& utf8String);
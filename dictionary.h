#pragma once

#include "framework.h"
#include "database.h"
#include <cjson/cJSON.h>
#include <vector>
#include <map>

//map���� �ұ��

//struct Meaning {
//	CString partOfSpeech;
//	//std::vector<CString> examples; //����
//	std::vector<CString> definitions;
//	//std::vector<CString> synonyms; //���Ǿ�
//	//std::vector<CString> antonyms; //�ݾ�
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
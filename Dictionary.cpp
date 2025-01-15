#include "dictionary.h"

CStringW ConvertUTF8ToCStringW(const CStringA& utf8String) {
	if (utf8String.IsEmpty()) return L"";

	int wideCharLen = MultiByteToWideChar(CP_UTF8, 0, utf8String, -1, NULL, 0);
	wchar_t* wideString = new wchar_t[wideCharLen];
	MultiByteToWideChar(CP_UTF8, 0, utf8String, -1, wideString, wideCharLen);

	CStringW cstring(wideString);
	delete[] wideString;

	return cstring;
}

DictionaryData::DictionaryData(cJSON* json) {
	cJSON* jsonWord = cJSON_GetObjectItemCaseSensitive(json->child, "word");
	CStringA utf8Word = cJSON_GetStringValue(jsonWord);
	word = ConvertUTF8ToCStringW(utf8Word);

	cJSON* jsonMeanings = cJSON_GetObjectItemCaseSensitive(json->child, "meanings");
	cJSON* jsonMeaning;

	cJSON_ArrayForEach(jsonMeaning, jsonMeanings) {
		Meaning* meaning = new Meaning;
		cJSON* jsonPartOfSpeech = cJSON_GetObjectItemCaseSensitive(jsonMeaning, "partOfSpeech");
		meaning->partOfSpeech = cJSON_GetStringValue(jsonPartOfSpeech);

		cJSON* jsonDefinitions = cJSON_GetObjectItemCaseSensitive(jsonMeaning, "definitions");
		cJSON* definition;

		cJSON_ArrayForEach(definition, jsonDefinitions) {
			cJSON* child = definition;
			cJSON* jsonDef = cJSON_GetObjectItemCaseSensitive(child, "definition");
			CStringA utf8Def = cJSON_GetStringValue(jsonDef);
			meaning->definitions.push_back(ConvertUTF8ToCStringW(utf8Def));
		}

		cJSON* jsonSynonyms = cJSON_GetObjectItemCaseSensitive(jsonMeaning, "synonyms");
		if (jsonSynonyms) {
			cJSON* jsonSynonym;
			cJSON_ArrayForEach(jsonSynonym, jsonSynonyms) {
				CStringA utf8Synonym = cJSON_GetStringValue(jsonSynonym);
				meaning->synonyms.push_back(ConvertUTF8ToCStringW(utf8Synonym));
			}
		}

		cJSON* jsonAntonyms = cJSON_GetObjectItemCaseSensitive(jsonMeaning, "antonyms");
		if (jsonAntonyms) {
			cJSON* jsonAntonym;
			cJSON_ArrayForEach(jsonAntonym, jsonAntonyms) {
				CStringA utf8Antonym = cJSON_GetStringValue(jsonAntonym);
				meaning->antonyms.push_back(ConvertUTF8ToCStringW(utf8Antonym));
			}
		}

		meanings.push_back(meaning);
	}
}

CString DictionaryData::GetDictionaryString() {
	CString dict = L"";
	CString dictWordPart;
	dictWordPart.Format(L"단어: %s\r\n\r\n", word);

	//CString dictMeaningsPart=L"";

	CString dictMeaningsPart = L"";
	for (int i = 0; i < meanings.size(); i++) {

		CString dictPartOfSpeechPart;
		dictPartOfSpeechPart.Format(L"  품사: %s\r\n", meanings[i]->partOfSpeech);

		dictMeaningsPart += dictPartOfSpeechPart;

		for (int j = 0; j < meanings[i]->definitions.size(); j++) {
			CString part;
			part.Format(L"    뜻: %s\r\n", meanings[i]->definitions[j]);
			dictMeaningsPart += part;
		}

		CString dictSynonymsPart = L"    동의어: ";
		for (int j = 0; j < meanings[i]->synonyms.size(); j++) {
			CString part;
			part.Format(L"%s", meanings[i]->synonyms[j]);
			dictSynonymsPart += part;
			if (j < meanings[i]->synonyms.size() - 1) {
				dictSynonymsPart += L", ";
			}
		}
		dictSynonymsPart += L"\r\n";
		dictMeaningsPart += dictSynonymsPart;

		CString dictAntonymsPart = L"    반어: ";
		for (int j = 0; j < meanings[i]->antonyms.size(); j++) {
			CString part;
			part.Format(L"%s", meanings[i]->antonyms[j]);
			dictAntonymsPart += part;
			if (j < meanings[i]->antonyms.size() - 1) {
				dictAntonymsPart += L", ";
			}
		}
		dictAntonymsPart += L"\r\n\r\n";
		dictMeaningsPart += dictAntonymsPart;
	}

	dict = dictWordPart + dictMeaningsPart;

	return dict;
}

CString DictionaryData::getWord() {
	return word;
}

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
	dict.insert({ dictData->getWord(),dictData });
}
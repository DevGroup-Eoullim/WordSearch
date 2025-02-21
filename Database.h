#pragma once

#include "sqlite3.h"
#include "framework.h"
#include <map>
#include <vector>

#include "DictionaryData.h"

typedef sqlite3 DBC; //DB Connection
//typedef (*sqlite3_open) DBOpen;
typedef std::map<int, int> PosMap;

namespace NS_DB{
	struct WordData {
		long start, end;
		int pos,tag;
	};
	struct TextBundle {
		int id;
		CString text;
	};
}


typedef std::vector<NS_DB::WordData> WDVec;
typedef std::vector<NS_DB::TextBundle> TextBundleVec;

//typedef std::vector<CString> DefVec;
//typedef DefVec::iterator DefVecIter;
//
//typedef std::map<CString, DefVec> MeaningMap;
//typedef MeaningMap::iterator MeaningMapIter;

class Database
{
private:
	DBC* Connect();
	void Close(DBC* db);
	std::map<CStringA, char> posMap = {
		{"ADJ",0},
		{"ADP",1},
		{"ADV",2},
		{"AUX",3},
		{"CCONJ",4},
		{"DET",5},
		{"INTJ",6},
		{"NOUN",7},
		{"NUM",8},
		{"PART",9},
		{"PRON",10},
		{"PROPN",11},
		{"PUNCT",12},
		{"SCONJ",13},
		{"SYM",14},
		{"VERB",15},
		{"X",16}
	};
	std::map<CStringA, char> tagMap = {
		{ "WRB",0 },
		{ "CC",1 },
		{ "CD",2 },
		{ "DT",3 },
		{ "EX",4 },
		{ "FW",5 },
		{ "IN",6 },
		{ "JJ",7 },
		{ "JJR",8 },
		{ "JJS",9 },
		{ "LS",10 },
		{ "MD",11 },
		{ "NN",12 },
		{ "NNS",13 },
		{ "NNP",14 },
		{ "NNPS",15 },
		{ "PDT",16 },
		{ "POS",17 },
		{ "PRP",18 },
		{ "PRP$",19 },
		{ "RB",20 },
		{ "RBR",21 },
		{ "RBS",22 },
		{ "RP",23 },
		{ "SYM",24 },
		{ "TO",25 },
		{ "UH",26 },
		{ "VB",27 },
		{ "VBD",28 },
		{ "VBG",29 },
		{ "VBN",30 },
		{ "VBP",31 },
		{ "VBZ",32 },
		{ "WDT",33 },
		{ "WP",34 },
		{ "WP$",35 }
	};
public:
	Database();
	void GetPartOfSpeech(CString condition, PosMap* pPosMap);
	void GetWord(int textid, long* start, long* end);
	void GetWordAll(int textid, CString text, WDVec* wordDataVec);
	void GetSentence(int textid, long* start, long* end);
	void GetTexts(TextBundleVec* pBundleVec);
	void SaveDef(CString word,CString pos, std::vector<CString> definitions);
	void GetDef(DictMap* dictMap);
};

extern Database dbManager; //db manager
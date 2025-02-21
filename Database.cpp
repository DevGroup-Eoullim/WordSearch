#define _CRT_SECURE_NO_WARNINGS

#include "Database.h"
#include <stdio.h>
#include <regex>

Database::Database() {}
DBC* Database::Connect() {
	DBC* db;
	int result = sqlite3_open(R"(.\database.db)",&db);
	if (result == SQLITE_OK) {
		//printf("database connected\n");
	}
	else {
		printf("database connect fail: %s\n", sqlite3_errmsg(db));
		return 0;
	}
	return db;
}
void Database::Close(DBC* db) {
	sqlite3_close(db);
	//sqlite3_exec()
}
void Database::GetPartOfSpeech(CString condition, PosMap* pPosMap) {
	CString query=L"select start, tag from parts where";
	query += condition;
	CStringA tQuery(query);
	printf("tQuery: %s\n", tQuery);
	char* queryBuff = tQuery.GetBuffer();
	int queryResult;
	char* dbErrMsg = 0;

	DBC* db = Connect();
	if (!db) {
		return;
	}

	sqlite3_stmt* stmt = 0;
	queryResult=sqlite3_prepare(db, queryBuff, -1, &stmt, 0);
	if (queryResult != SQLITE_OK) {
		sqlite3_finalize(stmt);
		Close(db);
		//printf("fail to get room members (%s)\n", dbErrMsg);
		return;
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {

		int start=sqlite3_column_int(stmt, 0);
		const char* tag=(const char*)sqlite3_column_text(stmt, 1);
		CStringA tagStr(tag);
		printf("%d, %s, %d\n", start, tag, tagMap[tagStr]);
		pPosMap->insert({ start ,tagMap[tagStr]});
		//printf("member: %u\n", sqlite3_column_int(stmt, 0));
		//members->insert({ sqlite3_column_int(stmt, 0) ,sqlite3_column_int(stmt, 1) });
		//members->push_back(sqlite3_column_int(stmt, 0));
	}
	sqlite3_finalize(stmt);
	Close(db);

	tQuery.ReleaseBuffer();
}
void Database::GetWord(int textid, long* start, long* end){
	std::regex pattern("[a-zA-Z]");
	char query[128];
	int queryResult;
	sprintf(query, "select token, start, end from parts where textid=%d and start<=%d and end>=%d", textid, *start, *start);

	DBC* db = Connect();
	if (!db) {
		return;
	}

	sqlite3_stmt* stmt = 0;
	queryResult = sqlite3_prepare(db, query, -1, &stmt, 0);
	
	if (queryResult != SQLITE_OK) {
		*start = 0;
		*end = 0;
		printf("fail to get room members %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		Close(db);
		return;
	}
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		const char* token = (const char*)sqlite3_column_text(stmt, 0);
		if (std::regex_search(token, pattern)) {
			*start = sqlite3_column_int(stmt, 1);
			*end = sqlite3_column_int(stmt, 2);
		}
		else {
			*start = 0;
			*end = 0;
		}
	}
	sqlite3_finalize(stmt);
	Close(db);
}
void Database::GetWordAll(int textid, CString text, WDVec* wordDataVec) {
	char query[128];
	CStringA tText(text);
	char* textBuff = tText.GetBuffer();
	int queryResult;

	sprintf(query, "select start, end, tag, pos from parts where textid=%d and token=\"%s\"", textid, textBuff);
	printf("%s\n",query);

	DBC* db = Connect();
	if (!db) {
		return;
	}

	sqlite3_stmt* stmt = 0;
	queryResult = sqlite3_prepare(db, query, -1, &stmt, 0);

	if (queryResult != SQLITE_OK) {
		printf("fail to get room members %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		Close(db);
		return;
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int start = sqlite3_column_int(stmt, 0);
		int end = sqlite3_column_int(stmt, 1);
		const char* tag = (const char*)sqlite3_column_text(stmt, 2);
		const char* pos= (const char*)sqlite3_column_text(stmt, 3);
		printf("start: %d end: %d\n", start, end);
		
		NS_DB::WordData wd = {
			start,end,
			posMap[pos],tagMap[tag]
		};

		wordDataVec->push_back(wd);
	}
	sqlite3_finalize(stmt);
	Close(db);

	tText.ReleaseBuffer();
}
void Database::GetSentence(int textid, long* start, long* end) {
	char query[128];
	int queryResult;
	sprintf(query, "select start, end from sentence where textid=%d and start<=%d and end>=%d", textid, *start, *start);

	DBC* db = Connect();
	if (!db) {
		return;
	}

	sqlite3_stmt* stmt = 0;
	queryResult = sqlite3_prepare(db, query, -1, &stmt, 0);

	if (queryResult != SQLITE_OK) {
		*start = 0;
		*end = 0;
		printf("fail to get room members %s\n", sqlite3_errmsg(db));
		return;
	}
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		*start = sqlite3_column_int(stmt, 0);
		*end = sqlite3_column_int(stmt, 1);
	}
	else {
		*start = 0;
		*end = 0;
	}
	sqlite3_finalize(stmt);
	Close(db);
}
void Database::GetTexts(TextBundleVec* pBundleVec) {
	char query[128]="select textid, text from texts";
	int queryResult;
	//sprintf(query, "select textid, text from texts", textid, *start, *start);

	DBC* db = Connect();
	if (!db) {
		return;
	}

	sqlite3_stmt* stmt = 0;
	queryResult = sqlite3_prepare(db, query, -1, &stmt, 0);

	if (queryResult != SQLITE_OK) {
		printf("fail to get room members %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		Close(db);
		return;
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		const char* text = (const char*)sqlite3_column_text(stmt, 1);

		NS_DB::TextBundle data = {id,};
		CString tstr(text);
		//wsprintf(data.text, L"%s", text);
		data.text.SetString(tstr);

		pBundleVec->push_back(data);
	}
	sqlite3_finalize(stmt);
	Close(db);
}
void Database::SaveDef(CString word, CString pos, std::vector<CString> definitions) {
	DBC* db = Connect();
	if (!db) {
		return;
	}

	CStringA query="";
	CStringA tWord(word);
	CStringA tPos(pos);

	char* wordBuf = tWord.GetBuffer();
	char* posBuf = tPos.GetBuffer();

	for (std::vector<CString>::iterator iter = definitions.begin(); iter != definitions.end(); iter++) {
		char q[1024];
		CStringA tDef(*iter);
		char* buf = tDef.GetBuffer();
		sprintf(q, "insert into words (word,pos,definition) values ('%s', '%s', '%s'); ", wordBuf, posBuf, buf);
		//CStringA queryBlock(q);
		query += q;
		printf("%s\n", q);
		//query.push_back(q);
		tDef.ReleaseBuffer();
	}

	
	char* err_msg;
	int rc = sqlite3_exec(db, query, 0, 0, &err_msg);
	sqlite3_exec(db, "COMMIT;", 0, 0, 0);

	tWord.ReleaseBuffer();
	tPos.ReleaseBuffer();
}
void Database::GetDef(DictMap* dictMap) {
	char query[] = "select distinct word,pos,definition from words;";
	int queryResult;
	//sprintf(query, "select textid, text from texts", textid, *start, *start);

	DBC* db = Connect();
	if (!db) {
		return;
	}

	sqlite3_stmt* stmt = 0;
	queryResult = sqlite3_prepare(db, query, -1, &stmt, 0);

	if (queryResult != SQLITE_OK) {
		printf("fail to get room members %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		Close(db);
		return;
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		const char* word = (const char*)sqlite3_column_text(stmt, 0);
		const char* pos = (const char*)sqlite3_column_text(stmt, 1);
		const char* def = (const char*)sqlite3_column_text(stmt, 2);
		
		CString tWord(word);
		CString tPos(pos);
		CString tDef(def);

		if (!dictMap->contains(tWord)) {
			dictMap->insert({ tWord, new DictionaryData(tWord) });
		}
		dictMap->at(tWord)->AppendDef(tPos, tDef);
	}
	sqlite3_finalize(stmt);
	Close(db);
}

Database dbManager;
#include "Database.h"
#include <stdio.h>

Database::Database() {}
DBC* Database::Connect() {
	DBC* db;
	int result = sqlite3_open(R"(.\database.db)",&db);
	if (result == SQLITE_OK) {
		printf("database connected\n");
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
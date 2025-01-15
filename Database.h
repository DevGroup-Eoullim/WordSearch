#pragma once

#include "sqlite3.h"

typedef sqlite3 DBC; //DB Connection
//typedef (*sqlite3_open) DBOpen;

class Database
{
private:
	DBC* Connect();
	void Close(DBC* db);
public:
	Database();
};


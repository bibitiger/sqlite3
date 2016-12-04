/*
 * mainForNode.h
 *
 *  Created on: 2016-12-4
 *      Author: fanxu
 */

#include "include/sqlite3.h"

typedef enum _E_SQL_FUNC{
eSqlCreateTable = 0,
eSqlInsert,
eSqlDelete,
eSqlUpdate,
eSqlSelect,
eSqlSelectAll
}E_SQL_FUNC;

class CForNode{
private:
	CForNode(){

	}

	~CForNode(){

	}

public:
	CForNode(char* db){
		_db = NULL;
		createDB(db);
	}

	bool createDB(char* db);

	bool createTable(char* table, char* tableFormat);

	bool sqlInsert(char* table, char* format, char* content);

	bool sqlDelete(char* table, char* condition);

	bool sqlUpdate(char* table, char* content, char* condition);

	bool sqlSelect(char* table, char* condition);

	bool sqlSelectAll(char* table);

	static int callback(void *NotUsed, int argc, char **argv, char **azColName);

private:
	sqlite3* _db;
};


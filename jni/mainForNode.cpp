/*
 * mainForNode.cpp
 *
 *  Created on: 2016-12-4
 *      Author: fanxu
 */


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stddef.h>
#include <stdlib.h>
#include "mainForNode.h"

using namespace std;

int main(int argc, char* argv[]){
	if(argc < 3){
		cout<<"error,arg number less than 3,cormate error"<<endl;
		return -1;
	}

	cout<<"fornode begin"<<endl;

	int sqlType = atoi(argv[2]);
	CForNode *cForNode = new CForNode(argv[1]);
	switch (sqlType){
	case eSqlCreateTable:
		cout<<"eSqlCreateTable"<<endl;
		if(argc < 5){
			cout<<"error,arg should be like : test1.db 0 users \"id INTEGER PREIMARY KEY AUTOINCRMENT , name TEXT, score TEXT\""<<endl;
			return -1;
		}
		cForNode->createTable(argv[3],argv[4]);
		break;	
	case eSqlInsert:
		cout<<"eSqlInsert"<<endl;
		if(argc < 6){
			cout<<"error,arg should be like : test1.db 1 users \"name , score\" \"'zhangqiang', '32'\""<<endl;
			return -1;
		}
		cForNode->sqlInsert(argv[3],argv[4],argv[5]);
		break;
	case eSqlDelete:
		cout<<"eSqlDelete"<<endl;
		if(argc < 5){
			cout<<"error,arg should be like : test1.db 2 users \"score = '32'\""<<endl;
			return -1;
		}
		cForNode->sqlDelete(argv[3],argv[4]);
		break;
	case eSqlUpdate:
		cout<<"eSqlUpdate"<<endl;
		if(argc < 6){
			cout<<"error,arg should be like : test1.db 3 users \"score = '45'\" \"name = 'zhangqiang'\""<<endl;
			return -1;
		}
		cForNode->sqlUpdate(argv[3],argv[4],argv[5]);
		break;
	case eSqlSelect:
		cout<<"eSqlSelect"<<endl;
		if(argc < 5){
			cout<<"error,arg should be like : test1.db 4 users \"score = '45'\""<<endl;
			return -1;
		}
		cForNode->sqlSelect(argv[3],argv[4]);
		break;
	case eSqlSelectAll:
		cout<<"eSqlSelectAll"<<endl;
		if(argc < 4){
			cout<<"error,arg should be like : test1.db 0 users"<<endl;
			return -1;
		}
		cForNode->sqlSelectAll(argv[3]);
		break;
	defualt:
		cout<<"cant know what you want do, arg: 0: createTable,1: insert, 2: delete, 3: update, 4: select, 5: selectAll"<<endl;
		break;
	}
	return 0;
}


bool CForNode::createDB(char* db) {
	int ret = sqlite3_open(db, &_db);
	if(ret != SQLITE_OK && ret != SQLITE_DONE){
		cout<<"error,can not open db,please check path!!"<<endl;
		return false;
	}
	cout<<"createDB success"<<endl;
	return true;
}

bool CForNode::createTable(char* table, char* tableFormat) {
	if(_db == NULL)
		return false;

	int tableLen = strlen(table);
	if(tableLen > 20){
		cout<<"error, table name length limit in 20"<<endl;
		return false;
	}
	int tableFormatLen = strlen(tableFormat);
	if(tableFormatLen > 200){
		cout<<"error, tableFormat length limit in 200"<<endl;
		return false;
	}

	char sql[300];
	memset(sql,0,sizeof(sql));
	sprintf(sql,"create table if not exists %s(%s)", table, tableFormat);
	char* error = NULL;
	int ret = sqlite3_exec(_db, sql, NULL, NULL, &error);
	if(ret == SQLITE_OK)
		cout<<"createTable success"<<endl;
	else{
		cout<<"error,createTable failed,error NO. is "<<ret<<" error is "<<error<<endl;
	}
	return true;
}

bool CForNode::sqlInsert(char* table, char* format, char* content) {
	if(_db == NULL)
	return false;

	int tableLen = strlen(table);
	if(tableLen > 20){
		cout<<"error, table name length limit in 20"<<endl;
		return false;
	}
	int formatLen = strlen(format);
	if(formatLen > 1024*1024){
		cout<<"error, format length limit in 1024*1024"<<endl;
		return false;
	}
	int contentLen = strlen(content);
	if(contentLen > 2*1024*1024){
		cout<<"error, content length limit in 2*1024*1024"<<endl;
		return false;
	}

	char sql[300+3*1024*1024];
	memset(sql,0,sizeof(sql));
	sprintf(sql,"replace into %s (%s) values (%s)", table, format, content);
	cout<<sql<<endl;
	char* error = NULL;
	int ret = sqlite3_exec(_db, sql, NULL, NULL, &error);
	if(ret == SQLITE_OK)
		cout<<"sqlInsert success"<<endl;
	else{
		cout<<"error,sqlInsert failed,error NO. is "<<ret<<" error is "<<error<<endl;
	}
	return true;
}

bool CForNode::sqlDelete(char* table, char* condition) {
	if(_db == NULL)
	return false;

	int tableLen = strlen(table);
	if(tableLen > 20){
		cout<<"error, table name length limit in 20"<<endl;
		return false;
	}
	int conditionLen = strlen(condition);
	if(conditionLen > 1024*1024){
		cout<<"error, condition length limit in 1024*1024"<<endl;
		return false;
	}

	char sql[300+1024*1024];
	memset(sql,0,sizeof(sql));
	sprintf(sql,"delete from %s where %s", table, condition);
	char* error = NULL;
	int ret = sqlite3_exec(_db, sql, NULL, NULL, &error);
	if(ret == SQLITE_OK)
		cout<<"sqlDelete success"<<endl;
	else{
		cout<<"error,sqlDelete failed,error NO. is "<<ret<<" error is "<<error<<endl;
	}
	return true;
}

bool CForNode::sqlUpdate(char* table, char* content, char* condition) {
	if(_db == NULL)
	return false;

	int tableLen = strlen(table);
	if(tableLen > 20){
		cout<<"error, table name length limit in 20"<<endl;
		return false;
	}
	int conditionLen = strlen(condition);
	if(conditionLen > 1024*1024){
		cout<<"error, condition length limit in 1024*1024"<<endl;
		return false;
	}
	int contentLen = strlen(content);
	if(contentLen > 2*1024*1024){
		cout<<"error, content length limit in 2*1024*1024"<<endl;
		return false;
	}

	char sql[300+3*1024*1024];
	memset(sql,0,sizeof(sql));
	sprintf(sql,"update %s set %s where %s", table, content, condition);
	char* error = NULL;
	int ret = sqlite3_exec(_db, sql, NULL, NULL, &error);
	if(ret == SQLITE_OK)
		cout<<"sqlUpdate success"<<endl;
	else{
		cout<<"error,sqlUpdate failed,error NO. is "<<ret<<" error is "<<error<<endl;
	}
	return true;
}

bool CForNode::sqlSelect(char* table, char* condition) {
	if(_db == NULL)
	return false;

	int tableLen = strlen(table);
	if(tableLen > 20){
		cout<<"error, table name length limit in 20"<<endl;
		return false;
	}
	int conditionLen = strlen(condition);
	if(conditionLen > 1024*1024){
		cout<<"error, condition length limit in 1024*1024"<<endl;
		return false;
	}

	char sql[300+1024*1024];
	memset(sql,0,sizeof(sql));
	sprintf(sql,"select * from %s where %s", table, condition);
	char* error = NULL;
	int ret = sqlite3_exec(_db, sql, CForNode::callback, NULL, &error);
	if(ret == SQLITE_OK)
		cout<<"sqlSelect success"<<endl;
	else{
		cout<<"error,sqlSelect failed,error NO. is "<<ret<<" error is "<<error<<endl;
	}
	return true;
}

bool CForNode::sqlSelectAll(char* table) {
	if(_db == NULL)
	return false;

	int tableLen = strlen(table);
	if(tableLen > 20){
		cout<<"error, table name length limit in 20"<<endl;
		return false;
	}

	char sql[300];
	memset(sql,0,sizeof(sql));
	sprintf(sql,"select * from %s", table);
	char* error = NULL;
	int ret = sqlite3_exec(_db, sql, CForNode::callback, NULL, &error);
	if(ret == SQLITE_OK)
		cout<<"sqlSelectAll success"<<endl;
	else{
		cout<<"error,sqlSelectAll failed,error NO. is "<<ret<<" error is "<<error<<endl;
	}
	return true;
}

int CForNode::callback(void *NotUsed, int argc, char **argv, char **azColName)  
{  
     
    for(int i = 0 ; i < argc ; i++)  
    {  
        cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << ", " ;  
    }  
   
    cout<< endl;  
    return 0;  
}




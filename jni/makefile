sql3 : src/sqlite3.o mainForNode.o
	g++ -o sql3 sqlite3.o mainForNode.o

src/sqlite3.o : src/sqlite3.c include/sqlite3.h include/sqlite3ext.h
	cc -c src/sqlite3.c
mainForNode.o : mainForNode.cpp mainForNode.h
	g++ -c mainForNode.cpp
clean :
	rm sql3 sqlite3.o mainForNode.o test.db test1.db
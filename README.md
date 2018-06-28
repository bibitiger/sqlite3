# sqlite3

##command example:

>create table: ./sql test1.db 0 users "id integer primary key autoincrement unique, name TEXT, score TEXT"

>insert: ./sql test1.db 1 users "id, name , score" "null, 'zhangqiang', '32'"

>delete: ./sql test1.db 2 users "score = '32'"

>update: ./sql test1.db 3 users "score = '45'" "name = 'zhangqiang'"

>select: ./sql test1.db 4 users "score = '45'"

>select all: ./sql test1.db 5 users


##command explain:


command | exec| db path| command tag| table name| format| cotent| condition
--------|------|------|---------|----------------|-------|------|-----------
create table:| ./sql| test1.db| 0| users| "id integer primary key autoincrement unique , name TEXT, score TEXT"
insert:| ./sql| test1.db |1 |users| "name , score" |"'zhangqiang', '32'"
delete:| ./sql |test1.db |2| users||| "score = '32'"
update:| ./sql| test1.db| 3| users ||"score = '45'"| "name = 'zhangqiang'"
select:| ./sql |test1.db| 4|users |||"score = '45'"
select all:| ./sql| test1.db| 5 |users

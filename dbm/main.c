//
//  main.c
//  dbm
//
//  Created by janezhuang on 2024/4/28.
//

#include <stdio.h>
#include <fcntl.h>
#include "db.h"
#include "apue.h"

int main(int argc, const char *argv[]) {
    DBHANDLE db;
    // 打开数据库
    if ((db = db_open("/Users/jane/Desktop/db4", O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) == NULL) {
        err_sys("db_open error");
    }
    // 增
    if (db_store(db, "Alpha", "data1", DB_INSERT) != 0) {
        err_sys("db_store error for alpha");
    }
    if (db_store(db, "Beta", "data for beta", DB_INSERT) != 0) {
        err_sys("db_store error for beta");
    }
    if (db_store(db, "gamma", "record3", DB_INSERT) != 0) {
        err_sys("db_store error for gamma");
    }
    // 查
    char *data = db_fetch(db, "Beta");
    printf("%s\n", data);
    // 删
    if (db_delete(db, "Beta") != 0) {
        err_sys("db_delete error");
    }
    // 改
    if (db_store(db, "gamma", "new record3", DB_REPLACE) != 0) {
        err_sys("db_store error for gamma");
    }
    // 遍历
    db_rewind(db);
    char key[1024];
    do {
        char *data = db_nextrec(db, key);
        if (data == NULL) {
            break;
        }
        printf("%s ==> %s \n", key, data);
    } while (1);
    // 关闭数据库
    db_close(db);

    return 0;
}

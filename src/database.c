#include "databse.h"
#include "sqlite3.h"
#include "knob.h"

#define LOG_SQLITE3_ERROR(db) knob_log(KNOB_ERROR, "%s:%d: SQLITE3 ERROR: %s\n", __FILE__, __LINE__, sqlite3_errmsg(db))

void database_start(GameData* g){
    sqlite3_open("game.db", &g->db);
}

const char* create_customer_table =
"CREATE TABLE IF NOT EXISTS Customer ("
"   CustomerId INTEGER PRIMARY KEY,"
"   name TEXT,"
"   email TEXT"
");";

void database_init_tables(GameData* g) {

    if (sqlite3_exec(g->db, create_customer_table, NULL, NULL, NULL) != SQLITE_OK) {
        LOG_SQLITE3_ERROR(g->db);
        return;
    }
}

void database_end(GameData* g) {
    sqlite3_close(g->db);
}
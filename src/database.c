#include "database.h"
#include "sqlite3.h"
#include "knob.h"

#define LOG_SQLITE3_ERROR(db) knob_log(KNOB_ERROR, "%s:%d: SQLITE3 ERROR: %s\n", __FILE__, __LINE__, sqlite3_errmsg(db))

void database_start(GameData* g){
    sqlite3_open("game.db", &g->db);
}


const char* create_race_table =
"CREATE TABLE IF NOT EXISTS Race ("
"   RaceId INTEGER PRIMARY KEY,"
"   race_name TEXT"
");";

const char* create_class_table =
"CREATE TABLE IF NOT EXISTS Classes ("
"   ClassId INTEGER PRIMARY KEY,"
"   class_name TEXT"
");";

const char* create_stats_table =
"CREATE TABLE IF NOT EXISTS Stats ("
"   StatId INT PRIMARY KEY,"
"   stat_name TEXT,"
"   stat_upgrade_cost INT,"
"   stat_points INT,"
"   FOREIGN KEY (stat_points) REFERENCES Character(stat_points)"
");";

const char* create_character_table =
"CREATE TABLE IF NOT EXISTS Character ("
"   CharacterId INTEGER PRIMARY KEY,"
"   gender INT,"// 1==male | 2==female
"   hair_type INT,"
"   hair_color INT,"
"   stat_points INT,"
"   RaceId INT,"
"   ClassId INT,"
"   StatId INT,"
"   FOREIGN KEY (RaceId) REFERENCES Race(RaceId),"
"   FOREIGN KEY (ClassId) REFERENCES Classes(ClassId),"
"   FOREIGN KEY (StatId) REFERENCES Stats(StatId)"
");";

const char* create_customer_table =
"CREATE TABLE IF NOT EXISTS Customer ("
"   CustomerId INTEGER PRIMARY KEY,"
"   name TEXT,"
"   email TEXT"
// "   CharacterId INT,"
// "   FOREIGN KEY (CharacterId) REFERENCES Character(CharacterId)"
");";

const char* create_item_table =
"CREATE TABLE IF NOT EXISTS Item ("
"   ItemId INT PRIMARY KEY,"
"   item_name TEXT,"
"   item_price INT,"
"   item_availability INT" // 1 == true == available | 0 == false == already bought
");";


void database_init_tables(GameData* g) {
    
    if (sqlite3_exec(g->db, create_race_table, NULL, NULL, NULL) != SQLITE_OK) {
        LOG_SQLITE3_ERROR(g->db);
        return;
    }

    if (sqlite3_exec(g->db, create_class_table, NULL, NULL, NULL) != SQLITE_OK) {
        LOG_SQLITE3_ERROR(g->db);
        return;
    }
    
    if (sqlite3_exec(g->db, create_stats_table, NULL, NULL, NULL) != SQLITE_OK) {
        LOG_SQLITE3_ERROR(g->db);
        return;
    }
    
    if (sqlite3_exec(g->db, create_character_table, NULL, NULL, NULL) != SQLITE_OK) {
        LOG_SQLITE3_ERROR(g->db);
        return;
    }

    if (sqlite3_exec(g->db, create_customer_table, NULL, NULL, NULL) != SQLITE_OK) {
        LOG_SQLITE3_ERROR(g->db);
        return;
    }

    if (sqlite3_exec(g->db, create_item_table, NULL, NULL, NULL) != SQLITE_OK) {
        LOG_SQLITE3_ERROR(g->db);
        return;
    }

}

void database_end(GameData* g) {
    sqlite3_close(g->db);
}
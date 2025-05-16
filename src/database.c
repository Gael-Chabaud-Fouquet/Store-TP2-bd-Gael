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

const char* create_socialstatus_table =
"CREATE TABLE IF NOT EXISTS SocialStatus ("
"   SocialStatusId INTEGER PRIMARY KEY,"
"   social_status TEXT"
");";

const char* create_faction_table =
"CREATE TABLE IF NOT EXISTS Faction ("
"   FactionId INTEGER PRIMARY KEY,"
"   faction_name TEXT"
");";

const char* create_character_table =
"CREATE TABLE IF NOT EXISTS Character ("
"   CharacterId INTEGER PRIMARY KEY,"
"   name TEXT CHECK (LENGTH(name) <= 16),"
"   level INT,"
"   strenght INT,"
"   stamina INT,"
"   stealth INT,"
"   rizz INT," //aka charisma
"   gender INT,"// 1==male | 2==female
"   RaceId INT,"
"   SocialStatusId INT,"
"   FactionId INT,"
"   FOREIGN KEY (RaceId) REFERENCES Race(RaceId),"
//"   FOREIGN KEY (ClassId) REFERENCES Classes(ClassId),"
"   FOREIGN KEY (FactionId) REFERENCES Faction(FactionId)"
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
"   ItemId INTEGER PRIMARY KEY,"
"   item_name TEXT,"
"   item_type INT," // 1 == light armor | 2 == heavy armor | 3 == weapon
"   item_type_type INT," // 1 == helmet | 2 == chest | 3 == legs | 4 == boots | 5 == sword | 6 == bow | etc, etc
"   item_material INT," // material is color | 1 == blue | 2 == green | etc, etc
"   item_price INT,"
"   item_availability INT" // 1 == true == available | 0 == false == already bought, thus unavailable
");";

const char* insert_race_table =
"INSERT INTO Race (race_name)"
"VALUES"
"   ('Nord'),"
"   ('Dark_Elf'),"
"   ('Redguard'),"
"   ('Orc');";

const char* insert_socialstatus_table =
"INSERT INTO SocialStatus (social_status)"
"VALUES"
"   ('Citizen'),"
"   ('Merchant'),"
"   ('Soldier');";

const char* insert_faction_table =
"INSERT INTO Faction (faction_name)"
"VALUES"
"   ('Dawnguard'),"
"   ('Forsworm'),"
"   ('BrotherhoodOfSteel'),"
"   ('Imperials');";

const char* insert_character_table =
"INSERT INTO Character (name, level, strenght, stamina, stealth, rizz, gender, RaceId, SocialStatusId, FactionId)"
"VALUES"
"   ('Placeholder', 1, 1, 1, 1, 1, 1, 1, 1, 1);";

const char* insert_item_table =
"INSERT INTO Item (item_name, item_type, item_type_type, item_material, item_price, item_availability)"
"VALUES"
"   ('helmet', 1, 1, 1, 5, 1),"
"   ('chest', 2, 2, 1, 8, 1),"
"   ('legs', 3, 1, 1, 7, 1),"
"   ('boots', 4, 2, 1, 4, 1),"
"   ('sword', 5, 5, 1, 2, 1),"
"   ('shield', 5, 6, 1, 4, 1);";

void database_init_tables(GameData* g) {
    
    if (sqlite3_exec(g->db, create_race_table, NULL, NULL, NULL) != SQLITE_OK) {
        LOG_SQLITE3_ERROR(g->db);
        return;
    }

    if (sqlite3_exec(g->db, create_socialstatus_table, NULL, NULL, NULL) != SQLITE_OK) {
        LOG_SQLITE3_ERROR(g->db);
        return;
    }
    
    if (sqlite3_exec(g->db, create_faction_table, NULL, NULL, NULL) != SQLITE_OK) {
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
    
    if (sqlite3_exec(g->db, insert_race_table, NULL, NULL, NULL) != SQLITE_OK) {
        LOG_SQLITE3_ERROR(g->db);
        return;
    }
    
    if (sqlite3_exec(g->db, insert_socialstatus_table, NULL, NULL, NULL) != SQLITE_OK) {
        LOG_SQLITE3_ERROR(g->db);
        return;
    }

    if (sqlite3_exec(g->db, insert_faction_table, NULL, NULL, NULL) != SQLITE_OK) {
        LOG_SQLITE3_ERROR(g->db);
        return;
    }

    if (sqlite3_exec(g->db, insert_character_table, NULL, NULL, NULL) != SQLITE_OK) {
        LOG_SQLITE3_ERROR(g->db);
        return;
    }
    
    if (sqlite3_exec(g->db, insert_item_table, NULL, NULL, NULL) != SQLITE_OK) {
        LOG_SQLITE3_ERROR(g->db);
        return;
    }
}

void database_end(GameData* g) {
    sqlite3_close(g->db);
}
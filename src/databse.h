#pragma once

#include "game.h"

void database_start(GameData* g);
void database_init_tables(GameData* g);
void database_end(GameData* g);
void database_create_user(GameData* g);
void database_save_character(GameData* g);
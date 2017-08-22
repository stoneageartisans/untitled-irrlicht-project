/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#ifndef DATABASE_H
#define DATABASE_H

#define DB_FILENAME "database.sqlite"

#include "queries.h"

#include <irrlicht.h>
#include <sqlite3.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Database
{    
    public:
        Database();
        ~Database();
        array<map<stringc, stringc>*>* multi_select(const char* QUERY, s32 ID = 0);
        map<stringc, stringc>* single_select(const char* QUERY, s32 ID = 0);
        void simple_update(const char* QUERY, s32 ID = 0);
        void update_last(s32 USER_ID);
        
    private:
        sqlite3* database;
        sqlite3_stmt* statement;
        void exit();
        void initialize();        
};

#endif // DATABASE_H

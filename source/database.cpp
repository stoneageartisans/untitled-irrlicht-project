/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#include "database.h"

#include <iostream>
#include <stddef.h>
#include <stdlib.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Database::Database()
{
    initialize();
}

Database::~Database()
{
    exit();
}

void Database::exit()
{
    if(database != NULL)
    {
        sqlite3_close_v2(database);
    }    
    sqlite3_shutdown();
}

void Database::initialize()
{
    sqlite3_initialize();
    database = NULL;
    statement = NULL;
    
    try
    {
        sqlite3_open_v2(DB_FILENAME, &database, SQLITE_OPEN_READWRITE, NULL);
    }
    catch(...)
    {
        std::cout << "ERROR: Unable to read database.sqlite file" << std::endl;
    }
}

array<map<stringc, stringc>*>* Database::multi_select(const char* QUERY, s32 ID)
{    
    array<map<stringc, stringc>*>* row_set = new array<map<stringc, stringc>*>();
    
    stringc* sql = new stringc(QUERY);
    *sql += ID;
    *sql += ";";
    
    if(database != NULL)
    {
        sqlite3_prepare_v2(database, sql->c_str(), strlen(sql->c_str()), &statement, NULL);
        
        while(sqlite3_step(statement) == SQLITE_ROW)
        {            
            map<stringc, stringc>* row = new map<stringc, stringc>();
            
            for(s32 i = 0; i < sqlite3_column_count(statement); i++)
            {
                stringc* key = new stringc(sqlite3_column_name(statement, i));
                stringc* value = new stringc(sqlite3_column_text(statement, i));        
                row->insert(stringc(key->c_str()), stringc(value->c_str()));
                std::cout << key->c_str() << " = " << value->c_str() << std::endl;
                delete key;
                delete value;
            }
            
            row_set->push_back(row);
        }               
    }
    
    delete sql; 
    
    return row_set;
}

map<stringc, stringc>* Database::single_select(const char* QUERY, s32 ID)
{    
    map<stringc, stringc>* row = new map<stringc, stringc>();
    
    stringc* sql = new stringc(QUERY);
    *sql += ID;
    *sql += ";";
    
    if(database != NULL)
    {
        sqlite3_prepare_v2(database, sql->c_str(), strlen(sql->c_str()), &statement, NULL);

        if(sqlite3_step(statement) != SQLITE_ROW)
        {
            std::cout << "ERROR: Query failed." << std::endl;
        }
        else
        {
            for(u32 i = 0; i < sqlite3_column_count(statement); i++)
            {
                stringc* key = new stringc(sqlite3_column_name(statement, i));
                stringc* value = new stringc(sqlite3_column_text(statement, i));        
                row->insert(stringc(key->c_str()), stringc(value->c_str()));
                std::cout << key->c_str() << " = " << value->c_str() << std::endl;
                delete key;
                delete value;
            }
        }               
    }
    
    delete sql; 
    
    return row;
}

void Database::simple_update(const char* QUERY, s32 ID)
{
    stringc* sql = new stringc(QUERY);
    *sql += ID;
    *sql += ";";
    
    if(database != NULL)
    {
        sqlite3_prepare_v2(database, sql->c_str(), strlen(sql->c_str()), &statement, NULL);

        if(sqlite3_step(statement) != SQLITE_DONE)
        {
            std::cout << "ERROR: Update failed." << std::endl;
        }
    }

    delete sql;
}

void Database::update_last(s32 USER_ID)
{
    stringc* sql = new stringc("UPDATE last SET LAST_USER_ID = ");
    *sql += USER_ID;
    *sql += " WHERE ID = 0;";
    
    if(database != NULL)
    {
        sqlite3_prepare_v2(database, sql->c_str(), strlen(sql->c_str()), &statement, NULL);

        if(sqlite3_step(statement) != SQLITE_DONE)
        {
            std::cout << "ERROR: Update failed." << std::endl;
        }
    }
    
    delete sql;
}

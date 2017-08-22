/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#include "user.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

User::User(Database* DATABASE, s32 ID)
{
    initialize(DATABASE, ID);
}

User::~User()
{
    delete database;
}

Character* User::get_character()
{
    return character;
}

s32 User::get_id()
{
    return id;
}

void User::initialize(Database* DATABASE, s32 ID)
{
    database = DATABASE;
    id = ID;
    
    character = new Character(database, id);
}

void User::update()
{
    //
}

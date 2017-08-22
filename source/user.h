/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#ifndef USER_H
#define USER_H

#include "character.h"
#include "database.h"

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class User
{
    public:
        User(Database* DATABASE, s32 ID);
        ~User();
        Character* get_character();
        s32 get_id();
        void update();

    private:
        Character* character;
        Database* database;
        s32 id;
        void initialize(Database* DATABASE, s32 ID);
};

#endif // USER_H

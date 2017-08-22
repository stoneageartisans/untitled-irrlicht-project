/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#ifndef WORLD_H
#define WORLD_H

#include "database.h"
#include "time.h"

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class World
{
    public:        
        Time* time;
        World(Time* TIME, Database* DATABASE, s32 ID = 0);
        ~World();
        s32 get_id();
        void update();
        
    private:
        Database* database;
        s32 id;
        void initialize(Time* TIME, Database* DATABASE, s32 ID);
};

#endif // WORLD_H

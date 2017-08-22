/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#include "world.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

World::World(Time* TIME, Database* DATABASE, s32 ID)
{
    initialize(TIME, DATABASE, ID);
}

World::~World()
{
    delete database;
}

s32 World::get_id()
{
    return id;
}

void World::initialize(Time* TIME, Database* DATABASE, s32 ID)
{
    time = TIME;
    database = DATABASE;
    id = ID;
}

void World::update()
{
    //
}
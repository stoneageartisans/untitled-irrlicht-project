/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "database.h"

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Character
{    
    public:
        Character(Database* DATABASE, s32 ID);
        ~Character();
        vector3d<f32>* get_coordinates();
        s32 get_id();
        stringc* get_name();
        bool is_moving();
        void set_coordinates(f32 X, f32 Y, f32 Z);
        void set_coordinates(vector3d<f32> COORDINATES);
        void set_moving(bool VALUE);
        void update();
    private:
        vector3d<f32>* coordinates;
        Database* database;
        s32 id;
        bool moving;
        stringc* name;
        void initialize(Database* DATABASE, s32 ID);
};

#endif // CHARACTER_H

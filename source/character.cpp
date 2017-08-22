/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#include "character.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Character::Character(Database* DATABASE, s32 ID)
{
    initialize(DATABASE, ID);
}

Character::~Character()
{
    delete coordinates;
    delete database;
    delete name;
}

vector3d<f32>* Character::get_coordinates()
{
    return coordinates;
}

s32 Character::get_id()
{
    return id;
}

stringc* Character::get_name()
{
    return name;
}

void Character::initialize(Database* DATABASE, s32 ID)
{
    database = DATABASE;
    id = ID;
    moving = true; // temporarily set to true for testing; default will be false
    
    map<stringc, stringc>* character_data = database->single_select(GET_CHARACTER);
    if(!character_data->empty())
    {
        name = new stringc((*character_data)["NAME"]);
        
        stringc* x = new stringc((*character_data)["X"]);
        stringc* y = new stringc((*character_data)["Y"]);
        stringc* z = new stringc((*character_data)["Z"]);      
        coordinates = new vector3d<f32>(atof(x->c_str()), atof(y->c_str()), atof(z->c_str()));        
        delete x;
        delete y;
        delete z;
    }
    delete character_data;
}

bool Character::is_moving()
{
    return moving;
}

void Character::set_coordinates(f32 X, f32 Y, f32 Z)
{
    coordinates->set(X, Y, Z);
}

void Character::set_coordinates(vector3d<f32> COORDINATES)
{
    coordinates->set(COORDINATES);
}

void Character::set_moving(bool VALUE)
{
    moving = VALUE;
}

void Character::update()
{
    //
}
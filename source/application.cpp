/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#include "application.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Application::Application()
{
    initialize();
}

Application::~Application()
{
    delete database;
    delete irrlicht_device;
    delete time;
    delete ui;
    delete user;
    delete world;
}

void Application::exit()
{
    database->simple_update(UPDATE_PROPERTIES, user->get_id());
    database->update_last(user->get_id());
    irrlicht_device->drop();
}

void Application::initialize()
{
    map<stringc, stringc>* files;
    map<stringc, stringc>* irrlicht_settings;
    map<stringc, stringc>* properties;
        
    database = new Database();
    
    load_user();
    
    properties = database->single_select(GET_PROPERTIES, user->get_id());    
    files = database->single_select(GET_FILES, user->get_id());    
    irrlicht_settings = database->single_select(GET_IRRLICHT_SETTINGS, user->get_id());        
    
    time = new Time();    
    world = new World(time, database);    
    ui = new Ui(files, irrlicht_settings);
    ui->user = user;
    ui->time = time;    
    
    delete properties;
    delete irrlicht_settings;
    delete files;
    
    irrlicht_device = ui->irrlicht_device;
}

void Application::load_user()
{    
    map<stringc, stringc>* last = database->single_select(GET_LAST);    

    if(last->find("LAST_USER_ID") != 0)
    {
        stringc* value = new stringc((*last)["LAST_USER_ID"]);
        user = new User(database, atoi(value->c_str()));
        delete value;        
    }
    else
    {
        user = new User(database, 0);
    }
    
    delete last;
}

void Application::process_events()
{
    switch(ui->application_event)
    {
        case EVENT_ADVANCE:
            time->advance_time(ui->time_unit);
            world->update();
            ui->application_event = EVENT_NONE;
            break;
    }
}

void Application::run()
{    
	while(irrlicht_device->run())
    {
        if(irrlicht_device->isWindowFocused()) // or isWindowMinimized() ?
        {
            process_events();
            ui->update();
        }
        else
        {
            irrlicht_device->yield();
        }
    }
    
    exit();
}

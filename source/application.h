/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "database.h"
#include "time.h"
#include "ui.h"
#include "user.h"
#include "world.h"

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Application
{
    public:
        Application();
        ~Application();
        void run();

    private:
	Database* database;
        IrrlichtDevice* irrlicht_device;
        Time* time;
        s32 timer_start;
	Ui* ui;
        User* user;
        World* world;       
        void exit();        
        void initialize();
        void load_user();
        void process_events();
};

#endif // APPLICATION_H

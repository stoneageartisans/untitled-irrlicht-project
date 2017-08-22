/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#ifndef UI_H
#define UI_H

#include "time.h"
#include "user.h"

#include <irrlicht.h>

// Application Events
#define EVENT_NONE          0
#define EVENT_ADVANCE       1

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Ui : public IEventReceiver
{    
    public:        
        s32 application_event;
        IrrlichtDevice* irrlicht_device;
        Time* time;
        s32 time_unit;
        User* user;
        Ui(map<stringc, stringc>* FILES, map<stringc, stringc>* IRRLICHT_SETTINGS);
        ~Ui();
        bool OnEvent(const SEvent& EVENT);
        void update();

    private:        
        bool back_buffer_state;
        IGUIButton* button_advance;
        IGUIButton* button_exit;
        IGUIButton* button_minimize;
        ICameraSceneNode* camera_overhead;
        SColor* color_background;
        IGUIComboBox* combobox_time_unit;
        map<s32, const wchar_t*>* day_names;        
        IGUIEnvironment* gui_environment;
        IMeshSceneNode* mesh_node_plane;
        s32 mouse_x;
        s32 mouse_x_previous;
        s32 mouse_y;        
        s32 mouse_y_previous;
        ISceneManager* scene_manager;
        map<s32, const wchar_t*>* season_names;
        IGUIStaticText* statictext_clock;
        IGUIStaticText* statictext_coordinate_x;
        IGUIStaticText* statictext_coordinate_y;
        IGUIStaticText* statictext_coordinate_z;
        IGUIStaticText* statictext_date;
        IGUIStaticText* statictext_day;
        IGUIStaticText* statictext_fps;
        IGUIStaticText* statictext_season;
        stringw* stringw_clock;
        stringw* stringw_coordinate;
        stringw* stringw_date;
        stringw* stringw_day;
        stringw* stringw_fps;
        stringw* stringw_season;
        ITerrainSceneNode* terrain_node;
        map<s32, const wchar_t*>* time_units;
        IVideoDriver* video_driver;
        s32 window_height;
        s32 window_width;        
        bool z_buffer_state;
        IGUIElement* add_widget(EGUI_ELEMENT_TYPE WIDGET_TYPE, s32 X, s32 Y, s32 WIDTH, s32 HEIGHT, const wchar_t* TEXT, s32 ID = -1);
        void exit();
        const wchar_t* format_digits(s32 TIME_VALUE, s32 NUM_OF_DIGITS = 2);        
        void initialize(map<stringc, stringc>* FILES, map<stringc, stringc>* IRRLICHT_SETTINGS);
        void update_clock();
        void update_coordinates();
        void update_date();
        void update_fps();
};

#endif // UI_H

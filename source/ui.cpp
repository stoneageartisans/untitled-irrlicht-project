/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#include "ui.h"
#include "user.h"

// Irrlicht Settings
#define FULLSCREEN          true
#define WINDOWED            false
#define USE_BACK_BUFFER     true
#define NO_BACK_BUFFER      false
#define USE_Z_BUFFER        true
#define NO_Z_BUFFER         false

// Irrlicht Colors
#define COLOR_TRANSPARENT   SColor(0, 0, 0, 0)
#define COLOR_BLACK         SColor(255, 0, 0, 0)
#define COLOR_WHITE         SColor(255, 255, 255, 255)
#define COLOR_RED           SColor(255, 255, 0, 0)
#define COLOR_ORANGE        SColor(255, 255, 127, 0)
#define COLOR_YELLOW        SColor(255, 255, 255, 0)
#define COLOR_GREEN         SColor(255, 0, 255, 0)
#define COLOR_BLUE          SColor(255, 0, 0, 255)
#define COLOR_PURPLE        SColor(255, 127, 0, 255)
#define COLOR_PINK          SColor(255, 255, 0, 255)
#define COLOR_GRAY          SColor(255, 127, 127, 127)
#define COLOR_LTGRAY        SColor(255, 191, 191, 191)
#define COLOR_DKGRAY        SColor(255, 63, 63, 63)
#define COLOR_BROWN         SColor(255, 127, 63, 0)
#define COLOR_MATGRAY       SColor(255, 89, 87, 91)

// Fonts
#define FONT_SMALL      1
#define FONT_MEDIUM     2
#define FONT_LARGE      3

// Widget IDs
#define BUTTON_EXIT             1
#define BUTTON_MINIMIZE         2
#define BUTTON_ADVANCE          3
#define COMBOBOX_TIME_UNIT      4
#define COMBOBOX_TIME_AMOUNT    5

// Widget labels and/or text
#define LABEL_NONE          L""
#define LABEL_EXIT          L"Exit"
#define LABEL_MINIMIZE      L"Minimize"
#define LABEL_ADVANCE       L"Advance"
#define TEXT_TIME_UNIT      L"Time Unit"
#define TEXT_TIME_AMOUNT    L"Time Amount"

// Top Widget Bar
#define TOTAL_TOP_WIDGETS   8
#define TOTAL_TIME_UNITS    9
#define TOTAL_TIME_AMOUNTS  11
#define SLOT_EXIT           7
#define SLOT_MINIMIZE       6
#define SLOT_TIME_UNIT      5
#define SLOT_ADVANCE        4

// Upper Info Display
#define TOTAL_UPPER_SECTIONS    5
#define SECTION_FPS             4
#define SECTION_CLOCK           0
#define SECTION_DAY             1
#define SECTION_DATE            2
#define SECTION_SEASON          3

// Lower Info Display
#define TOTAL_LOWER_SECTIONS    3
#define SECTION_COORDINATE_X    0
#define SECTION_COORDINATE_Y    1
#define SECTION_COORDINATE_Z    2

// Cameras
#define CAMERA_OVERHEAD         1
#define CAMERA_FIRST_PERSON     2
#define CAMERA_TURN_SPEED       100.0f
#define CAMERA_MOVE_SPEED       0.5f
#define CAMERA_VERTICAL_MOVE    true
#define CAMERA_NO_VERTICAL      false
#define CAMERA_JUMP_SPEED       0.0f
#define CAMERA_INVERT_MOUSE     true
#define CAMERA_NO_INVERT        false
#define CAMERA_ACTIVE           true
#define CAMERA_INACTIVE         false
#define CAMERA_ROTATE_SPEED     0.0f
#define CAMERA_ZOOM_SPEED       1000.0f 
#define CAMERA_TRANSLATE_SPEED  1000.0f
#define CAMERA_DISTANCE         500.0f

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Ui::Ui(map<stringc, stringc>* FILES, map<stringc, stringc>* IRRLICHT_SETTINGS)
{
	initialize(FILES, IRRLICHT_SETTINGS);
}

Ui::~Ui()
{
    delete color_background;
}

IGUIElement* Ui::add_widget(EGUI_ELEMENT_TYPE WIDGET_TYPE, s32 X, s32 Y, s32 WIDTH, s32 HEIGHT, const wchar_t* TEXT, s32 ID)
{
    IGUIElement* widget;
    
    vector2d<s32>* position = new vector2d<s32>(X, Y);
    dimension2d<u32>* size = new dimension2d<u32>(WIDTH, HEIGHT);            
    rect<s32>* rectangle = new rect<s32>(*position, *size);
    
    switch(WIDGET_TYPE)
    {
        case EGUIET_BUTTON:
            widget = gui_environment->addButton(*rectangle, 0, ID, TEXT);            
            break;
        case EGUIET_STATIC_TEXT:
            widget = gui_environment->addStaticText(TEXT, *rectangle, false, false, 0, ID, false);
            break;
        case EGUIET_COMBO_BOX:
            widget = gui_environment->addComboBox(*rectangle, 0, ID);
            break;
        case EGUIET_SPIN_BOX:
            widget = gui_environment->addSpinBox(TEXT, *rectangle, false, 0, ID);
            break;
    }
    
    delete position;
    delete size;
    delete rectangle;
    
    return widget;
}

void Ui::exit()
{
    irrlicht_device->setEventReceiver(0);
    irrlicht_device->closeDevice();
    irrlicht_device->run();    
}

const wchar_t* Ui::format_digits(s32 TIME_VALUE, s32 NUM_OF_DIGITS)
{
    stringw* value = new stringw();
    const wchar_t* result;
    
    switch(NUM_OF_DIGITS)
    {
        case 2:
            if(TIME_VALUE < 10)
            {
                *value += "0";
            }
            break;
        case 4:
            if(TIME_VALUE < 1000)
            {
                *value += "0";
                if(TIME_VALUE < 100)
                {
                    *value += "0";
                    if(TIME_VALUE < 10)
                    {
                        *value += "0";
                    }
                }                
            }
            break;
    }    
    *value += TIME_VALUE;    
    result = value->c_str();    
    delete value;
    
    return result;
}

void Ui::initialize(map<stringc, stringc>* FILES, map<stringc, stringc>* IRRLICHT_SETTINGS)
{
    // Get Irrlicht ready
    bool display_type; 
    E_DRIVER_TYPE driver_type;
    s32 bit_depth;
    s32 font_size;
    
    if(IRRLICHT_SETTINGS->find("DRIVER_TYPE") != 0)
    {
        stringc* key = new stringc((*IRRLICHT_SETTINGS)["DRIVER_TYPE"]);
        switch(atoi(key->c_str()))
        {
            case 0:
                driver_type = EDT_NULL;
                break;
            case 1:
                driver_type = EDT_SOFTWARE;
                break;
            case 2:
                driver_type = EDT_BURNINGSVIDEO;
                break;
            case 5:
                driver_type = EDT_OPENGL;
                break;
            default:
                driver_type = EDT_OPENGL;
                break;
        }
        delete key;
    }
    else
    {
        driver_type = EDT_OPENGL;
    }        
    
    if(IRRLICHT_SETTINGS->find("WINDOW_WIDTH") != 0)
    {
        stringc* key = new stringc((*IRRLICHT_SETTINGS)["WINDOW_WIDTH"]);
        window_width = atoi(key->c_str());
        delete key;
    }
    else
    {
        window_width = 1024;
    }
    
    if(IRRLICHT_SETTINGS->find("WINDOW_HEIGHT") != 0)
    {
        stringc* key = new stringc((*IRRLICHT_SETTINGS)["WINDOW_HEIGHT"]);
        window_height = atoi(key->c_str());
        delete key;
    }
    else
    {
        window_height = 600;
    }
    
    if(IRRLICHT_SETTINGS->find("BIT_DEPTH") != 0)
    {
        stringc* key = new stringc((*IRRLICHT_SETTINGS)["BIT_DEPTH"]);
        bit_depth = atoi(key->c_str());
        delete key;
    }
    else
    {
        bit_depth = 32;
    }
    
    if(IRRLICHT_SETTINGS->find("DISPLAY_TYPE") != 0)
    {
        stringc* key = new stringc((*IRRLICHT_SETTINGS)["DISPLAY_TYPE"]);
        switch(atoi(key->c_str()))
        {
           case 0:
               display_type = WINDOWED;
               break;
           case 1:
               display_type = FULLSCREEN;
               break;
           default:
               display_type = WINDOWED;
               break;
        }
        delete key;
    }
    else
    {
        display_type = WINDOWED;
    }
    
    irrlicht_device = createDevice(driver_type,
                                   dimension2d<u32>(window_width, window_height),
                                   bit_depth,
                                   display_type
                                   );
    irrlicht_device->setEventReceiver(this);
    irrlicht_device->setResizable(false);
    
    if(IRRLICHT_SETTINGS->find("WINDOW_CAPTION") != 0)
    {
        stringw* key = new stringw(stringc((*IRRLICHT_SETTINGS)["WINDOW_CAPTION"]));
        irrlicht_device->setWindowCaption(key->c_str());
        delete key;
    }
    else
    {
        irrlicht_device->setWindowCaption(L"Is your 'database.sqlite' file missing?");
    }
    //irrlicht_device->setResizable(true);
    
    if(FILES->find("RESOURCES") != 0)
    {
        stringc* key = new stringc((*FILES)["RESOURCES"]);
        if(!key->empty())
        {
            irrlicht_device->getFileSystem()->addFileArchive(key->c_str());
        }
    }
    
    video_driver = irrlicht_device->getVideoDriver();
    scene_manager = irrlicht_device->getSceneManager();
    gui_environment = irrlicht_device->getGUIEnvironment();
    
    if(IRRLICHT_SETTINGS->find("BACK_BUFFER") != 0)
    {
        stringc* key = new stringc((*IRRLICHT_SETTINGS)["BACK_BUFFER"]);
        switch(atoi(key->c_str()))
        {
            case 0:
                back_buffer_state = NO_BACK_BUFFER;
                break;
            case 1:
                back_buffer_state = USE_BACK_BUFFER;
                break;
            default:
                back_buffer_state = USE_BACK_BUFFER;
                break;
        }
        delete key;
    }
    else
    {
        back_buffer_state = USE_BACK_BUFFER;
    }
    
    if(IRRLICHT_SETTINGS->find("Z_BUFFER") != 0)
    {
        stringc* key = new stringc((*IRRLICHT_SETTINGS)["Z_BUFFER"]);
        switch(atoi(key->c_str()))
        {
            case 0:
                z_buffer_state = NO_Z_BUFFER;
                break;
            case 1:
                z_buffer_state = USE_Z_BUFFER;
                break;
            default:
                z_buffer_state = USE_Z_BUFFER;
                break;
        }
        delete key;
    }
    else
    {
        z_buffer_state = USE_Z_BUFFER;
    }
    
    if(IRRLICHT_SETTINGS->find("FONT_SIZE") != 0)
    {
        stringc* key = new stringc((*IRRLICHT_SETTINGS)["FONT_SIZE"]);
        font_size = atoi(key->c_str());
        delete key;
    }
    else
    {
        font_size = FONT_MEDIUM;
    }
    
    // Create day names
    day_names = new map<s32, const wchar_t*>();
    day_names->insert(MONDAY, L"Monday");
    day_names->insert(TUESDAY, L"Tuesday");
    day_names->insert(WEDNESDAY, L"Wednesday");
    day_names->insert(THURSDAY, L"Thursday");
    day_names->insert(FRIDAY, L"Friday");
    day_names->insert(SATURDAY, L"Saturday");
    day_names->insert(SUNDAY, L"Sunday");
    
    // Create season names
    season_names = new map<s32, const wchar_t*>();
    season_names->insert(SPRING, L"Spring");
    season_names->insert(SUMMER, L"Summer");
    season_names->insert(AUTUMN, L"Autumn");
    season_names->insert(WINTER, L"Winter");
    
    // Create time unit names
    time_units = new map<s32, const wchar_t*>();
    time_units->insert(UNIT_NONE, TEXT_TIME_UNIT);
    time_units->insert(UNIT_SECOND, L"Second");
    time_units->insert(UNIT_MINUTE, L"Minute");
    time_units->insert(UNIT_HOUR, L"Hour");
    time_units->insert(UNIT_DAY, L"Day");
    time_units->insert(UNIT_WEEK, L"Week");
    time_units->insert(UNIT_MONTH, L"Month");
    time_units->insert(UNIT_SEASON, L"Season");
    time_units->insert(UNIT_YEAR, L"Year");
    
    // Set the fill color for the 3D background
    color_background = new COLOR_BLACK;
    
    // Initialize some values
    application_event = 0;
    mouse_x = 0;
    mouse_x_previous = -1;
    mouse_y = 0;
    mouse_y_previous = -1;
    stringw_clock = new stringw(L"XX:XX:XX");
    stringw_coordinate = new stringw(L"X:  X.XXXXXX");
    stringw_date = new stringw(L"XXXX-XX-XX");
    stringw_day = new stringw(L"XXXXXXXXX");
    stringw_fps = new stringw(L"XXXX");
    stringw_season = new stringw(L"XXXXXX");
    time_unit = UNIT_NONE;
    
    // Create gui skin
    IGUISkin* gui_skin = gui_environment->getSkin();
    
    // Modify the background transparency of combo boxes (and other widgets unfortunately!)
    SColor* color = new SColor(gui_skin->getColor(EGDC_3D_HIGH_LIGHT));
    color->setAlpha(127);
    gui_skin->setColor(EGDC_3D_HIGH_LIGHT, *color);
    
    // Set up the Font
    IGUIFont* font_main;
    if(FILES->find("FONT_SMALL") != 0)
    {
        stringc* key;
        switch(font_size)
        {
            case FONT_SMALL:
                key = new stringc((*FILES)["FONT_SMALL"]);            
                break;
            case FONT_MEDIUM:
                key = new stringc((*FILES)["FONT_MEDIUM"]);
                break;
            case FONT_LARGE:
                key = new stringc((*FILES)["FONT_LARGE"]);
                break;
            default:
                key = new stringc((*FILES)["FONT_MEDIUM"]);
                break;
        }
        if(key->empty() || irrlicht_device->getFileSystem()->getFileArchiveCount() == 0)
        {
            font_main = gui_environment->getBuiltInFont();        
        }
        else
        {        
            font_main = gui_environment->getFont(key->c_str());        
        }
        delete key;
    }
    else
    {
        font_main = gui_environment->getBuiltInFont();
    }        
    gui_skin->setFont(font_main);
    
    // Set the margin size for the gui
    s32 gui_margin = font_main->getDimension(L"X").Width;
    
    // Set the size of the gui buttons
    s32 top_bar_widget_height = font_main->getDimension(L"X").Height * 1.5;
    s32 top_bar_widget_width = window_width / TOTAL_TOP_WIDGETS;
    
    // Create top button bar coordinates    
    s32 top_bar_widget_x[TOTAL_TOP_WIDGETS];
    for(u32 i = 0; i < TOTAL_TOP_WIDGETS; i ++)
    {
        top_bar_widget_x[i] = top_bar_widget_width * i;
    }
    s32 top_bar_widget_y = 0;
    
    // Create exit button on the top widget bar
    button_exit = (IGUIButton*) add_widget(EGUIET_BUTTON, top_bar_widget_x[SLOT_EXIT], top_bar_widget_y, top_bar_widget_width, top_bar_widget_height, LABEL_EXIT, BUTTON_EXIT);
    
    // Create minimize button on the top widget bar
    button_minimize = (IGUIButton*) add_widget(EGUIET_BUTTON, top_bar_widget_x[SLOT_MINIMIZE], top_bar_widget_y, top_bar_widget_width, top_bar_widget_height, LABEL_MINIMIZE, BUTTON_MINIMIZE);
    
    // Create time advance button on the top widget bar
    button_advance = (IGUIButton*) add_widget(EGUIET_BUTTON, top_bar_widget_x[SLOT_ADVANCE], top_bar_widget_y, top_bar_widget_width, top_bar_widget_height, LABEL_ADVANCE, BUTTON_ADVANCE);
    
    // Create time unit combox box on the top widget bar
    combobox_time_unit =  (IGUIComboBox*) add_widget(EGUIET_COMBO_BOX, top_bar_widget_x[SLOT_TIME_UNIT], top_bar_widget_y, top_bar_widget_width, top_bar_widget_height, LABEL_NONE, COMBOBOX_TIME_UNIT);
    combobox_time_unit->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
    for(u32 i = 0; i < TOTAL_TIME_UNITS; i++)
    {
        combobox_time_unit->addItem((*time_units)[i], i);
    }
    combobox_time_unit->setMaxSelectionRows(TOTAL_TIME_UNITS);
    combobox_time_unit->setSelected(UNIT_NONE);
    
    // Set the size of the upper info display sections
    s32 upper_section_height = font_main->getDimension(L"X").Height * 2;
    s32 upper_section_width = (window_width - gui_margin - gui_margin) / TOTAL_UPPER_SECTIONS;
    
    // Create the upper info display coordinates   
    s32 upper_section_x[TOTAL_UPPER_SECTIONS];
    for(u32 i = 0; i < TOTAL_UPPER_SECTIONS; i ++)
    {
        upper_section_x[i] = gui_margin + (upper_section_width * i);
    }
    s32 upper_section_y = top_bar_widget_height;
    
    // Create the FPS counter on the upper info display
    statictext_fps = (IGUIStaticText*) add_widget(EGUIET_STATIC_TEXT, upper_section_x[SECTION_FPS], upper_section_y, upper_section_width, upper_section_height, stringw_fps->c_str());
    statictext_fps->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
    statictext_fps->setOverrideColor(COLOR_LTGRAY);
    
    // Create the Clock on the upper info display
    statictext_clock = (IGUIStaticText*) add_widget(EGUIET_STATIC_TEXT, upper_section_x[SECTION_CLOCK], upper_section_y, upper_section_width, upper_section_height, stringw_clock->c_str());
    statictext_clock->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
    statictext_clock->setOverrideColor(COLOR_LTGRAY);
    
    // Create the Day on the upper info display
    statictext_day = (IGUIStaticText*) add_widget(EGUIET_STATIC_TEXT, upper_section_x[SECTION_DAY], upper_section_y, upper_section_width, upper_section_height, stringw_day->c_str());
    statictext_day->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
    statictext_day->setOverrideColor(COLOR_LTGRAY);
    
    // Create the Date on the upper info display
    statictext_date = (IGUIStaticText*) add_widget(EGUIET_STATIC_TEXT, upper_section_x[SECTION_DATE], upper_section_y, upper_section_width, upper_section_height, stringw_date->c_str());
    statictext_date->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
    statictext_date->setOverrideColor(COLOR_LTGRAY);
    
    // Create the Season on the upper info display
    statictext_season = (IGUIStaticText*) add_widget(EGUIET_STATIC_TEXT, upper_section_x[SECTION_SEASON], upper_section_y, upper_section_width, upper_section_height, stringw_season->c_str());
    statictext_season->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
    statictext_season->setOverrideColor(COLOR_LTGRAY);
    
    // Set the size of the lower info display sections
    s32 lower_section_height = font_main->getDimension(L"X").Height * 2;
    s32 lower_section_width = (window_width - gui_margin - gui_margin) / TOTAL_LOWER_SECTIONS;
    
    // Create the lower info display coordinates   
    s32 lower_section_x[TOTAL_LOWER_SECTIONS];
    for(u32 i = 0; i < TOTAL_LOWER_SECTIONS; i ++)
    {
        lower_section_x[i] = gui_margin + (lower_section_width * i);
    }
    s32 lower_section_y = window_height - lower_section_height;
    
    // Create the Coordinates on the lower info display
    statictext_coordinate_x = (IGUIStaticText*) add_widget(EGUIET_STATIC_TEXT, lower_section_x[SECTION_COORDINATE_X], lower_section_y, lower_section_width, lower_section_height, stringw_coordinate->c_str());
    statictext_coordinate_x->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
    statictext_coordinate_x->setOverrideColor(COLOR_LTGRAY);
    
    statictext_coordinate_y = (IGUIStaticText*) add_widget(EGUIET_STATIC_TEXT, lower_section_x[SECTION_COORDINATE_Y], lower_section_y, lower_section_width, lower_section_height, stringw_coordinate->c_str());
    statictext_coordinate_y->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
    statictext_coordinate_y->setOverrideColor(COLOR_LTGRAY);
    
    statictext_coordinate_z = (IGUIStaticText*) add_widget(EGUIET_STATIC_TEXT, lower_section_x[SECTION_COORDINATE_Z], lower_section_y, lower_section_width, lower_section_height, stringw_coordinate->c_str());
    statictext_coordinate_z->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
    statictext_coordinate_z->setOverrideColor(COLOR_LTGRAY);
    
    // Create the camera    
    camera_overhead = scene_manager->addCameraSceneNodeMaya(0,
                                                            CAMERA_ROTATE_SPEED,
                                                            CAMERA_ZOOM_SPEED,
                                                            CAMERA_TRANSLATE_SPEED,
                                                            CAMERA_OVERHEAD,
                                                            CAMERA_DISTANCE,
                                                            CAMERA_ACTIVE
                                                            );

    // Create plane
    if(FILES->find("MESH_01") != 0)
    {
        stringc* key = new stringc((*FILES)["MESH_01"]);
        if(!key->empty())
        {
            mesh_node_plane = scene_manager->addMeshSceneNode(scene_manager->getMesh(key->c_str()));
            mesh_node_plane->setPosition(vector3d<f32>(0, 0, 0));
            mesh_node_plane->setRotation(vector3d<f32>(0, -90, 0));
            mesh_node_plane->setMaterialFlag(EMF_LIGHTING, false);
        }
        delete key;
    }
    
    if(FILES->find("TEXTURE_01") != 0)
    {
        stringc* key = new stringc((*FILES)["TEXTURE_01"]);
        if(!key->empty())
        {
            mesh_node_plane->setMaterialTexture(0, video_driver->getTexture(key->c_str()));
        }
        delete key;
    }
}

bool Ui::OnEvent(const SEvent& EVENT)
{
    bool return_value = false;

    switch(EVENT.EventType)
    {
        case EET_MOUSE_INPUT_EVENT:
            switch(EVENT.MouseInput.Event)
            {
                case EMIE_MOUSE_MOVED:
                    mouse_x = EVENT.MouseInput.X;
                    mouse_y = EVENT.MouseInput.Y;
                    break;
                case EMIE_LMOUSE_PRESSED_DOWN:
                    // nothing yet
                    break;
                case EMIE_LMOUSE_LEFT_UP:
                    // nothing yet
                    break;
                case EMIE_RMOUSE_PRESSED_DOWN:
                    irrlicht_device->getCursorControl()->setVisible(false);
                    break;
                case EMIE_RMOUSE_LEFT_UP:
                    irrlicht_device->getCursorControl()->setVisible(true);
                    break;
                case EMIE_MMOUSE_PRESSED_DOWN:
                    irrlicht_device->getCursorControl()->setVisible(false);
                    break;
                case EMIE_MMOUSE_LEFT_UP:
                    irrlicht_device->getCursorControl()->setVisible(true);
                    break;
                default:
                    break;
            }
            break;
		case EET_KEY_INPUT_EVENT:
            switch(EVENT.KeyInput.Key)
            {
                case KEY_ESCAPE:
                    if(!EVENT.KeyInput.PressedDown)
                    {
                        //exit(); // This is now being done via a button
                        //return_value = true;
                    }
                    break;
                default:
                    break;
            }
            break;
        case EET_GUI_EVENT:
            switch(EVENT.GUIEvent.EventType)
            {
                case EGET_BUTTON_CLICKED:
                    switch(EVENT.GUIEvent.Caller->getID())
                    {
                        case BUTTON_EXIT:
                            exit();
                            return_value = true;
                            break;
                        case BUTTON_MINIMIZE:
                            irrlicht_device->minimizeWindow();
                            return_value = true;
                            break;
                        case BUTTON_ADVANCE:
                            application_event = EVENT_ADVANCE;
                            return_value = true;
                            break;
                    }
                    break;
                case EGET_COMBO_BOX_CHANGED:
                    switch(EVENT.GUIEvent.Caller->getID())
                    {
                        case COMBOBOX_TIME_UNIT:
                            time_unit = combobox_time_unit->getSelected();
                            return_value = true;
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    return return_value;

}

void Ui::update()
{
    update_fps();
    update_clock();    
    update_date();
    update_coordinates();
    video_driver->beginScene(back_buffer_state, z_buffer_state, *color_background);    
    scene_manager->drawAll();
    gui_environment->drawAll();
    video_driver->endScene();
}

void Ui::update_clock()
{
    if(time->time_changed)
    {
        *stringw_clock = format_digits(time->get_hour());
        *stringw_clock += L":";
        *stringw_clock += format_digits(time->get_minute());
        *stringw_clock += L":";
        *stringw_clock += format_digits(time->get_second());
        statictext_clock->setText(stringw_clock->c_str());
        time->time_changed = false;
    }
}

void Ui::update_coordinates()
{
    if(user->get_character()->is_moving())
    {
        switch(scene_manager->getActiveCamera()->getID())
        {
            case CAMERA_OVERHEAD:
                // nothing yet
                break;
            case CAMERA_FIRST_PERSON:
                user->get_character()->set_coordinates(scene_manager->getActiveCamera()->getAbsolutePosition());
                break;
        }    
        *stringw_coordinate = L"X:  ";
        *stringw_coordinate += user->get_character()->get_coordinates()->X;
        statictext_coordinate_x->setText(stringw_coordinate->c_str());
        *stringw_coordinate = L"Y:  ";
        *stringw_coordinate += user->get_character()->get_coordinates()->Y;
        statictext_coordinate_y->setText(stringw_coordinate->c_str());
        *stringw_coordinate = L"Z:  ";
        *stringw_coordinate += user->get_character()->get_coordinates()->Z;
        statictext_coordinate_z->setText(stringw_coordinate->c_str());        
        user->get_character()->set_moving(false); // temporary - for testing
    }
}

void Ui::update_date()
{
    
    if(time->date_changed)
    {
        Day* day = time->get_day(time->get_day_of_year());
        *stringw_day = L"";
        *stringw_day += (*day_names)[day->get_day_of_week()];
        statictext_day->setText(stringw_day->c_str());
        
        *stringw_date = format_digits(time->get_year(), 4);
        *stringw_date += L"-";
        *stringw_date += format_digits(day->get_month());
        *stringw_date += L"-";
        *stringw_date += format_digits(day->get_day_of_month());
        statictext_date->setText(stringw_date->c_str());
        
        *stringw_season = L"";
        *stringw_season += (*season_names)[day->get_season()];
        statictext_season->setText(stringw_season->c_str());
        
        time->date_changed = false;
    }   
}

void Ui::update_fps()
{
    *stringw_fps = L"";
    *stringw_fps += video_driver->getFPS();
    statictext_fps->setText(stringw_fps->c_str());
}

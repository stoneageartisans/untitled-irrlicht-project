/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#ifndef TIME_H
#define TIME_H

#include "day.h"

#include <irrlicht.h>

// Units of Time
#define UNIT_NONE       0
#define UNIT_SECOND     1
#define UNIT_MINUTE     2
#define UNIT_HOUR       3
#define UNIT_DAY        4
#define UNIT_WEEK       5
#define UNIT_MONTH      6
#define UNIT_SEASON     7
#define UNIT_YEAR       8

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Time
{
    public:
        bool date_changed;
        bool time_changed;
        Time();
        Time(s32 YEAR, s32 DAY_OF_YEAR, s32 HOUR, s32 MINUTE, s32 SECOND);
        ~Time();        
        void advance_time(s32 UNIT);
        Day* get_day(s32 DAY_OF_YEAR);
        s32 get_day_of_year();
        s32 get_hour();
        s32 get_minute();
        s32 get_second();
        s32 get_year();

    private:
        map<s32, Day*>* days;
        s32 day_of_year;
        s32 hour;
        s32 minute;
        s32 second;
        s32 year;
        void advance_day();
		void advance_hour();
		void advance_minute();
		void advance_month();
		void advance_season();
		void advance_second();
		void advance_week();
		void advance_year();
        void initialize(s32 YEAR, s32 DAY_OF_YEAR, s32 HOUR, s32 MINUTE, s32 SECOND);
};

#endif // TIME_H

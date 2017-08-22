/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#ifndef DAY_H
#define DAY_H

#include <irrlicht.h>

// Days of the Week
#define MONDAY      1
#define TUESDAY     2
#define WEDNESDAY   3
#define THURSDAY    4
#define FRIDAY      5
#define SATURDAY    6
#define SUNDAY      7

// Seasons
#define SPRING  1
#define SUMMER  2
#define AUTUMN  3
#define WINTER  4

// Some Time Values
#define DAYS_IN_WEEK            7
#define DAYS_IN_MONTH           28
#define DAYS_IN_SEASON          91
#define DAYS_IN_YEAR            364
#define WEEKS_IN_MONTH          4
#define WEEKS_IN_SEASON         13
#define WEEKS_IN_YEAR           52
#define MONTHS_IN_YEAR          13
#define SEASONS_IN_YEAR         4
#define SPRING_LUNAR_ECLIPSE    46
#define AUTUMN_LUNAR_ECLIPSE    228

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Day
{
    public:
        Day();
        Day(s32 DAY_OF_YEAR);
        ~Day();
        s32 get_day_of_month();
        s32 get_day_of_season();
        s32 get_day_of_week();
        s32 get_day_of_year();
        s32 get_month();
        f32 get_moon_phase();
        f32 get_moon_position(s32 HOUR);
        s32 get_season();
        f32 get_sun_position(s32 HOUR);
        s32 get_week_of_month();
        s32 get_week_of_season();
        s32 get_week_of_year();

    private:
        s32 day_of_month;
        s32 day_of_season;
        s32 day_of_week;
        s32 day_of_year;
        s32 month;
        f32 moon_phase; // per day_of_month; 1.0 is a full moon
        map<s32, f32>* moon_positions; // per hour; 0.25 is due east (aka moonrise); 0.75 is due west (aka moonset)
        s32 season;
        map<s32, f32>* sun_positions; // per hour; 0.25 is due east (aka sunrise); 0.75 is due west (aka sunset)
        s32 week_of_month;
        s32 week_of_season;
        s32 week_of_year;
        void initialize(s32 DAY_OF_YEAR);
};

#endif // DAY_H

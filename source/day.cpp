/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#include "day.h"

#include <cmath>

// Astronomical-related constants
#define DEGREES_PER_HOUR        15
#define POSITION_MULITPLIER     ((f32) (24.0 / ((f32) DAYS_IN_MONTH)))
#define PHASE_DIVISOR           14
#define LENGTH_OF_DAY           0

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Day::Day()
{
	initialize(1);
}

Day::Day(s32 DAY_OF_YEAR)
{
	initialize(DAY_OF_YEAR);
}

Day::~Day()
{
    //
}

s32 Day::get_day_of_month()
{
    return day_of_month;
}

s32 Day::get_day_of_season()
{
    return day_of_season;
}

s32 Day::get_day_of_week()
{
    return day_of_week;
}

s32 Day::get_day_of_year()
{
    return day_of_year;
}

s32 Day::get_month()
{
    return month;
}

s32 Day::get_week_of_month()
{
    return week_of_month;
}

f32 Day::get_moon_phase()
{
    return moon_phase;
}

f32 Day::get_moon_position(s32 HOUR)
{
    return (*moon_positions)[HOUR];
}

s32 Day::get_season()
{
    return season;
}

f32 Day::get_sun_position(s32 HOUR)
{
    return (*sun_positions)[HOUR];
}

s32 Day::get_week_of_season()
{
    return week_of_season;
}

s32 Day::get_week_of_year()
{
    return week_of_year;
}

void Day::initialize(s32 DAY_OF_YEAR)
{   
    day_of_year = DAY_OF_YEAR;
    
    /* Do not change the order of these assignments */
    season = 1 + ((day_of_year - 1) / DAYS_IN_SEASON);
    day_of_season = day_of_year - (DAYS_IN_SEASON * (season - 1));
    week_of_season = 1 + ((day_of_season - 1) / DAYS_IN_SEASON);    
    month = 1 + ((day_of_year - 1) / DAYS_IN_MONTH);
    day_of_month = day_of_year - (DAYS_IN_MONTH * (month - 1));
    week_of_month = 1 + ((day_of_month - 1) / DAYS_IN_WEEK);
    day_of_week = day_of_month - (DAYS_IN_WEEK * (week_of_month - 1));    
    week_of_year = 1 + ((day_of_year - 1) / DAYS_IN_WEEK);
    
    /* Pre-calculate moon's phase based on the day */
    if(day_of_month > PHASE_DIVISOR)
    {
        moon_phase = (f32) ((f32) (DAYS_IN_MONTH - day_of_month) / (f32) PHASE_DIVISOR);
    }
    else
    {
        moon_phase = (f32) ((f32) day_of_month / (f32) PHASE_DIVISOR);
    }
    
    /* Pre-calculate moon's positions based on the hour */
    s32 moon_start = (s32) round(POSITION_MULITPLIER * ((f32) day_of_month)); // the hour that the moon's position is 0.0
    moon_positions = new map<s32, f32>(); // moonrise = 0.25, moonset = 0.75
    for(u32 hour = 0; hour < 24; hour ++)
    {
        if(hour < moon_start)
        {
            moon_positions->insert(hour, (f32) ((f32) (360 - ((moon_start - hour) * DEGREES_PER_HOUR)) / (f32) 360));
        }
        else
        {
            moon_positions->insert(hour, (f32) ((f32) ((hour - moon_start) * DEGREES_PER_HOUR) / (f32) 360));
        }
    }
    
    /* Pre-calculate sun's positions based on the hour */
    sun_positions = new map<s32, f32>(); // sunrise = 0.25, sunset = 0.75
    for(u32 hour = 0; hour < 24; hour ++)
    {
        sun_positions->insert(hour, (f32) ((f32) (hour * DEGREES_PER_HOUR) / (f32) 360));
    }
}

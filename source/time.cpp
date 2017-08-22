/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#include "time.h"
#include "day.h"

#include <iostream> // temp

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Time::Time()
{
	initialize(1, 1, 0, 0, 0);
}

Time::Time(s32 YEAR, s32 DAY_OF_YEAR, s32 HOUR, s32 MINUTE, s32 SECOND)
{
	initialize(YEAR, DAY_OF_YEAR, HOUR, MINUTE, SECOND);
}

Time::~Time()
{
    delete days;
}

void Time::advance_day()
{
    day_of_year = day_of_year + 1;
    if(day_of_year > DAYS_IN_YEAR)
    {
        day_of_year = 1;
        advance_year();
    }
    date_changed = true;
    std::cout << "Moon phase: " << get_day(day_of_year)->get_moon_phase() << std::endl; // temp
}

void Time::advance_hour()
{
    hour = hour + 1;
    if(hour > 23)
        {
        hour = 0;
        advance_day();
    }
    time_changed = true;
    std::cout << "Moon position: " << get_day(day_of_year)->get_moon_position(hour) << std::endl; // temp
    std::cout << "Sun position: " << get_day(day_of_year)->get_sun_position(hour) << std::endl; // temp
}

void Time::advance_minute()
{
    minute = minute + 1;
    if(minute > 59)
    {
        minute = 0;
        advance_hour();
    }
    time_changed = true;
}

void Time::advance_month()
{
    day_of_year = day_of_year + DAYS_IN_MONTH;
    if(day_of_year > DAYS_IN_YEAR)
    {
        day_of_year = day_of_year - DAYS_IN_YEAR;
        advance_year();
    }
    date_changed = true;
    std::cout << "Moon phase: " << get_day(day_of_year)->get_moon_phase() << std::endl; // temp
}

/* Advances the time and date to midnight on the first day of the next season */
void Time::advance_season()
{
    Day* day = (*days)[day_of_year];
    s32 season = day->get_season() + 1;
    
    if(season > SEASONS_IN_YEAR)
    {
        season = 1;
        advance_year();
    }

    switch(season)
    {
        case 1:
            initialize(year, 1, 0, 0, 0);
            break;
        case 2:
            initialize(year, 92, 0, 0, 0);
            break;
        case 3:
            initialize(year, 183, 0, 0, 0);
            break;
        case 4:
            initialize(year, 274, 0, 0, 0);
            break;
    }
    time_changed = true;
    date_changed = true;
    std::cout << "Moon phase: " << get_day(day_of_year)->get_moon_phase() << std::endl; // temp
    std::cout << "Moon position: " << get_day(day_of_year)->get_moon_position(hour) << std::endl; // temp
    std::cout << "Sun position: " << get_day(day_of_year)->get_sun_position(hour) << std::endl; // temp
}

void Time::advance_second()
{
    second = second + 1;
    if(second > 59)
    {
        second = 0;
        advance_minute();
    }
    time_changed = true;
}

void Time::advance_time(s32 UNIT)
{
	switch(UNIT)
	{
        case UNIT_NONE:
            // do nothing
            break;
		case UNIT_SECOND:
			advance_second();
			break;
		case UNIT_MINUTE:
			advance_minute();
			break;
		case UNIT_HOUR:
			advance_hour();
			break;
		case UNIT_DAY:
			advance_day();
			break;
		case UNIT_WEEK:
			advance_week();
			break;
		case UNIT_MONTH:
			advance_month();
			break;
		case UNIT_SEASON:
			advance_season();
			break;
		case UNIT_YEAR:
			advance_year();
			break;
	}
}

void Time::advance_week()
{
    day_of_year = day_of_year + DAYS_IN_WEEK;
    if(day_of_year > DAYS_IN_YEAR)
    {
        day_of_year = day_of_year - DAYS_IN_YEAR;
        advance_year();
    }
    date_changed = true;
    std::cout << "Moon phase: " << get_day(day_of_year)->get_moon_phase() << std::endl; // temp
}

void Time::advance_year()
{
    year = year + 1;
    date_changed = true;
}

Day* Time::get_day(s32 DAY_OF_YEAR)
{
    return (*days)[DAY_OF_YEAR];
}

s32 Time::get_day_of_year()
{
    return day_of_year;
}

s32 Time::get_hour()
{
    return hour;
}

s32 Time::get_minute()
{
    return minute;
}

s32 Time::get_second()
{
    return second;
}

s32 Time::get_year()
{
    return year;
}

void Time::initialize(s32 YEAR, s32 DAY_OF_YEAR, s32 HOUR, s32 MINUTE, s32 SECOND)
{
    year = YEAR;    
    day_of_year = DAY_OF_YEAR;
    hour = HOUR;
    minute = MINUTE;
    second = SECOND;
    
    days = new map<s32, Day*>();
    days->insert(0, 0);
    for(s32 i = 1; i <= DAYS_IN_YEAR; i ++)
    {
        days->insert(i, new Day(i));
    }
    
    date_changed = true;
    time_changed = true;
}

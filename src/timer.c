#include <pebble.h>
#include <timer.h>
#include <watchface.h>
#include <globals.h>

void update_time(int hour, int minute, int day, int month) {
	// Set Hours
	int buffer_hour = hour;
	if(minute == 40 ||
	   minute == 45 ||
	   minute >= 50
	  ){
		buffer_hour++;
	}
	if(buffer_hour>23){
		buffer_hour = 0;
	}
	set_hour(HOURS[buffer_hour]);
	// Set Minutes
	static char buffer_minute[32];
	strcpy(buffer_minute, WITH_HOURS[buffer_hour]);
	strcat(buffer_minute, MINUTES[minute]);
	set_minute(buffer_minute);
	// Set Dates
	static char buffer_dates[42];
	strcpy(buffer_dates, DAYS[day]);
	strcat(buffer_dates, MONTHS[month]);
	set_date(buffer_dates);
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
	update_time(tick_time->tm_hour, tick_time->tm_min, tick_time->tm_mday-1, tick_time->tm_mon);
}
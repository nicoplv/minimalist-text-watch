#ifndef TIMER_H
#define TIMER_H
	
void update_time(int hour, int minute, int day, int month);
void tick_handler(struct tm *tick_time, TimeUnits units_changed) ;

#endif
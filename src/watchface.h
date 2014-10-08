#ifndef WATCHFACE_H
#define WATCHFACE_H

void set_hour(char _hour[]);
void set_minute(char _minute[]);
void set_date(char _date[]);
void set_battery_bitmap(int _id_ressource);

void init_watchface();
void deinit_watchface();

#endif
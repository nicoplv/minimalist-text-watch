#ifndef BATTERY_H
#define BATTERY_H

void update_battery(BatteryChargeState charge_state);
void battery_handler(BatteryChargeState charge_state);
	
#endif
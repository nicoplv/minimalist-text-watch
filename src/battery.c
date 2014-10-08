#include <pebble.h>
#include <battery.h>
#include <watchface.h>

void update_battery(BatteryChargeState charge_state) {
	int charge_percent = charge_state.charge_percent;
	if(charge_percent>=87){
		set_battery_bitmap(RESOURCE_ID_BATTERY_06);
	}
	else if(charge_percent>=74){
		set_battery_bitmap(RESOURCE_ID_BATTERY_05);
	}
	else if(charge_percent>=61){
		set_battery_bitmap(RESOURCE_ID_BATTERY_04);
	}
	else if(charge_percent>=48){
		set_battery_bitmap(RESOURCE_ID_BATTERY_03);
	}
	else if(charge_percent>=35){
		set_battery_bitmap(RESOURCE_ID_BATTERY_02);
	}
	else if(charge_percent>=22){
		set_battery_bitmap(RESOURCE_ID_BATTERY_01);
	}
	else if(charge_percent>=9){
		set_battery_bitmap(RESOURCE_ID_BATTERY_00);
	}
}

void battery_handler(BatteryChargeState charge_state) {
	update_battery(charge_state);
}
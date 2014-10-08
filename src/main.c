#include <pebble.h>
#include <watchface.h>
#include <battery.h>
#include <timer.h>

void init() {
	// Init Watchface
	init_watchface();
	
	// Subscribe to Battery service
	battery_state_service_subscribe(battery_handler);
	// Initial Update
	BatteryChargeState charge_state = battery_state_service_peek();
	update_battery(charge_state);
	
	// Subscribe to Timer service
	tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
	// Initial Update
	time_t temp = time(NULL); 
	struct tm *tick_time = localtime(&temp);
	update_time(tick_time->tm_hour, tick_time->tm_min, tick_time->tm_mday-1, tick_time->tm_mon);
	
	// debug mode
	// init_debug(s_main_window, s_hours_layer, s_minutes_layer);
}

void deinit() {
	// Deinit Watchface
	deinit_watchface();
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
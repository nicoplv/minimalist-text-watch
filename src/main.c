#include <pebble.h>
	
static Window *s_main_window;
static BitmapLayer *s_background_layer;
static GFont s_hours_font;
static GFont s_minutes_font;
static GFont s_dates_font;
static TextLayer *s_hours_layer;
static char s_hours_text[24][20] = {"minuit", "une", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf", "dix", "onze", "midi", "treize", "quatorze", "quinze",
									"seize", "dix-sept", "dix-huit", "dix-neuf", "vingt", "vingt-et-une", "vingt-deux", "vingt-trois"};
static TextLayer *s_minutes_layer;
static char s_with_hours_text[24][10] = {"", "heure ", "heures ", "heures ", "heures ", "heures ", "heures ", "heures ", "heures ", "heures ", "heures ", "heures ", "", "heures ",
										"heures ", "heures ", "heures ", "heures ", "heures ", "heures ", "heures ", "heures ", "heures ", "heures "};
static char s_minutes_text[60][20] = {"pile", "une", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf", "dix", "onze", "douze", "treize", "quatorze", "et quart",
									"seize", "dix-sept", "dix-huit", "dix-neuf", "vingt", "vingt-et-une", "vingt-deux", "vingt-trois", "vingt-quatre", "vingt-cinq", "vingt-six",
									"vingt-sept", "vingt-huit", "vingt-neuf", "et demi", "trente-et-une", "trente-deux", "trente-trois", "trente-quatre", "trente-cinq",
									"trente-six", "trente-sept", "trente-huit", "trente-neuf", "moins vingt", "quarente-et-une", "quarente-deux", "quarente-trois", "quarente-quatre",
									"moins le quart", "quarente-six", "quarente-sept", "quarente-huit", "quarente-neuf", "moins dix", "moins neuf", "moins huit",
									"moins sept", "moins six", "moins cinq", "moins quatre", "moins trois", "moins deux", "moins une"};
static TextLayer *s_dates_layer;
static char s_days_text[32][20] = {"", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf", "dix", "onze", "douze", "treize", "quatorze", "quinze",
									"seize", "dix-sept", "dix-huit", "dix-neuf", "vingt", "vingt-et-une", "vingt-deux", "vingt-trois", "vingt-quatre", "vingt-cinq", "vingt-six",
									"vingt-sept", "vingt-huit", "vingt-neuf", "trente", "trente-et-un"};
static char s_months_text[12][20] = {" janvier", " février", " mars", " avril", " mai", " juin", " juillet", " août", " septembre", " octobre", " novembre", " décembre"};
static BitmapLayer *s_battery_layer;
static GBitmap *s_battery_bitmap_00;
static GBitmap *s_battery_bitmap_01;
static GBitmap *s_battery_bitmap_02;
static GBitmap *s_battery_bitmap_03;
static GBitmap *s_battery_bitmap_04;
static GBitmap *s_battery_bitmap_05;
static GBitmap *s_battery_bitmap_06;

static void main_window_load(Window *window) {
	// Create Background Layer
	s_background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
	bitmap_layer_set_background_color(s_background_layer, GColorBlack);
	layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_background_layer));
	// Load Fonts
	s_hours_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LATO_BLACK_24));
	s_minutes_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LATO_REGULAR_18));
	s_dates_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LATO_REGULAR_12));
	// Create Hours Text Layer
	s_hours_layer = text_layer_create(GRect(4,42,136,32));
	text_layer_set_background_color(s_hours_layer, GColorClear);
	text_layer_set_text_color(s_hours_layer, GColorWhite);
	text_layer_set_text(s_hours_layer, "mille");
	text_layer_set_font(s_hours_layer, s_hours_font);
	text_layer_set_text_alignment(s_hours_layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_hours_layer));
	// Create Minutes Text Layer
	s_minutes_layer = text_layer_create(GRect(4,68,136,64));
	text_layer_set_background_color(s_minutes_layer, GColorClear);
	text_layer_set_text_color(s_minutes_layer, GColorWhite);
	text_layer_set_text(s_minutes_layer, "heures moins mille");
	text_layer_set_font(s_minutes_layer, s_minutes_font);
	text_layer_set_text_alignment(s_minutes_layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_minutes_layer));
	// Create Dates Text Layer
	s_dates_layer = text_layer_create(GRect(4,150,136,32));
	text_layer_set_background_color(s_dates_layer, GColorClear);
	text_layer_set_text_color(s_dates_layer, GColorWhite);
	text_layer_set_text(s_dates_layer, "mille movembre");
	text_layer_set_font(s_dates_layer, s_dates_font);
	text_layer_set_text_alignment(s_dates_layer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_dates_layer));
	// Create Battery Layer
	s_battery_bitmap_00 = gbitmap_create_with_resource(RESOURCE_ID_BATTERY_00);
	s_battery_bitmap_01 = gbitmap_create_with_resource(RESOURCE_ID_BATTERY_01);
	s_battery_bitmap_02 = gbitmap_create_with_resource(RESOURCE_ID_BATTERY_02);
	s_battery_bitmap_03 = gbitmap_create_with_resource(RESOURCE_ID_BATTERY_03);
	s_battery_bitmap_04 = gbitmap_create_with_resource(RESOURCE_ID_BATTERY_04);
	s_battery_bitmap_05 = gbitmap_create_with_resource(RESOURCE_ID_BATTERY_05);
	s_battery_bitmap_06 = gbitmap_create_with_resource(RESOURCE_ID_BATTERY_06);
	s_battery_layer = bitmap_layer_create(GRect(59, 4, 26, 10));
	bitmap_layer_set_bitmap(s_battery_layer, s_battery_bitmap_00);
	layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_battery_layer));
}

static void main_window_unload(Window *window) {
	// Destroy Background Layer
	bitmap_layer_destroy(s_background_layer);
	// Unload Fonts
	fonts_unload_custom_font(s_hours_font);
	fonts_unload_custom_font(s_minutes_font);
	fonts_unload_custom_font(s_dates_font);
	// Destroy Hours Text Layer
	text_layer_destroy(s_hours_layer);
	// Destroy Minutes Text Layer
	text_layer_destroy(s_minutes_layer);
	// Destroy Dates Text Layer
	text_layer_destroy(s_dates_layer);
	// Destroy Battery Layer and Bitmap
	bitmap_layer_destroy(s_battery_layer);
	gbitmap_destroy(s_battery_bitmap_00);
	gbitmap_destroy(s_battery_bitmap_01);
	gbitmap_destroy(s_battery_bitmap_02);
	gbitmap_destroy(s_battery_bitmap_03);
	gbitmap_destroy(s_battery_bitmap_04);
	gbitmap_destroy(s_battery_bitmap_05);
	gbitmap_destroy(s_battery_bitmap_06);
}

static void update_time() {
	time_t temp = time(NULL);
	struct tm *tick_time = localtime(&temp);
	// Set Hours
	int buffer_hours = tick_time->tm_hour;
	if(tick_time->tm_min == 40 ||
	   tick_time->tm_min == 45 ||
	   tick_time->tm_min >= 50
	  ){
		buffer_hours++;
	}
	if(buffer_hours>23){
		buffer_hours = 0;
	}
	text_layer_set_text(s_hours_layer, s_hours_text[buffer_hours]);
	// Set Minutes
	static char buffer_minutes[32];
	strcpy(buffer_minutes, s_with_hours_text[buffer_hours]);
	strcat(buffer_minutes, s_minutes_text[tick_time->tm_min]);
	text_layer_set_text(s_minutes_layer, buffer_minutes);
	// Set Dates
	static char buffer_dates[42];
	strcpy(buffer_dates, s_days_text[tick_time->tm_wday]);
	strcat(buffer_dates, s_months_text[tick_time->tm_mon]);
	text_layer_set_text(s_dates_layer, buffer_dates);
}

static void update_battery() {
	// Set Battery
	BatteryChargeState charge_state = battery_state_service_peek();
	uint8_t charge_percent = charge_state.charge_percent;
	if(charge_percent>=87){
		bitmap_layer_set_bitmap(s_battery_layer, s_battery_bitmap_06);
	}
	else if(charge_percent>=74){
		bitmap_layer_set_bitmap(s_battery_layer, s_battery_bitmap_05);
	}
	else if(charge_percent>=61){
		bitmap_layer_set_bitmap(s_battery_layer, s_battery_bitmap_04);
	}
	else if(charge_percent>=48){
		bitmap_layer_set_bitmap(s_battery_layer, s_battery_bitmap_03);
	}
	else if(charge_percent>=35){
		bitmap_layer_set_bitmap(s_battery_layer, s_battery_bitmap_02);
	}
	else if(charge_percent>=22){
		bitmap_layer_set_bitmap(s_battery_layer, s_battery_bitmap_01);
	}
	else if(charge_percent>=9){
		bitmap_layer_set_bitmap(s_battery_layer, s_battery_bitmap_00);
	}
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
	update_time();
}

static void battery_handler(BatteryChargeState charge_state) {
	update_battery();
}

static void init() {
	s_main_window = window_create();
	
	window_set_window_handlers(s_main_window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload
	});
	
	window_stack_push(s_main_window, true);
	
	update_time();
	update_battery();

	tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
	battery_state_service_subscribe(battery_handler);
}

static void deinit() {
	window_destroy(s_main_window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
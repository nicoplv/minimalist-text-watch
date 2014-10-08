#include <pebble.h>
#include <watchface.h>
	
static Window *window_watchface;

static BitmapLayer *layer_background;
static TextLayer *layer_hour;
static TextLayer *layer_minute;
static TextLayer *layer_date;
static BitmapLayer *layer_battery;

static GFont font_hour;
static GFont font_minute;
static GFont font_date;

static GBitmap *bitmap_battery;

void window_load(Window *window) {	
	// Load Fonts
	font_hour = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LATO_BLACK_24));
	font_minute = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LATO_REGULAR_18));
	font_date = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LATO_REGULAR_12));
	
	// Create Background Layer
	layer_background = bitmap_layer_create(GRect(0, 0, 144, 168));
	bitmap_layer_set_background_color(layer_background, GColorBlack);
	layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(layer_background));
	
	// Create Hours Text Layer
	layer_hour = text_layer_create(GRect(4,42,136,32));
	text_layer_set_background_color(layer_hour, GColorClear);
	text_layer_set_text_color(layer_hour, GColorWhite);
	text_layer_set_text(layer_hour, "mille");
	text_layer_set_font(layer_hour, font_hour);
	text_layer_set_text_alignment(layer_hour, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(layer_hour));
	
	// Create Minutes Text Layer
	layer_minute = text_layer_create(GRect(4,68,136,64));
	text_layer_set_background_color(layer_minute, GColorClear);
	text_layer_set_text_color(layer_minute, GColorWhite);
	text_layer_set_text(layer_minute, "heures moins mille");
	text_layer_set_font(layer_minute, font_minute);
	text_layer_set_text_alignment(layer_minute, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(layer_minute));
	
	// Create Dates Text Layer
	layer_date = text_layer_create(GRect(4,150,136,32));
	text_layer_set_background_color(layer_date, GColorClear);
	text_layer_set_text_color(layer_date, GColorWhite);
	text_layer_set_text(layer_date, "mille movembre");
	text_layer_set_font(layer_date, font_date);
	text_layer_set_text_alignment(layer_date, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(layer_date));
	
	// Create Battery Layer
	bitmap_battery = gbitmap_create_with_resource(RESOURCE_ID_BATTERY_00);
	layer_battery = bitmap_layer_create(GRect(59, 4, 26, 10));
	bitmap_layer_set_bitmap(layer_battery, bitmap_battery);
	layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(layer_battery));
}

void window_unload(Window *window) {
	// Unload Fonts
	fonts_unload_custom_font(font_hour);
	fonts_unload_custom_font(font_minute);
	fonts_unload_custom_font(font_date);
	// Destroy Layer
	bitmap_layer_destroy(layer_background);
	text_layer_destroy(layer_hour);
	text_layer_destroy(layer_minute);
	text_layer_destroy(layer_date);
	bitmap_layer_destroy(layer_battery);
	// Destroy Bitmap
	gbitmap_destroy(bitmap_battery);
}

void set_hour(char _hour[]) {
	text_layer_set_text(layer_hour, _hour);
}

void set_minute(char _minute[]) {
	text_layer_set_text(layer_minute, _minute);
}

void set_date(char _date[]) {
	text_layer_set_text(layer_date, _date);
}

void set_battery_bitmap(int _id_ressource) {
	gbitmap_destroy(bitmap_battery);
	bitmap_battery = gbitmap_create_with_resource(_id_ressource);
	bitmap_layer_set_bitmap(layer_battery, bitmap_battery);
}

void init_watchface() {
	window_watchface = window_create();
	
	window_set_window_handlers(window_watchface, (WindowHandlers) {
		.load = window_load,
		.unload = window_unload
	});
	
	window_stack_push(window_watchface, true);
}

void deinit_watchface() {
	window_destroy(window_watchface);
}
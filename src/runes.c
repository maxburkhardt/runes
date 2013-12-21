#include <pebble.h>

static Window *window;
TextLayer *text_hour_layer; //will display the hour
TextLayer *text_hex_layer; //will display the tens place of the time
TextLayer *text_minute_layer; //will display the least significant minute digit

void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {

    //first let's deal with the hour
    int hour_value = tick_time->tm_hour % 12;
    switch (hour_value)
    {
        case 0:
            text_layer_set_text(text_hour_layer, "twelve");
            break;
        case 1:
            text_layer_set_text(text_hour_layer, "one");
            break;
        case 2:
            text_layer_set_text(text_hour_layer, "two");
            break;
        case 3:
            text_layer_set_text(text_hour_layer, "xree");
            break;
        case 4:
            text_layer_set_text(text_hour_layer, "four");
            break;
        case 5:
            text_layer_set_text(text_hour_layer, "five");
            break;
        case 6:
            text_layer_set_text(text_hour_layer, "siks");
            break;
        case 7:
            text_layer_set_text(text_hour_layer, "seven");
            break;
        case 8:
            text_layer_set_text(text_hour_layer, "eight");
            break;
        case 9:
            text_layer_set_text(text_hour_layer, "nine");
            break;
        case 10:
            text_layer_set_text(text_hour_layer, "ten");
            break;
        case 11:
            text_layer_set_text(text_hour_layer, "eleven");
            break;
    }

    int minute_value = tick_time->tm_min;

    if (minute_value >= 0 && minute_value < 11) {
        //no third row, use single digits
        switch (minute_value) {
            case 0:
                text_layer_set_text(text_hex_layer, "");
                break;
            case 1:
                text_layer_set_text(text_hex_layer, "one");
                break;
            case 2:
                text_layer_set_text(text_hex_layer, "two");
                break;
            case 3:
                text_layer_set_text(text_hex_layer, "xree");
                break;
            case 4:
                text_layer_set_text(text_hex_layer, "four");
                break;
            case 5:
                text_layer_set_text(text_hex_layer, "five");
                break;
            case 6:
                text_layer_set_text(text_hex_layer, "siks");
                break;
            case 7:
                text_layer_set_text(text_hex_layer, "seven");
                break;
            case 8:
                text_layer_set_text(text_hex_layer, "eight");
                break;
            case 9:
                text_layer_set_text(text_hex_layer, "nine");
                break;
            case 10:
                text_layer_set_text(text_hex_layer, "ten");
                break;
        }
        text_layer_set_text(text_minute_layer, "");
    } else if (minute_value >= 11 && minute_value < 20) {
        //handle teens
        switch (minute_value) {
            case 11:
                text_layer_set_text(text_hex_layer, "eleven");
                text_layer_set_text(text_minute_layer, "");
                break;
            case 12:
                text_layer_set_text(text_hex_layer, "twelve");
                text_layer_set_text(text_minute_layer, "");
                break;
            case 13:
                text_layer_set_text(text_hex_layer, "xirteen");
                text_layer_set_text(text_minute_layer, "");
                break;
            case 14:
                text_layer_set_text(text_hex_layer, "four");
                text_layer_set_text(text_minute_layer, "teen");
                break;
            case 15:
                text_layer_set_text(text_hex_layer, "fif");
                text_layer_set_text(text_minute_layer, "teen");
                break;
            case 16:
                text_layer_set_text(text_hex_layer, "siks");
                text_layer_set_text(text_minute_layer, "teen");
                break;
            case 17:
                text_layer_set_text(text_hex_layer, "seven");
                text_layer_set_text(text_minute_layer, "teen");
                break;
            case 18:
                text_layer_set_text(text_hex_layer, "eight");
                text_layer_set_text(text_minute_layer, "teen");
                break;
            case 19:
                text_layer_set_text(text_hex_layer, "nine");
                text_layer_set_text(text_minute_layer, "teen");
                break;
        }
    } else {
        //handle the rest of the numbers
        // now first part of minute
        int hex = (minute_value - (minute_value % 10)) / 10;
        switch (hex)
        {
            case 2:
                text_layer_set_text(text_hex_layer, "twenty");
                break;
            case 3:
                text_layer_set_text(text_hex_layer, "xirty");
                break;
            case 4:
                text_layer_set_text(text_hex_layer, "forty");
                break;
            case 5:
                text_layer_set_text(text_hex_layer, "fifty");
                break;
        }
        int minute_ls = minute_value % 10;
        switch (minute_ls) {
            case 0:
                text_layer_set_text(text_minute_layer, "");
                break;
            case 1:
                text_layer_set_text(text_minute_layer, "one");
                break;
            case 2:
                text_layer_set_text(text_minute_layer, "two");
                break;
            case 3:
                text_layer_set_text(text_minute_layer, "xree");
                break;
            case 4:
                text_layer_set_text(text_minute_layer, "four");
                break;
            case 5:
                text_layer_set_text(text_minute_layer, "five");
                break;
            case 6:
                text_layer_set_text(text_minute_layer, "siks");
                break;
            case 7:
                text_layer_set_text(text_minute_layer, "seven");
                break;
            case 8:
                text_layer_set_text(text_minute_layer, "eight");
                break;
            case 9:
                text_layer_set_text(text_minute_layer, "nine");
                break;
        }
    }
}


static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);

  text_hour_layer = text_layer_create(GRect(15, 10, 104, 50));
  text_layer_set_text_color(text_hour_layer, GColorWhite);
  text_layer_set_background_color(text_hour_layer, GColorClear);
  text_layer_set_font(text_hour_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_RUNES_30)));
  layer_add_child(window_layer, text_layer_get_layer(text_hour_layer));

  text_hex_layer = text_layer_create(GRect(15, 65, 104, 50));
  text_layer_set_text_color(text_hex_layer, GColorWhite);
  text_layer_set_background_color(text_hex_layer, GColorClear);
  text_layer_set_font(text_hex_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_RUNES_30)));
  layer_add_child(window_layer, text_layer_get_layer(text_hex_layer));

  text_minute_layer = text_layer_create(GRect(15, 120, 104, 50));
  text_layer_set_text_color(text_minute_layer, GColorWhite);
  text_layer_set_background_color(text_minute_layer, GColorClear);
  text_layer_set_font(text_minute_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_RUNES_30)));
  layer_add_child(window_layer, text_layer_get_layer(text_minute_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_hour_layer);
  text_layer_destroy(text_hex_layer);
  text_layer_destroy(text_minute_layer);
}

static void init(void) {
  window = window_create();
  window_set_background_color(window, GColorBlack);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);

  tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);
}

static void deinit(void) {
  window_destroy(window);
  tick_timer_service_unsubscribe();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}

#pragma once

#include <U8glib.h>

typedef void (*drawhandler)(U8GLIB &);

void lcd_init();

void lcd_draw(drawhandler handler);

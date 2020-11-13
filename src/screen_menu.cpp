#include <Arduino.h>

#include "screen_menu.h"
#include "buzzer.h"

static void testBuzzer()
{
    buzzer_toggle(true);
    delay(500);
    buzzer_toggle(false);
}

typedef void (*item_action)();

typedef struct
{
    const char *label;
    const item_action action;
    const ScreenType next;
} MenuItem;

const MenuItem ITEMS[] = {
    {.label = "< Back", .action = nullptr, .next = MAIN},
    {.label = "    Fan Speed", .action = nullptr, .next = FANCONTROL},
    {.label = "    Buzzer Test (LOUD)", .action = testBuzzer, .next = NO_CHANGE},
};

#define ITEM_COUNT (sizeof(ITEMS) / sizeof(MenuItem))

size_t selectedItem = 0;

void MenuScreen::draw(U8GLIB &u8g)
{
    for (size_t i = 0; i < ITEM_COUNT; ++i)
    {
        if (i == selectedItem)
        {
            u8g.drawLine(0, i * 14, 127, i * 14);
            u8g.drawLine(0, i * 14 + 12, 127, i * 14 + 12);
        }
        u8g.drawStr(8, i * 14 + 10, ITEMS[i].label);
    }
}

ScreenType MenuScreen::handleClick()
{
    auto &item = ITEMS[selectedItem];
    if (item.action)
    {
        item.action();
    }
    return item.next;
}

void MenuScreen::handleScroll(int steps)
{
    selectedItem = (size_t)constrain((int)selectedItem + steps, 0, (int)ITEM_COUNT - 1);
}

#include <iostream>
#include "cldraw.h"

using namespace std;

const int CANVAS_W = WIDTH/2;
const int CANVAS_H = HEIGHT - 2;
const int PANEL_Y = HEIGHT - 1;

int canvas[CANVAS_H][CANVAS_W];
int selected_color = BACKGROUND_RED;
int cursor_x = 0;
int cursor_y = 0;

int palette[]{
    112, 
    128,
    15, 
    111, 
    32,
    16, 
    60, 
    64,
};
const int palette_len = 8;

void clear_canvas(int color) {
    for (int y = 0; y < CANVAS_H; y++) {
        for (int x = 0; x < CANVAS_W; x++) {
            canvas[y][x] = color;
        }
    }
}
void draw_canvas() {
    for (int y = 0; y < CANVAS_H; y++) {
        for (int x = 0; x < CANVAS_W; x++) {
            console_pixel(x * 2, y, ' ', canvas[y][x]);
            console_pixel(x * 2 + 1, y, ' ', canvas[y][x]);
        }
    }
}
void draw_cursor() {
    console_pixel(cursor_x * 2, cursor_y, '<',
        canvas[cursor_y][cursor_x]);
    console_pixel(cursor_x * 2 + 1, cursor_y, '>',
        canvas[cursor_y][cursor_x]);
}

void control_cursor() {
    if (just_pressed(VK_LEFT)) {
        if (cursor_x > 0) {
            cursor_x--;
        }
    }
    if (just_pressed(VK_RIGHT)) {
        if (cursor_x < CANVAS_W - 1) {
            cursor_x++;
        }
    }
    if (just_pressed(VK_UP)) {
        if (cursor_y > 0) {
            cursor_y--;
        }
    }
    if (just_pressed(VK_DOWN)) {
        if (cursor_y < CANVAS_H - 1) {
            cursor_y++;
        }
    }
    if (console_is_pressed(VK_SPACE)) {
        canvas[cursor_y][cursor_x] = selected_color;
    }
}

void control_color() {
    for (int i = 0; i < palette_len; i++) {
        if (console_is_pressed('1' + i)) {
            selected_color = palette[i];
        }
    }
}

void main() {
    setlocale(LC_ALL, "");
    clear_canvas(BACKGROUND_INTENSITY);
    create_console(L"Paint 2.0");
    while (true) {
        control_cursor();
        control_color();

        console_clear();
        draw_canvas();
        draw_cursor();
        console_text("color", 0, PANEL_Y);
        console_text("      ", 6, PANEL_Y, selected_color);

        console_text("colors", 40, PANEL_Y);
        for (int i = 0; i < palette_len; i++) {
            console_pixel(46+i*2, PANEL_Y - 1, '1' + i);
            console_pixel(46 + i * 2, PANEL_Y, ' ',
                          palette[i]);
        }
        console_flip(60);
    }
}
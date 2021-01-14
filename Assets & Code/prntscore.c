// Copyright (c) 2020 Marcus A. Mosley All rights reserved.
//
// Created by Marcus A. Mosley
// Created on January 2020
// This program prints the score

#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <font.c>
#include <Cursor.c>
#include <score_map.c>
#include <keyboard_map.c>

int count;
int initial;
int scorestr[];
struct Cursor cursor;
UBYTE keydown, playerhasname;
const UINT8 mincursorx = 12;
const UINT8 mincursory = 56;
const UINT8 maxcursorx = 156;
const UINT8 maxcursory = 88;

extern INT32 score;
extern INT32 onerank;
extern INT32 tworank;
extern INT32 threerank;
extern int oneinit;
extern int twoinit;
extern int threeinit;

UBYTE isWithinKeyboard(UINT8 x, UINT8 y) {
    // check special locations at bottom of keyboard
    if (x == 140 && y == 144 || x == 156 && y == 144) {
        return 1;
    }
    return (x >= mincursorx && x <= maxcursorx && y >= mincursory &&
        y <= maxcursory);
}

void playname() {
    NR10_REG = 0x00;
    NR11_REG = 0x81;
    NR12_REG = 0x43;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
}

void updateplayername(struct Cursor* cursor) {
    int number;
    // check if cursor at done
    if (cursor->x == 156 && cursor->y == 88) {
        // Player Finished
        playerhasname = 1;
        playname();
    } else {
        number = cursor->row * 10 + cursor->col + 11;
        if (number <= 34) {
            initial = number;
        }
        set_sprite_tile(1, initial);
        move_sprite(1, 12, 40);
    }
}

void keyboard() {
    DISPLAY_OFF;
    set_bkg_tiles(0, 0, 20, 18, keyboard_map);
    scroll_bkg(-4, 0);
    DISPLAY_ON;
    HIDE_SPRITES;
    for (count = 0; count <= 39; count++) {
        set_sprite_tile(count, 0);
        move_sprite(count, 152, 136);
    }
    cursor.x = 12;
    cursor.y = 56;
    cursor.col = 0;
    cursor.row = 0;
    set_sprite_tile(0, 37);
    move_sprite(0, cursor.x, cursor.y);
    SHOW_SPRITES;

    while (!playerhasname) {
        if (keydown) {
            waitpadup();
            keydown = 0;
        }

        switch (joypad()) {
            case J_UP:
                if (isWithinKeyboard(cursor.x, cursor.y - 16)) {
                    cursor.y -= 16;
                    scroll_sprite(0, 0, -16);
                    keydown = 1;
                    cursor.row -= 1;
                }
                break;
            case J_DOWN:
                if (isWithinKeyboard(cursor.x, cursor.y + 16)) {
                    cursor.y += 16;
                    scroll_sprite(0, 0, 16);
                    keydown = 1;
                    cursor.row += 1;
                }
                break;
            case J_LEFT:
                if (isWithinKeyboard(cursor.x - 16, cursor.y)) {
                    cursor.x -= 16;
                    scroll_sprite(0, -16, 0);
                    keydown = 1;
                    cursor.col -= 1;
                }
                break;
            case J_RIGHT:
                if (isWithinKeyboard(cursor.x + 16, cursor.y)) {
                    cursor.x += 16;
                    scroll_sprite(0, 16, 0);
                    keydown = 1;
                    cursor.col += 1;
                }
                break;
            case J_A:
                updateplayername(&cursor);
                keydown = 1;
                break;
        }
    }
}

int drawfinal(unsigned int scorebak, int number, int usedspr) {
    int tile;
    int length;
    int digit;
    length = 0;
    while (scorebak != 0) {
        digit = scorebak % 10;
        scorestr[length] = digit;
        scorebak = scorebak / 10;
        length++;
    }
    for (count = length; count >= 0; count--) {
        tile = scorestr[count - 1] + 1;
        set_sprite_tile(count + usedspr, tile);
        set_sprite_prop(count + usedspr, get_sprite_prop(count + usedspr) &
                        ~S_FLIPX);
        if (number == 3) {
            move_sprite(count + usedspr, (length - count + 2) * 8, 120);
        } else {
            move_sprite(count + usedspr, (length - count + 12) * 8,
                48 + number * 16);
        }
    }
    set_sprite_tile(usedspr, 1);
    usedspr = usedspr + length + 2;
    return usedspr;
}
void drawscore(unsigned int scorebak) {
    int tile;
    int length;
    int digit;
    length = 0;

    HIDE_SPRITES;
    while (scorebak != 0) {
        digit = scorebak % 10;
        scorestr[length] = digit;
        scorebak = scorebak / 10;
        length = length + 1;
    }
    for (count = length; count >= 0; count--) {
        tile = scorestr[count - 1] + 55;
        set_sprite_tile(count + 25, tile);
        move_sprite(count + 25, (length - count + 1) * 8 + 2, 150);
    }
    set_sprite_tile(25, 55);
    SHOW_SPRITES;
}

void playhi() {
    NR21_REG = 0x81;
    NR22_REG = 0x83;
    NR23_REG = 0xD7;
    NR24_REG = 0x86;
}

void prntscore(unsigned int score) {
    int usedspr;

    waitpad(J_A);
    ENABLE_RAM_MBC1;

    if (score > threerank) {playhi();}

    DISPLAY_OFF;
    set_bkg_data(0, 40, font);
    set_bkg_tiles(0, 0, 20, 18, score_map);
    DISPLAY_ON;

    set_sprite_data(0, 40, font);

    for (count = 0; count <= 39; count++) {
        set_sprite_tile(count, 0);
        move_sprite(count, 152, 136);
    }

    usedspr = 0;
    usedspr = drawfinal(score, 3, usedspr);

    if (onerank < 0) {onerank = 0;}
    if (tworank < 0) {tworank = 0;}
    if (threerank < 0) {threerank = 0;}

    if (onerank > 0) {
        usedspr = drawfinal(onerank, 0, usedspr);
        set_sprite_tile(usedspr - 1, oneinit);
        set_sprite_prop(usedspr - 1, get_sprite_prop(usedspr - 1) & ~S_FLIPX);
        move_sprite(usedspr - 1, 56, 48);
    }
    if (tworank > 0) {
        usedspr = drawfinal(tworank, 1, usedspr + 1);
        set_sprite_tile(usedspr - 1, twoinit);
        set_sprite_prop(usedspr - 1, get_sprite_prop(usedspr - 1) & ~S_FLIPX);
        move_sprite(usedspr - 1, 56, 64);
    }
    if (threerank > 0) {
        usedspr = drawfinal(threerank, 2, usedspr + 1);
        set_sprite_tile(usedspr - 1, threeinit);
        set_sprite_prop(usedspr - 1, get_sprite_prop(usedspr - 1) & ~S_FLIPX);
        move_sprite(usedspr - 1, 56, 80);
    }

    SHOW_SPRITES;
    waitpad(J_START);

    if (score > 0) {
        if (score > threerank) {
            if (score > tworank) {
                if (score > onerank) {
                    threerank = tworank;
                    threeinit = twoinit;
                    tworank = onerank;
                    twoinit = oneinit;
                    onerank = score;
                    keyboard();
                    oneinit = initial;
                } else {
                    threerank = tworank;
                    threeinit = twoinit;
                    tworank = score;
                    keyboard();
                    twoinit = initial;
                }
            } else {
                threerank = score;
                keyboard();
                threeinit = initial;
            }
        }
    }
    DISABLE_RAM_MBC1;
}

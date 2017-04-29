//
//  viewutil.c
//  cbook
//
//  Created by Mebius on 2017/4/29.
//  Copyright © 2017年 ashan. All rights reserved.
//

#include "viewutil.h"

void init_setting()
{
    setlocale(LC_ALL,"");
    initscr();
    noecho();
    raw();
    start_color();
    curs_set(0);
    keypad(stdscr,TRUE);
}

void init_color_theme()
{
    init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    init_pair(2, COLOR_GREEN,COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_GREEN);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_RED,COLOR_BLACK);
}

void printw_color_c(int color,const char *format,char* context)
{
    attron(COLOR_PAIR(color));
    printw(format,context);
    attroff(COLOR_PAIR(color));
}

void printw_color_i(int color,const char *format,int context)
{
    attron(COLOR_PAIR(color));
    printw(format,context);
    attroff(COLOR_PAIR(color));
}

void showHelp(int height)
{
    move(height-1,0);
    printw_color_c(1,"%s",HELP);
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    return local_win;
}

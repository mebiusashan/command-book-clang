//
//  viewutil.h
//  cbook
//
//  Created by Mebius on 2017/4/29.
//  Copyright © 2017年 ashan. All rights reserved.
//

#ifndef viewutil_h
#define viewutil_h

#include <stdio.h>
#include <locale.h>
#include "ncurses.h"

#define HELP " Menu:m Up/Prev:k Down/Next:j Go:enter Quit:q --- copyright © ashan.org "

void init_setting();
void init_color_theme();
void printw_color_c(int color,const char *format,char* context);
void printw_color_i(int color,const char *format,int context);
void showHelp(int height);
WINDOW *create_newwin(int height, int width, int starty, int startx);

#endif /* viewutil_h */

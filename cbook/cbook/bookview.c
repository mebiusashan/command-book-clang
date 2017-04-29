//
//  BookView.c
//  cbook
//
//  Created by Mebius on 2017/4/27.
//  Copyright © 2017年 ashan. All rights reserved.
//

#include "bookview.h"

char* path;
char* name;
WINDOW *bookMain_win;

void showBookView()
{
    int w,h;
    getmaxyx(stdscr, h, w);
    
    bookMain_win = create_newwin(h-1, w, 0, 0);
    printw_color_c(2,"%s",path);
    printw_color_c(2,"%s",name);
}

void set_book_path(char* _name, char* _path, int p)
{
    path = _path;
    name = _name;
}

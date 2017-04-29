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
FILE* boop_fp;
struct bookc* bookc;

void init_book(int w,int h)
{
    if(bookMain_win==NULL)
    {
        bookMain_win = create_newwin(h-1, w, 0, 0);
    }
}

void open_book()
{
    
}

void show_book_title(char* book_name, char* prog)
{
    move(0,2);
    printw_color_c(2,"[ %s ] [ ",book_name);
    printw_color_c(5,"%s",prog);
    printw_color_c(2,"%s"," ]");
}

void showBookView()
{
    
    int w,h;
    getmaxyx(stdscr, h, w);
    init_book(w,h);
    box(bookMain_win, 0 , 0);
    wrefresh(bookMain_win);
    show_book_title(bookc->name, bookc->progress);
    
    showHelp(h);
}

void set_book_path(struct bookc* _bookc)
{
    bookc = _bookc;
}

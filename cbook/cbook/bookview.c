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
FILE* book_fp;
struct bookc* bookc;
WINDOW *text_win;

void init_book(int w,int h)
{
    if(bookMain_win==NULL)
    {
        bookMain_win = create_newwin(h-1, w, 0, 0);
        //text_win = newwin(h-1, w, 0, 0);
        text_win = newwin(h-3, w-2, 1, 1);
    }
}

void open_book()
{
    book_fp = fopen(bookc->path, "r");
    if(book_fp==NULL)
    {
        move(1,2);
        printw_color_c(2,"Error: book file read is faild: %s",bookc->path);
        return;
    }
    
    int rel =fseek(book_fp, bookc->bp->point, SEEK_SET);
    if(rel==-1)
    {
        move(1,2);
        printw_color_c(2,"Error: book file seek error: %s",bookc->path);
        return;
    }
    
    int w,h;
    getmaxyx(text_win, h, w);
    
    int cx,cy;
    getyx(text_win, cy, cx);
    wchar_t crel=0;
    while (cy<h-1) {
        if(cx>=(w-1)) {
            waddch(text_win, '\n');
            getyx(text_win, cy, cx);
        }
        rel = fgetc(book_fp);
        if(crel==EOF) break;
        waddch(text_win, rel);
        getyx(text_win, cy, cx);
        
        
    }
    
    wrefresh(text_win);
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
    open_book();
    showHelp(h);
}

void set_book_path(struct bookc* _bookc)
{
    bookc = _bookc;
}

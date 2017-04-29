//
//  ViewManger.c
//  cbook
//
//  Created by Mebius on 2017/4/27.
//  Copyright © 2017年 ashan. All rights reserved.
//

#include "viewmanger.h"

//
void backMenu();
void next();
void prev();
void enter();
void ref();
void openBook(int index);
void initKeyboard();

int win = MENU_WIN;
struct bookc* head;
int booknum = 0;

void initview(struct bookc* bc,int _num)
{
    head = bc;
    booknum = _num;
    init_setting();
    init_color_theme();
    ref();
    initKeyboard();
    endwin();
}

void initKeyboard()
{
    int ch = getch();
    while (ch!='q'&&ch!=27) {
        switch (ch) {
            case 'j':
                next();
                break;
            case 'k':
                prev();
                break;
            case 'm':
                backMenu();
                break;
            case 32:
                next();
                break;
            case 10:
                enter();
                break;
            default:
                break;
        }
        ch = getch();
    }
}

void ref()
{
    refresh();
    if(win==MENU_WIN)
    {
        showMenuView(head, booknum);
    }
    else
    {
        showBookView();
    }
}

void next()
{
    if(win==MENU_WIN)
    {
        nextMenu();
    }
    else
    {
        
    }
}

void prev()
{
    if(win==MENU_WIN)
    {
        prevMenu();
    }
    else
    {
        
    }
}


void backMenu()
{
    if(win==BOOK_WIN)
    {
        clear();
        win=MENU_WIN;
        ref();
    }
}


void enter()
{
    clear();
    if(win==MENU_WIN)
    {
        int curIndex = enterMenu();
        openBook(curIndex);
        win=BOOK_WIN;
    }
    ref();
}

void openBook(int index)
{
    struct bookc* cur = head;
    for (int i=0; i<index; i++) {
        cur = cur->next;
    }
    set_book_path(cur->name , cur->path,cur->bp->point);
}



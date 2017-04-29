//
//  ViewManger.c
//  cbook
//
//  Created by Mebius on 2017/4/27.
//  Copyright © 2017年 ashan. All rights reserved.
//

#include "ViewManger.h"

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

void initview(struct bookc* bc)
{
    head = bc;
    setlocale(LC_ALL,"");
    initscr();
    noecho();
    raw();
    start_color();
    curs_set(0);
    keypad(stdscr,TRUE);
    
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
                //next
                next();
                break;
            case 'k':
                prev();
                break;
            case 'm':
                //
                backMenu();
                break;
            case 32:
                //space
                next();
                break;
            case 10:
                //ENTER
                enter();
                break;
            default:
                //printf("key is Down:%d\n",ch);
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
        showMenuView(head);
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
        win = MENU_WIN;
        showMenuView(head);
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
    else
    {
        win=MENU_WIN;
    }
    ref();
}

void openBook(int index)
{
    
}



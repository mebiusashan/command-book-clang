//
//  ListView.c
//  cbook
//
//  Created by Mebius on 2017/4/27.
//  Copyright © 2017年 ashan. All rights reserved.
//

#include "menuview.h"

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;
    
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);		/* 0, 0 gives default characters
                                 * for the vertical and horizontal
                                 * lines			*/
    wrefresh(local_win);		/* Show that box 		*/
    
    return local_win;
}

void showTitle(int num)
{
    move(0,2);
    init_pair(6, COLOR_RED,COLOR_BLACK);
    init_pair(2, COLOR_GREEN,COLOR_BLACK);
    attron(COLOR_PAIR(2));
    printw(" CBook 共[");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(6));
    printw("%d",num+1);
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(2));
    printw("]本图书 ");
    attroff(COLOR_PAIR(2));
}

void showHelp(int h)
{
    move(h-1,0);
    init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    attron(COLOR_PAIR(1));
    printw(HELP);
    attroff(COLOR_PAIR(1));
}

MENU *my_menu;
WINDOW *my_menu_win;
void showMenu(struct bookc* head,int w,int h)
{
    int num = 0;
    
    ITEM **my_items;
    my_items = (ITEM **)calloc(47 + 1, sizeof(ITEM *));
    
    struct bookc* cur = head;
    while(cur->next!=NULL)
    {
        my_items[num] = new_item(cur->progress, cur->name);
        cur = cur->next;
        num++;
    }
    my_items[47] = (ITEM *)NULL;
    my_menu = new_menu((ITEM **)my_items);
    
    my_menu_win = newwin(h-3, w-2, 1, 1);
    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win, 6, w-2, 3, 1));
    set_menu_format(my_menu, h-3, 1);
    set_menu_mark(my_menu, " -> ");
    
    init_pair(3, COLOR_WHITE, COLOR_GREEN);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    set_menu_back(my_menu, COLOR_PAIR(4));
    set_menu_fore(my_menu, COLOR_PAIR(3)|A_BOLD);
    
    post_menu(my_menu);
    wrefresh(my_menu_win);
    
    showTitle(num);
}

void nextMenu()
{
    menu_driver(my_menu, REQ_DOWN_ITEM);
    wrefresh(my_menu_win);
}

void prevMenu()
{
    menu_driver(my_menu, REQ_UP_ITEM);
    wrefresh(my_menu_win);
}

void showMenuView(struct bookc* head)
{
    int w,h;
    getmaxyx(stdscr, h, w);
    
    WINDOW *my_win;
    my_win = create_newwin(h-1, w, 0, 0);
   
    showMenu(head,w,h);
    showHelp(h);
}

int enterMenu()
{
    return current_item(my_menu)->imenu->curitem->index;
}

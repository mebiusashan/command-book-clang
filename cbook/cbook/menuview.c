//
//  ListView.c
//  cbook
//
//  Created by Mebius on 2017/4/27.
//  Copyright © 2017年 ashan. All rights reserved.
//

#include "menuview.h"


WINDOW *menuMain_win;
MENU *my_menu;
WINDOW *my_menu_win;
ITEM **my_items;
int num = 0;

void showMenuView(struct bookc* head, int _num)
{
    num = _num;
    int w,h;
    getmaxyx(stdscr, h, w);
    
    initMenu(w,h);
    box(menuMain_win, 0 , 0);
    wrefresh(menuMain_win);
    
    showMenu(head,w,h);
    showTitle(num);
    showHelp(h);
}

void initMenu(int w, int h)
{
    if( menuMain_win==NULL )
    {
        menuMain_win = create_newwin(h-1, w, 0, 0);
    }
}

void inin_menu_win(struct bookc* head,int w,int h)
{
    if(my_items==NULL)
    {
        my_items = (ITEM **)calloc(num + 1, sizeof(ITEM *));
        
        struct bookc* cur = head;
        int index = 0;
        while(cur->next!=NULL)
        {
            my_items[index] = new_item(cur->progress, cur->name);
            cur = cur->next;
            index++;
        }
        my_items[num] = (ITEM *)NULL;
        my_menu = new_menu((ITEM **)my_items);
        
        my_menu_win = newwin(h-3, w-2, 1, 1);
        set_menu_win(my_menu, my_menu_win);
        set_menu_sub(my_menu, derwin(my_menu_win, 6, w-2, 3, 1));
        set_menu_format(my_menu, h-3, 1);
        set_menu_mark(my_menu, " -> ");
        
        set_menu_back(my_menu, COLOR_PAIR(4));
        set_menu_fore(my_menu, COLOR_PAIR(3)|A_BOLD);
        
        
        post_menu(my_menu);
    }
}

void showMenu(struct bookc* head,int w,int h)
{
    inin_menu_win(head,w,h);
    menu_driver(my_menu, REQ_FIRST_ITEM);
    wrefresh(my_menu_win);
}

void showTitle(int num)
{
    move(0,2);
    printw_color_c(2,"%s"," CBook 共[");
    printw_color_i(5,"%d",num+1);
    printw_color_c(2,"%s","]本图书 ");
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

int enterMenu()
{
    return current_item(my_menu)->imenu->curitem->index;
}

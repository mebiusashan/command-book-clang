//
//  BookView.c
//  cbook
//
//  Created by Mebius on 2017/4/27.
//  Copyright © 2017年 ashan. All rights reserved.
//

#include "BookView.h"


WINDOW *acreate_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;
    
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);		/* 0, 0 gives default characters
                                 * for the vertical and horizontal
                                 * lines			*/
    wrefresh(local_win);		/* Show that box 		*/
    
    return local_win;
}


void showBookView()
{
    int w,h;
    getmaxyx(stdscr, h, w);
    
    WINDOW *my_win;
    my_win = acreate_newwin(h-1, w, 0, 0);
    //printw("fadfad");
}

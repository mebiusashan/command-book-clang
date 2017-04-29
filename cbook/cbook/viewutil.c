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

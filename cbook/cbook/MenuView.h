//
//  ListView.h
//  cbook
//
//  Created by Mebius on 2017/4/27.
//  Copyright © 2017年 ashan. All rights reserved.
//

#ifndef MenuView_h
#define MenuView_h

#include <stdio.h>
#include "ncurses.h"
#include "menu.h"
#include "config.h"

#define HELP " 目录:m 上一行/上翻页:k 下一行/下翻页:j 确认:enter 退出:q copyright © ashan.org "

void showMenuView(struct bookc* head);
void nextMenu();
void prevMenu();
int enterMenu();


#endif /* ListView_h */

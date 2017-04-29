//
//  ListView.h
//  cbook
//
//  Created by Mebius on 2017/4/27.
//  Copyright © 2017年 ashan. All rights reserved.
//

#ifndef menuview_h
#define menuview_h

#include <stdio.h>
#include "ncurses.h"
#include "menu.h"
#include "config.h"
#include "viewutil.h"


void showMenuView(struct bookc* head, int num);
void showMenu(struct bookc* head,int w,int h);
void initMenu(int w, int h);
void nextMenu();
void prevMenu();
int  enterMenu();
void showTitle(int num);


#endif /* ListView_h */

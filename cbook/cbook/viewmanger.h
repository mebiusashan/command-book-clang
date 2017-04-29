//
//  ViewManger.h
//  cbook
//
//  Created by Mebius on 2017/4/27.
//  Copyright © 2017年 ashan. All rights reserved.
//

#ifndef viewmanger_h
#define viewmanger_h

#include <stdio.h>
#include <locale.h>
#include "ncurses.h"

#include "menuview.h"
#include "bookview.h"
#include "viewutil.h"

#define MENU_WIN 0
#define BOOK_WIN 1

//int win = MENU_WIN;
void initview(struct bookc* bc);




#endif /* ViewManger_h */

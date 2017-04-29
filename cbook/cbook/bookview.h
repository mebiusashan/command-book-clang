//
//  BookView.h
//  cbook
//
//  Created by Mebius on 2017/4/27.
//  Copyright © 2017年 ashan. All rights reserved.
//

#ifndef bookview_h
#define bookview_h

#include <stdio.h>
#include "ncurses.h"

#include "viewutil.h"

void showBookView();
void set_book_path(char* name, char* path, int p);

#endif /* BookView_h */

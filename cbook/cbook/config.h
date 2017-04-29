//
//  config.h
//  cbook
//
//  Created by Mebius on 2017/4/23.
//  Copyright © 2017年 ashan. All rights reserved.
//

#ifndef config_h
#define config_h


#define READ_DATA_SIZE	1024
#define MD5_SIZE		16
#define MD5_STR_LEN		(MD5_SIZE * 2)

int Compute_file_md5(const char *file_path, char *md5_str);


//------------------------------------------------------------------------------

#include <dirent.h>

#include "Math.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>

#define CBOOK_CONFIG "/cbook.config"
#define CBOOK_POINT_CONFIG "/zcbookp.config.txt"

struct bookc {
    char *path;
    char *name;
    char *progress;
    unsigned int len_r;
    struct bookp *bp;
    struct bookc* next;
};
struct bookp {
    char *md5;
    unsigned int point;
};

int readConfig(char** bpath);
struct bookc *scanDir(char* path);
void readPointConfig();
void writePointConfig();

#endif /* config_h */

//
//  config.c
//  cbook
//
//  Created by Mebius on 2017/4/23.
//  Copyright © 2017年 ashan. All rights reserved.
//

#include "config.h"
#include "md5.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int Compute_file_md5(const char *file_path, char *md5_str)
{
    int i;
    int fd;
    int ret;
    unsigned char data[READ_DATA_SIZE];
    unsigned char md5_value[MD5_SIZE];
    MD5_CTX md5;
    
    fd = open(file_path, O_RDONLY);
    if (-1 == fd)
    {
        perror("open");
        return -1;
    }
    
    // init md5
    MD5Init(&md5);
    
    while (1)
    {
        ret = read(fd, data, READ_DATA_SIZE);
        if (-1 == ret)
        {
            perror("read");
            return -1;
        }
        
        MD5Update(&md5, data, ret);
        
        if (0 == ret || ret < READ_DATA_SIZE)
        {
            break;
        }
    }
    
    close(fd);
    
    MD5Final(&md5, md5_value);
    
    for(i = 0; i < MD5_SIZE; i++)
    {
        //printf("%d-%c-%d\n",i,md5_value[i],md5_str + i*2);
        snprintf(md5_str + i*2, 2+1, "%02x", md5_value[i]);
    }
    md5_str[MD5_STR_LEN] = '\0'; // add end
    
    return 0;
}

//------------------------------------------------------------------------------


#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

/**
 TODO: 如果路径过长，bpath将内容不足，超出1024则会出错
 */
int readConfig(char** bpath)
{
    struct passwd *pw = getpwuid(getuid());
    char *configRoot = (char *)malloc(1+strlen(pw->pw_dir)+strlen(CBOOK_CONFIG));
    strcpy(configRoot, pw->pw_dir);
    strcat(configRoot, CBOOK_CONFIG);
    FILE *fd = fopen(configRoot, "r");
    if(fd==NULL) return 1;
    
    char* path = (char *)malloc(1024*sizeof(char *));
    int count = 0;
    char ch = getc(fd);
    
    while((ch!='\n')&&(ch!=EOF))
    {
        path[count] = ch;
        ch = getc(fd);
        count++;
    }
    path[count] = '\0';
    *bpath = path;
    path = NULL;
    free(configRoot);
    return 0;
}

//------------------------------------------------------------------------------

struct bookc *scanDir(char* path)
{
    DIR *d;
    if(!(d = opendir(path))) return NULL;
    
    struct dirent *file;
    size_t pathlen = strlen(path);
    struct bookc* head = NULL;
    struct bookc* cur = NULL;
    
    struct stat st;
    while((file = readdir(d)) != NULL)
    {
        if(strncmp(file->d_name, ".", 1) == 0)
            continue;
        
        struct bookc* bc = (struct bookc*)malloc(sizeof(struct bookc));
        bc->path = (char*)malloc(1 + pathlen + file->d_namlen);
        bc->name = (char*)malloc(1 + file->d_namlen);
        bc->progress = (char *)malloc(5*sizeof(char*));
        bc->bp = (struct bookp*)malloc(sizeof(struct bookp));
        bc->bp->md5 = (char*)malloc(MD5_STR_LEN+1);
        bc->bp->point = 0;
        bc->next = NULL;
        
        strcpy(bc->name, file->d_name);
        strcpy(bc->path, path);
        strcat(bc->path, file->d_name);
        
        stat(bc->path, &st);
        bc->len_r = st.st_size;
        
        if(Compute_file_md5(bc->path, bc->bp->md5)!=0)
        {
            printf("文件读取失败:%s\n",bc->path);
            closedir(d);
            return NULL;
        }
        
        if(cur!=NULL) cur->next = bc;
        cur = bc;
        
        if(head==NULL) head = bc;
    }
    
    closedir(d);
    return head;
}

void setPointByMD5(char* md5, unsigned int p, struct bookc* head)
{
    struct bookc* cur = head;
    while(cur->next!=NULL)
    {
        if(strcmp(cur->bp->md5,md5)==0){
            cur->bp->point = p;
            float prog = (float)p/cur->len_r*100;
            prog = ceilf(prog);
            if(prog<10){
                sprintf(cur->progress,"  %d%%",(int)prog);
            }else if(prog<100){
                sprintf(cur->progress," %d%%",(int)prog);
            }else{
                cur->progress = "100%";
            }
            break;
        }
        cur = cur->next;
    }
}

int readPointConfig(struct bookc* head)
{
    struct passwd *pw = getpwuid(getuid());
    char *configRoot = (char *)malloc(1+strlen(pw->pw_dir)+strlen(CBOOK_POINT_CONFIG));
    
    strcpy(configRoot, pw->pw_dir);
    strcat(configRoot, CBOOK_POINT_CONFIG);
    
    int num = 0;
    
    if(access(configRoot, F_OK)==-1)
    {
        num = writePointConfig(configRoot, head);
    }
    else
    {
        //读取文件，然后将里面的数据赋值给现在内存中的数据
        FILE *fd= fopen(configRoot, "r");
        if(fd==NULL) -1;
        struct bookp* bp = (struct bookp*)malloc(sizeof(struct bookp));
        bp->md5 = (char*)malloc(MD5_STR_LEN+1);
        bp->point = 0;
        
        while( fscanf(fd,"%s %d ",bp->md5,&bp->point)!=EOF) {
            setPointByMD5(bp->md5, bp->point, head);
            num++;
        }
        fclose(fd);
    }
    return num;
}

int writePointConfig(char* path, struct bookc* head)
{
    int num = 0;
    FILE *fd= fopen(path, "w");
    struct bookc* cur = head;
    while(cur->next!=NULL)
    {
        fprintf(fd, "%s %d ",cur->bp->md5,cur->bp->point);
        cur = cur->next;
        num++;
    }
    fclose(fd);
    return num;
}


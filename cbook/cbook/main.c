#include "cbook.h"

#define CONFIG_ERR "警告：尚未配置书库路径。\ncbook <book library dir path>\n"
#define BOOKDIR_ERR "错误：书库路径不存在:%s\ncbook <book library dir path>\n"

//------------------------------------------------------------------------------

int main()
{
    char *url = NULL;
    if(readConfig(&url)==1)
    {
        printf(CONFIG_ERR);
        free(url);
        return 0;
    }
    
    struct bookc* bc = scanDir(url);
    if(scanDir(url)==NULL)
    {
        printf(BOOKDIR_ERR,url);
        free(url);
        return 0;
    }
    
    readPointConfig(bc);
    initview(bc);
    
    return 0;
}


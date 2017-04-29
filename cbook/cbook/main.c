#include "cbook.h"

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
    
    int rel = readPointConfig(bc);
    if(rel==-1)
    {
        printf(CONFIG_P_ERR);
        return 0;
    }
        
    initview(bc,rel);
    
    return 0;
}


#include "header.h"

string pwd(){
    char path[1024];
    if(getcwd(path, sizeof(path))!=NULL){
        // cout<<path;
        string s=path;
        return s;
    }
    else{
        perror("error getting pwd");
        exit(1);
    }
}

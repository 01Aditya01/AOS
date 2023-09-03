#include "header.h"

void callCwd(const char* path){
    string temp_dir=pwd();
    if(chdir(path)!=0){
        perror("error changing directory");
    }
    else{
        prev_dir=temp_dir;
    }
}

void chDirectory(vector<string>& arg){
    // cout<<"path: "<<path<<endl;
    int n=arg.size();
    if(n>2){
        cerr<<"Invalid arguments"<<endl;
        return;
    }

    string cwd=pwd();
    // if((arg[1]==".." || arg[1]=="../") && cwd==home_directory_path){
    //     cout<<cwd<<endl;
    // }
    if(n==1 || arg[1]=="~"){
        // cout<<home_directory_path<<endl;
        const char* path=home_directory_path.c_str();
        callCwd(path);
    }
    else if(arg[1]=="-"){
        const char* path=prev_dir.c_str();
        callCwd(path);
    }
    // else if(arg)
    else{
        const char* path=arg[1].c_str();
        callCwd(path);
        // if(chdir(path)!=0){
        //     perror("error changing directory");
        // }
    }

    // cout<<pwd()<<endl;
}

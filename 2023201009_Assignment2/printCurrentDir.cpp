#include "header.h"

bool pathCmp(string home, string cur){

    int n1=home.length(), n2=cur.length();
    if(n1>n2) return false;
    
    for(int i=0;i<n1;i++){
        if(home[i]!=cur[i]) return false;
    }
    return true;
}

void printCurrentDir(char* argv[]){


    string curDir=pwd();
    if(!pathCmp(home_directory_path, curDir)){
        cout<<curDir<<"$ ";
    }
    // cout<<"curDir len: "<<curDir.length()<<endl;
    // cout<<"home_len: "<<home_path_len<<endl;
    // cout<<"home_path: "<<home_directory_path<<endl;
    // cout<<"curDir: "<<curDir<<endl;
    // home_path_len=curDir.length();
    else{
        cout<<"~"<<curDir.substr(home_path_len)<<"$ ";
    }

    // cout << "Executable Path: " << executablePath << std::endl;
    // cout << "Executable Directory: " << executableDirectory << std::endl;

}

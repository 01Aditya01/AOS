#include "header.h"

bool search(string dir_path, string target_file){

    DIR* directory = opendir(dir_path.c_str());
    if (!directory){
        cerr << "Error opening directory " << dir_path << std::endl;
        return false;
    }

    struct dirent* file;

    while((file = readdir(directory))!=NULL){
        char* file_name=file->d_name;
        struct stat file_info;
        if(strcmp(file_name, ".")==0 || strcmp(file_name, "..")==0) continue;
        string file_path=dir_path+"/"+string(file_name);
        if(stat(file_path.c_str(), &file_info)!=0){
            cout<<file_name<<endl;
            perror("stat");
            continue;
        }
        if(string(file_name)==target_file){
            return true;
        }
        if(S_ISDIR(file_info.st_mode)){
            if(search(dir_path+"/"+string(file_name), target_file)) return true;
        }
    }
    return false;
}
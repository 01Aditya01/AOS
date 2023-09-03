#include "header.h"

void getPermission(string file_name, string dir_path){
    
    string file_path=dir_path+"/"+file_name;
    // cout<<file_path<<endl;
    struct stat fileStat;
    if(stat(file_path.c_str(), &fileStat)==-1){
        perror("error getting file info");
        return;
    }
    
    // owner
    string permissions;
    permissions.push_back(S_ISDIR(fileStat.st_mode) ? 'd' : '-');
    permissions.push_back((fileStat.st_mode & S_IRUSR) ? 'r' : '-');
    permissions.push_back((fileStat.st_mode & S_IWUSR) ? 'w' : '-');
    permissions.push_back((fileStat.st_mode & S_IXUSR) ? 'x' : '-');

    // group
    permissions.push_back((fileStat.st_mode & S_IRGRP) ? 'r' : '-');
    permissions.push_back((fileStat.st_mode & S_IWGRP) ? 'w' : '-');
    permissions.push_back((fileStat.st_mode & S_IXGRP) ? 'x' : '-');

    // others
    permissions.push_back((fileStat.st_mode & S_IROTH) ? 'r' : '-');
    permissions.push_back((fileStat.st_mode & S_IWOTH) ? 'w' : '-');
    permissions.push_back((fileStat.st_mode & S_IXOTH) ? 'x' : '-');

    cout<<permissions<<" "<<fileStat.st_nlink<<" ";

    struct passwd* owner = getpwuid(fileStat.st_uid);
    struct group* grp = getgrgid(fileStat.st_gid);

    cout<<owner->pw_name<<" "<<grp->gr_name<<" "<<fileStat.st_size << " ";

    char timebuf[80];
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&fileStat.st_mtime));
    cout << timebuf << " ";
    cout << file_name<<endl;
    return;
}

int listFile(const char* dir_path, string all_flags, bool flag){

    if(string(dir_path)=="~") dir_path=home_directory_path.c_str();

    DIR* directory = opendir(dir_path);
    if (!directory) {
        cerr << "Error opening directory " << dir_path << std::endl;
        return 1;
    }

    if(flag) cout<<dir_path<<":"<<endl;
    struct dirent* file;
    vector<string> file_name;

    while((file = readdir(directory))){
        file_name.push_back(file->d_name);
    }

    sort(file_name.begin(), file_name.end());
    int n=file_name.size();
    if(all_flags=="l"){
        for(int i=0;i<n;i++){
            if(file_name[i][0]!='.')
                getPermission(file_name[i], dir_path);
        }
    }

    else if(all_flags=="a"){
        for(int i=0;i<n;i++){
            cout<<file_name[i]<<endl;
        }
    }

    else if(all_flags=="la" || all_flags=="al"){
        for(int i=0;i<n;i++){
            getPermission(file_name[i], dir_path);
        }
    }

    else{
        for(int i=0;i<n;i++){
            if(file_name[i][0]!='.')
            cout<<file_name[i]<<endl;
        }
    }
    cout<<endl;
    return 0;
}

void ls(vector<string>& arg){
    int n=arg.size();

    unordered_set<string> flag={"-l","-a","-la","-al"};

    // all_flags storing all flags as string
    string all_flags;
    int flag_count=0;
    for(int i=1;i<n;i++){
        if(flag.find(arg[i])!=flag.end()) {
            flag_count+=1;
            all_flags.append(arg[i].substr(1));
            }
    }
    if(flag_count==n-1){
        listFile(".",all_flags,false);
        return;
    }
    bool multiple_dir=false;
    if(n-1-flag_count>=2) multiple_dir=true;

    for(int i=1;i<n;i++){
        if(flag.find(arg[i])==flag.end()) listFile(arg[i].c_str(),all_flags,multiple_dir);
    }

    
}
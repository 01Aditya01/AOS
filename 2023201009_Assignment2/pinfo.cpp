#include "header.h"

void pinfo(vector<string> &arg){
    string pidStr;
    pid_t my_pid;
    if(arg.size()==1){
        pidStr="self";
        my_pid=getpid();
    }
    else{
        pidStr=string(arg[1]);
        my_pid=stoi(arg[1]);
    }
    pid_t fg_pgid=tcgetpgrp(STDIN_FILENO);
    pid_t my_pgid=getpgid(my_pid);


    string fileStatus = "/proc/" + pidStr + "/status";

    ifstream file(fileStatus);
    if(!file){
        cerr<<"error opening file"<<endl;
        return;
    }

    string line;
    cout<<"Pid: "<<my_pid<<endl;
    while (getline(file, line)) {
        // cout << line << endl; // Print each line from the file
        if(line.compare(0,6,"State:")==0){
            cout<<"fg_pgid="<<fg_pgid<<endl;
            cout<<"my_pgid="<<my_pgid<<endl;
            cout<<"Process Status: "<<line.substr(7,1);
            if(fg_pgid==my_pgid) cout<<"+";
            cout<<endl;
        }
        else if(line.compare(0,6,"VmSize:")==0){
            cout<<"memory: "<<line.substr(7)<<endl;
        }
    }

    file.close();

    char buffer[512];
    int len=readlink(("/proc/"+pidStr+"/exe").c_str(), buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        cout << "Executable Path: " << buffer << endl;
    } else {
        cerr << "Error retrieving executable path" << endl;
    }

    
}
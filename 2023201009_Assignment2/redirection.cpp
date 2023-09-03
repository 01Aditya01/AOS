#include "header.h"

bool redirection(vector<string> &arg){

    int n=arg.size();
    bool flag=false;
    int index=n;
    int stdout_fd = dup(STDOUT_FILENO);
    int stdin_fd = dup(STDIN_FILENO);
    for(int i=0;i<n;i++){
        if(arg[i]=="<"){
            flag=true;
            index=min(index,i);
            int fd1 = open(arg[i+1].c_str(),O_RDONLY);
            if(fd1 == -1){
                perror("open");
                return false;
            }
            if(dup2(fd1, STDIN_FILENO) == -1){
                perror("dup2");
                return false;
            }
            close(fd1);
        }
        else if(arg[i]==">"){
            flag=true;
            index=min(index,i);
            int fd2 = open(arg[i+1].c_str(),O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if(fd2 == -1){
                perror("open");
                return false;
            }
            if(dup2(fd2, STDOUT_FILENO) == -1){
                perror("dup2");
                return false;
            }
            close(fd2);
        }
        else if(arg[i]==">>"){
            flag=true;
            index=min(index,i);
            int fd3 = open(arg[i+1].c_str(),O_WRONLY | O_CREAT | O_APPEND, 0644);
            if(fd3 == -1){
                perror("open");
                return false;
            }
            if(dup2(fd3, STDOUT_FILENO) == -1){
                perror("dup2");
                return false;
            }
            close(fd3);
        }
    }
    if(flag==true){
        vector<string> temp = vector<string> (arg.begin(), arg.begin()+index);
        detectCommand(temp);
        dup2(stdin_fd, STDIN_FILENO);
        dup2(stdout_fd, STDOUT_FILENO);
        return true;
    }
    return false;

}
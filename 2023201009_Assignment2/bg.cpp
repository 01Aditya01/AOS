#include "header.h"

int bg(vector<string> &arg){
    pid_t pid= fork();

    if (pid < 0) {
        cerr << "Fork failed." << endl;
        return 1;
    }

    if(pid==0){
        int n=arg.size();
        char* c_arg[n];
        for(int i=0;i<n-1;i++){
            c_arg[i]=const_cast<char*>(arg[i].c_str());  //arg[i].c_str();
            cout<<c_arg[i]<<" ";
        }
        c_arg[n-1]=NULL;
        if(execvp(c_arg[0], c_arg)==-1){
            cerr<<"Execution failed"<<endl;
            return 1;
        }
    }
    else{
        // int status;
        cout<<"child pid: "<<pid<<endl;
        // wait(&status);
    }
    return 0;
}
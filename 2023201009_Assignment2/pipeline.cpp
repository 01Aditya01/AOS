#include "header.h"

void pipeline(){
    
    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed." << endl;
        return 1;
    }
}
#include "header.h"

// using namespace std;
void detectCommand(vector<string>&);


    string home_directory_path;
    int home_path_len;
    string prev_dir;

int main(int argc, char* argv[]){

    prev_dir=pwd();
    filesystem::path executablePath = argv[0];
    filesystem::path absoluteExecutablePath = filesystem::absolute(executablePath);
    // Get the directory path containing the executable
    filesystem::path executableDirectory = absoluteExecutablePath.parent_path();

    home_directory_path=executableDirectory.string();
    home_path_len=home_directory_path.length()-2;
    home_directory_path=home_directory_path.substr(0,home_path_len);
    while(true){
        // cout<<"argv[0]: "<<argv[0]<<endl;
        char *username = getlogin();
        if (username != nullptr) {
            cout <<username<<"@";
        } else {
            cerr << "Error getting username.";
        }
        char hostname[256];
        if (gethostname(hostname, sizeof(hostname)) == 0) {
            cout <<hostname<<":";
        } else {
            cerr << "Error getting hostname.";
        }
        // Get the path of the executable

        printCurrentDir(argv);


        char input[128];
        cin.getline(input,128);

        char* token;
        vector<string> arg;
        token=strtok(input," ");
        while(token!=NULL){
            // string s=token;
            arg.push_back(token);
            token=strtok(NULL," ");
        }
        if(!redirection(arg))
        detectCommand(arg);

        
    }
    return 0;
}
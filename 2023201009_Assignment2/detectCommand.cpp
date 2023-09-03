#include "header.h"
// using namespace std;

void detectCommand(vector<string> &arg){
    // static int count=0;
    // if(count==0){
    //     count+=1;
    //     if(redirection(arg)) {
    //         cout<<"here"<<endl;
    //         return;}
    // }

    if(arg[0]=="echo"){
            // cout<<endl;
            for(int i=1;i<arg.size()-1;i++){
                cout<<arg[i]<<" ";
            }
            cout<<arg.back()<<"\n";

        }

    else if(arg[0]=="pwd"){
        string path = pwd();
        cout<<path<<endl;
    }

    else if(arg[0]=="cd"){
        chDirectory(arg);
    }

    else if(arg[0]=="ls"){
        ls(arg);
    }
    else if(arg.back()=="&"){
        bg(arg);
    }
    else if(arg[0]=="pinfo"){
        pinfo(arg);
    }
    else if(arg[0]=="search"){
        cout<<boolalpha<<search(".",arg[1])<<endl;
    }

    else{
        rest(arg);
    }
    
}
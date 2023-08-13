#include <iostream>
#include <unistd.h>
#include <string.h>
#include <algorithm>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
using namespace std;

long long b_size=100000;
char yes[]="Yes";
int y=strlen(yes);
char no[]="No";
int n=strlen(no);
int fd1, fd2;

// function to check if givern char arrays are reverse
bool isReverse(char buffer1[], char buffer2[]){
    int len=strlen(buffer1);
    for(int i=0;i<len;i++){
        if(buffer1[i]!=buffer2[len-1-i]) return false;
    }
    return true;
}

// function to check if old file and new file are reverse
void checkReverse(int fd1, int fd2){
    char s[]="Whether file contents are reversed in newfile: ";
    char buffer1[b_size];
    char buffer2[b_size];
    write(1,s,strlen(s));
    long long f_size1=lseek(fd1,0,SEEK_END);
    long long f_size2=lseek(fd2,0,SEEK_END);
    lseek(fd1,-f_size1,SEEK_CUR);
    if(f_size1!=f_size2){
        write(1,no,n);
        write(1,"\n",1);
        return;
    }
    // cout << "hello" << endl;
    long long ofst=1;
    long long pos=min(b_size,f_size2);
    while(ofst>0){
        // cout<<true<<endl<<endl;
        ofst=lseek(fd2,-pos,SEEK_CUR);
        if(read(fd1,buffer1,pos)==-1){
            perror("Error reading file: ");
            exit(1);
        }
        if(read(fd2,buffer2,pos)==-1){
            perror("Error reading file: ");
            exit(1);
        };
        if(!isReverse(buffer1, buffer2)){
            write(1,no,n);
            write(1,"\n",1);
            return;
        }
        lseek(fd2,-pos,SEEK_CUR);
        pos=min(b_size,ofst);
    }
    write(1,yes,y);
    write(1,"\n",1);
}

// function to check file/directory permissions
void checkPermissions(const char* path, string file_type){
    struct stat file_info;
    if(stat(path, &file_info)==0){
        // check user permissions
        string s="User has read permissions on " + file_type;
        const char* output1= s.c_str();
        write(1,output1,strlen(output1));
        if(file_info.st_mode & S_IRUSR) write(1,yes,y);
        else write(1,no,n);
        write(1,"\n",1);

        s="User has write permissions on " + file_type;
        const char* output2= s.c_str();
        write(1,output2,strlen(output2));
        if(file_info.st_mode & S_IWUSR) write(1,yes,y);
        else write(1,no,n);
        write(1,"\n",1);

        s="User has execute permissions on " + file_type;
        const char* output3= s.c_str();
        write(1,output3,strlen(output3));
        if(file_info.st_mode & S_IXUSR) write(1,yes,y);
        else write(1,no,n);
        write(1,"\n",1);

        // check group permissions
        s="Group has read permissions on " + file_type;
        const char* output4= s.c_str();
        write(1,output4,strlen(output4));
        if(file_info.st_mode & S_IRGRP) write(1,yes,y);
        else write(1,no,n);
        write(1,"\n",1);

        s="Group has write permissions on " + file_type;
        const char* output5= s.c_str();
        write(1,output5,strlen(output5));
        if(file_info.st_mode & S_IWGRP) write(1,yes,y);
        else write(1,no,n);
        write(1,"\n",1);

        s="Group has execute permissions on " + file_type;
        const char* output6= s.c_str();
        write(1,output6,strlen(output6));
        if(file_info.st_mode & S_IXGRP) write(1,yes,y);
        else write(1,no,n);
        write(1,"\n",1);
        
        // check others permissions
        s="Others has read permissions on " + file_type;
        const char* output7= s.c_str();
        write(1,output7,strlen(output7));
        if(file_info.st_mode & S_IROTH) write(1,yes,y);
        else write(1,no,n);
        write(1,"\n",1);

        s="Others has write permissions on " + file_type;
        const char* output8= s.c_str();
        write(1,output8,strlen(output8));
        if(file_info.st_mode & S_IWOTH) write(1,yes,y);
        else write(1,no,n);
        write(1,"\n",1);

        s="Others has execute permissions on " + file_type;
        const char* output9= s.c_str();
        write(1,output9,strlen(output9));
        if(file_info.st_mode & S_IXOTH) write(1,yes,y);
        else write(1,no,n);
        write(1,"\n\n",2);
    }
    else{
        perror("error- stat");
        exit(1);
    }

}

int main(int argc, char* argv[]){
    if(argc<4){
        char error[]="error: too few arguements given";
        write(1,error,sizeof(error));
        exit(1);
    }
    char s[]="Directory is created: ";
    write(1,s,strlen(s));
    // to check if given directory exists
    if(access(argv[3], F_OK)==0){
        write(1,yes,y);
    }
    else{
        write(1,no,n);
    }
    write(1,"\n",1);
    fd1=open(argv[2],O_RDONLY);
    if(fd1==-1){
        perror("error opening file: ");
        exit(1);
    }
    fd2=open(argv[1],O_RDONLY);
    if(fd2==-1){
        perror("error opening file: ");
        exit(1);
    }
    checkReverse(fd1,fd2);

    checkPermissions(argv[1], "new file: ");
    checkPermissions(argv[2], "old file: ");
    checkPermissions(argv[3], "directory: ");

    if(close(fd1)==-1){
        perror("error closing file: ");
        exit(1);
    }
    if(close(fd2)==-1){
        perror("error closing file: ");
        exit(1);
    }
    return 0;
}
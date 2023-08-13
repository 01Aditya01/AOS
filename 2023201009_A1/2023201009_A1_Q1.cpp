#include<iostream>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include <sys/stat.h>
#include <stdlib.h>

using namespace std;


string input_file_name; 
string output_file_name= "Assignment1_1/1_";
int fd2;

// function to reverse the given block of input file, and write it to the output file
void reverse(char *buffer, int block_size){
    char temp;
    for(int i=0;i<block_size/2;i++){
        temp=buffer[i];
        buffer[i]=buffer[block_size-1-i];
        buffer[block_size-1-i]=temp;
    }
    ssize_t bytes_written = write(fd2, buffer, block_size);
    if(bytes_written==-1){
        perror("error writing file:");
        exit(1);
    }
}
// function to generate output file path
void outputFileName(string& s, string input_file){
    string f_name="";
    int n=input_file.length(),i=n-1;
    while(i>=0 && input_file[i]!='/'){
        f_name.push_back(input_file[i]);
        i--;
    }
    reverse(f_name.begin(), f_name.end());
    s+=f_name;
}


int main(int argc, char *argv[]){
    if(argc<2){
        char error[]="error: input file path not given";
        write(1,error,sizeof(error));
        exit(1);
    }
    outputFileName(output_file_name, argv[1]);

    int new_dir = mkdir("Assignment1_1",0700);
    if(new_dir==-1 && errno!=EEXIST){
        perror("error creating directory:");
        exit(1);
    }
    int fd= open(argv[1],O_RDONLY);
    if(fd==-1){
        perror("error opening file:");
        exit(1);
    }

    fd2=open(output_file_name.c_str(),O_CREAT|O_RDWR|O_APPEND|O_TRUNC,S_IRUSR | S_IWUSR);
    if(fd2==-1){
        perror("error creating file:");
        exit(1);
    }
    if(chmod(output_file_name.c_str(),S_IRUSR | S_IWUSR)==-1){
        perror("error chaninging file permissions:");
        exit(1);
    }

    long long b_size=100000;
    char buffer[b_size];
    long long f_size= lseek(fd,0,SEEK_END);
    long long pos=min(b_size,f_size);
    long long percentage=0;
    long long ofst=1;

    // reading file from end till start in blocks of 100kb
    while(ofst>0){
        ofst= lseek(fd, -pos,SEEK_CUR);
        long long block_size = read(fd,buffer,pos);
        if(block_size==-1){
            perror("error reading file:");
            exit(1);
        }
        // passing the current read block to reverse function
        reverse(buffer,block_size);
        // calculating percentage of output file written
        percentage= ((f_size-ofst)*100)/f_size;
        string p=to_string(percentage)+"%";
        if(ofst!=0) p+='\r';
        write(1, p.c_str(), p.length());

        lseek(fd, -pos,SEEK_CUR);
        pos=min(b_size,ofst);
    }
    write(1,"\n",1);
    if(close(fd)==-1){
        perror("error closing file: ");
        exit(1);
    }
    if(close(fd2)==-1){
        perror("error closing file: ");
        exit(1);
    }
     
    return 0;
}
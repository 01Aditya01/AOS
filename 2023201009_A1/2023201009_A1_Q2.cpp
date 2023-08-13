#include<iostream>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include <sys/stat.h>

using namespace std;


string input_file_name; 
string output_file_name= "Assignment1_2/1_";
int fd2;
long long total_file_size;
long long file_written=0;

// function to write the given character array into output file 
void write_file(int fd,char *buffer, int block_size){
    ssize_t bytes_written = write(fd2, buffer, block_size);
    if(bytes_written==-1){
        perror("error writing file:");
        exit(1);
    }
    file_written+=bytes_written;
    long long percentage=0;
    // calcultaing percentage of file written uptill now and printing it to terminal
    percentage= (file_written*100)/total_file_size;
    write(1,"\r",1);
    string p=to_string(percentage)+"%";
    write(1, p.c_str(), p.length());
}

// function to read from input file from start to en end index and writing it to output file
void read_file(long long start, long long end, int fd){
    long long b_size=100000;
    char buffer[b_size];
    lseek(fd,start,SEEK_SET);
    long long pos;
    long long ofst=end-1;
    while(ofst<end){
        ofst= lseek(fd, 0,SEEK_CUR);
        pos=min(b_size,end-ofst+1);
        long long block_size = read(fd,buffer,pos);
        if(block_size==-1){
            perror("error reading file:");
            exit(1);
        }
        write_file(fd2,buffer,block_size);
    }
}

// function to reverse the given character array
void reverse(char *buffer, int block_size){
    char temp;
    for(int i=0;i<block_size/2;i++){
        temp=buffer[i];
        buffer[i]=buffer[block_size-1-i];
        buffer[block_size-1-i]=temp;
    }
}

// function to reverse a part of file between start and end index and writing it to output file
void partialReverse(long long start, long long end, int fd){
    long long b_size=100000;
    char buffer[b_size];
    lseek(fd,end+1,SEEK_SET);
    // cout << pos1 ;
    long long pos=min(b_size,end-start+1);
    long long ofst=start+1;
    while(ofst>start){
        // cout<<1;
        ofst= lseek(fd, -pos,SEEK_CUR);
        long long block_size = read(fd,buffer,pos);
        if(block_size==-1){
            perror("error reading file:");
        }
        reverse(buffer,block_size);
        write_file(fd2,buffer,block_size);
        lseek(fd, -pos,SEEK_CUR);
        pos=min(b_size,ofst-start);
    }

}
// function to determine output file path
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
    if(argc<4){
        char error[]="error: too few arguements given";
        write(1,error,sizeof(error));
        exit(1);
    }
    outputFileName(output_file_name, argv[1]);

    // creating new directory
    int new_dir = mkdir("Assignment1_2",0700);
    if(new_dir==-1 && errno!=EEXIST){
        perror("error creating directory:");
        exit(1);
    }
    // opening input file
    int fd= open(argv[1],O_RDONLY);
    if(fd==-1){
        perror("error opening file:");
        exit(1);
    }
    // finding input file size
    struct stat fileInfo;
    if (stat(argv[1], &fileInfo) == 0) {
        total_file_size =(long long)fileInfo.st_size;
    } else {
        perror("Error");
        exit(1);
    }
    // opening output file
    fd2=open(output_file_name.c_str(),O_CREAT|O_RDWR|O_APPEND|O_TRUNC,S_IRUSR | S_IWUSR);
    if(fd2==-1){
        perror("error opening file:");
    }

    // calling partialReverse to reverse first part of the file and writing it to output
    partialReverse(0,stoll(argv[2])-1,fd);
    // calling read_file to read and write middle part of file unchanged
    read_file(stoll(argv[2]), stoll(argv[3]),fd);
    // calling partialReverse to reverse third part of the file and writing it to output
    partialReverse(stoll(argv[3])+1,total_file_size-1,fd);
    
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
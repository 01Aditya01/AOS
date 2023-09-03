#ifndef HEADER_H
#define HEADER_H

#include<iostream>
#include <sys/utsname.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <filesystem>
#include <dirent.h>
#include <unordered_set>
#include <sys/stat.h>
#include <ctime>
#include <cstring>
#include <pwd.h>
#include <grp.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <sys/wait.h>
#include <fcntl.h>

using namespace std;

extern string home_directory_path;
extern int home_path_len;
extern string prev_dir;

void printCurrentDir(char *[]);
void detectCommand(vector<string> &);
string pwd();
void chDirectory(vector<string>& );
void callCwd(const char*);
void ls(vector<string>&);
int listFile(const char* , string);
bool pathCmp(string, string);
int bg(vector<string> &);
void pinfo(vector<string> &);
bool search(string , string);
int rest(vector<string> &);
bool redirection(vector<string> &);


#endif
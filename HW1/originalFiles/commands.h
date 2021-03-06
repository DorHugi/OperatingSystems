#ifndef _COMMANDS_H
#define _COMMANDS_H
#include <iostream>
#include <unistd.h> 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <errno.h>
#include <sstream>
#include <dirent.h>
#include "jobs.h"
#define MAX_LINE_SIZE 80
#define MAX_ARG 20
#define MAX_BUF 1024
#define MAX_HISTORY 50
#define MAX_JOB_NAME 50
#define MAX_JOBS 100

using namespace std;

int ExeComp(char* lineSize);
int BgCmd(char* lineSize);
int ExeCmd(char* lineSize, char* cmdString);
void ExeExternal(char *args[MAX_ARG], char* cmdString);
void showpid_cmd();    		

//My functions:
bool bg_cmd(int jobNum);
void pwd_cmd();
void history_cmd();
void jobs_cmd(); 		
bool cd_cmd(const char* path);
void kill_cmd(int signal, int jobNum);
bool fg_cmd(char* ser);
void quit_cmd();
void quit_kill_cmd();




#endif








































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
#include <list>
#include <unistd.h>
#include <stdbool.h>

#define MAX_LINE_SIZE 80
#define MAX_ARG 20
#define MAX_BUF 1024
#define MAX_CMD_HISTORY 50
int ExeComp(char* lineSize);
int BgCmd(char* lineSize, void* jobs);
int ExeCmd(void* jobs, char* lineSize, char* cmdString);
void ExeExternal(char *args[MAX_ARG], char* cmdString);

//getPwd(): Fucntion retruns a char* of the current working directory. 
//Caller is obligated to free this memory.

void pwd_cmd();
void showpid_cmd();
void update_jobs();
void jobs_cmd();
void history_cmd();
void cd_cmd(const char* path);
#endif


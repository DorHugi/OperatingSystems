//		commands.cpp
//********************************************
#include "commands.h"

using namespace std;

//Global variables:

list<string> historyList; 

//Local functions declarations:

void updateHistoryList(char* cmdString); 


//********************************************
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************
int ExeCmd(void* jobs, char* lineSize, char* cmdString)
{
	char* cmd; 
	char* args[MAX_ARG];
	char pwd[MAX_LINE_SIZE];
	char* delimiters = " \t\n";  
	int i = 0, num_arg = 0;
	bool illegal_cmd = false; // illegal command
    	cmd = strtok(lineSize, delimiters);
	if (cmd == NULL)
		return 0; 
   	args[0] = cmd;
    updateHistoryList(cmdString);
	for (i=1; i<MAX_ARG; i++)
	{
		args[i] = strtok(NULL, delimiters); 
		if (args[i] != NULL) 
			num_arg++; 
 
	}
/*************************************************/
// Built in Commands PLEASE NOTE NOT ALL REQUIRED
// ARE IN THIS CHAIN OF IF COMMANDS. PLEASE ADD
// MORE IF STATEMENTS AS REQUIRED
/*************************************************/
	if (!strcmp(cmd, "cd") ) 
	{
		
	} 
	
	/*************************************************/
	else if (!strcmp(cmd, "pwd")) 
	{
       pwd_cmd(); 		
        
	}
	
	/*************************************************/
	else if (!strcmp(cmd, "history")) 
	{
       history_cmd(); 		
        
	}
	
	/*************************************************/
	else if (!strcmp(cmd, "mkdir"))
	{
 		
	}
	/*************************************************/
	
	else if (!strcmp(cmd, "jobs")) 
	{
 		
	}
	/*************************************************/
	else if (!strcmp(cmd, "showpid")) 
	{
        showpid_cmd();    		
	}
	/*************************************************/
	else if (!strcmp(cmd, "fg")) 
	{
		
	} 
	/*************************************************/
	else if (!strcmp(cmd, "bg")) 
	{
  		
	}
	/*************************************************/
	else if (!strcmp(cmd, "quit"))
	{
   		
	} 
	/*************************************************/
	else // external command
	{
 		ExeExternal(args, cmdString);
	 	return 0;
	}
	if (illegal_cmd == true)
	{
		printf("smash error: > \"%s\"\n", cmdString);
		return 1;
	}
    return 0;
}
//**************************************************************************************
// function name: ExeExternal
// Description: executes external command
// Parameters: external command arguments, external command string
// Returns: void
//**************************************************************************************
void ExeExternal(char *args[MAX_ARG], char* cmdString)
{
	int pID;
    	switch(pID = fork()) 
	{
    		case -1: 
					// Add your code here (error)
					
					/* 
					your code
					*/
                break;
        	case 0 :
                	// Child Process
               		setpgrp();
					
			        // Add your code here (execute an external command)
					
					/* 
					your code
					*/
		        break;	
			default:
                	// Add your code here
				printf("Hello!\n");	
					/* 
					your code
					*/
	}
}
//**************************************************************************************
// function name: ExeComp
// Description: executes complicated command
// Parameters: command string
// Returns: 0- if complicated -1- if not
//**************************************************************************************
int ExeComp(char* lineSize)
{
	char ExtCmd[MAX_LINE_SIZE+2];
	char *args[MAX_ARG];
    if ((strstr(lineSize, "|")) || (strstr(lineSize, "<")) || (strstr(lineSize, ">")) || (strstr(lineSize, "*")) || (strstr(lineSize, "?")) || (strstr(lineSize, ">>")) || (strstr(lineSize, "|&")))
    {
		// Add your code here (execute a complicated command)
					
		/* 
		your code
		*/
	} 
	return -1;
}
//**************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs
// Returns: 0- BG command -1- if not
//**************************************************************************************
int BgCmd(char* lineSize, void* jobs)
{

	char* Command;
	char* delimiters = " \t\n";
	char *args[MAX_ARG];
	if (lineSize[strlen(lineSize)-2] == '&')
	{
		lineSize[strlen(lineSize)-2] = '\0';
		// Add your code here (execute a in the background)
					
		/* 
		your code
		*/
		
	}
	return -1;
}



    

void pwd_cmd(){
    char cwdBuf[MAX_BUF] = {0};

    //put current working directory in myBuf.  
    if (!getcwd(cwdBuf,MAX_BUF)) //if Null is returned:
    {
        perror("Error in pwd_cmd\n");
        exit(-1);
    }
    //else
    printf("%s\n",cwdBuf);
}


void history_cmd(){

    string myStr ="Hello";
    
    for (list<string>::const_iterator it = historyList.begin() ; it != historyList.end() ; it++)
        cout << *it << endl;
}


void updateHistoryList(char* cmdString){

    if (historyList.size() >= MAX_HISTORY){
        historyList.pop_front(); //remove first element
    }
    
    string tmpCmdStr(cmdString); //create a new string from cmdString
    historyList.push_back(tmpCmdStr);
}



void showpid_cmd(){
    //pid_t id = getpid();
   cout << "smash pid is " << getpid() << endl; 
}









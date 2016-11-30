//		commands.c
//********************************************
#include "commands.h"

//********************************************
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************


static char* cmd_history[MAX_CMD_HISTORY];
static int num_cmd_history;
static char* prev_dir;

typedef struct Job{
	int pid;
	char* name;
	time_t start_time;
} Job;

std::list<Job> jobs;

int ExeCmd(void* jobs, char* lineSize, char* cmdString)
{
	char* cmd; 
	char* args[MAX_ARG];
	char pwd[MAX_LINE_SIZE];
	char* delimiters = " \t\n";  
	int i = 0, num_arg = 0;
	bool illegal_cmd = false; // illegal command
	if(num_cmd_history==MAX_CMD_HISTORY)
	{
		strcpy(cmd_history[MAX_CMD_HISTORY-1],"");//todo: change to list
		num_cmd_history--;
	}
	strcpy(cmd_history[num_cmd_history], cmdString);
	num_cmd_history++;
	cmd = strtok(lineSize, delimiters);
    	cmd = strtok(lineSize, delimiters);
	if (cmd == NULL)
		return 0; 
   	args[0] = cmd;
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
	  illegal_cmd = cd_cmd(args[1]);
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
 		
 		jobs_cmd();
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
    printf("%s",cwdBuf);
}


bool cd_cmd(const char* path)
{
	char buf[MAX_BUF];
	size_t size=MAX_BUF;
	char* tmp_dir=getcwd(buf,size);
	if(!strcmp(path,"-"))
	{
		chdir(strcat("~/",prev_dir));
		prev_dir=tmp_dir;
		return true;
	}
	else
	{
		if(chdir(path))
		{
			prev_dir=tmp_dir;
			return true;
		}
		else
		{
			return false;
		}
	}
}

void history_cmd()
{
	int num_cmd_tmp = num_cmd_history;
	int i=0;
	while (num_cmd_tmp>0)
	{
		printf("%s\n",cmd_history[i]);
		i++;
		num_cmd_tmp--;

	}
}


void jobs_cmd()
{
	update_jobs();
	int i = 1;
	double dur;
	for(std::list<Job>::iterator it=jobs.begin();it!=jobs.end(); ++it)
	{
		dur = difftime(time(NULL),it->start_time);
		printf("[%d] %s : %d %f secs",i,it->name,it->pid,dur);
				i++;
	}
}

void update_jobs()
{
	std::list<Job>::iterator it=jobs.begin();
	while(it!=jobs.end())
	{
		if(waitpid(it->pid,NULL,WNOHANG))
		{
			jobs.erase (it);
			continue;
		}
		else
		{
			++it;
		}
	}
}

void showpid_cmd()
{
	printf("smash pid is %d",getpid());
}

















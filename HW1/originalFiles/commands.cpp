//		commands.cpp
//********************************************
#include "commands.h"
using namespace std;

//Global variables:

list<string> historyList; 
list<jobs> jobsList;
char* delimiters = " \t\n";  

//Local functions declarations:

void updateHistoryList(char* cmdString); 
void updateJobsList(string name, pid_t pid);
void removeFinishedJobs(); 
jobs* findJob(int jobNum);
static char prev_dir[MAX_LINE_SIZE];


//********************************************
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************
int ExeCmd(char* lineSize, char* cmdString)
{
	char* cmd; 
	char* args[MAX_ARG];
	char pwd[MAX_LINE_SIZE];
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
		if(num_arg==1)
		{
			illegal_cmd = cd_cmd(args[1]);
		}
		else
		{
			printf("wrong number of parameters\n");
		}
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
	
	else if (strcmp(cmd, "jobs") == 0) 
	{
        jobs_cmd(); 		
	}
	/*************************************************/
	else if (!strcmp(cmd, "showpid")) 
	{
        showpid_cmd();    		
	}
	/*************************************************/
	else if (!strcmp(cmd, "kill")) 

	{
        //expecting to get job num and kill signal.
        //arg 1 is -<signal> ,arg 2 is job num.

        string sigString(args[1]);
        int signal = atoi(sigString.erase(0,1).c_str()); //Delete - sign. 
        cout << "signal is : " << signal << endl;
        int jobNum = atoi(args[2]);
        cout << "jobNum is: " << jobNum << endl;
        kill_cmd(signal,jobNum);    		
	}
	/*************************************************/
	else if (!strcmp(cmd, "fg")) 
	{
     if(num_arg>1)
     {
         printf("too many arguments\n");
     }
     else if(num_arg==1)
     {
         fg_cmd(args[1]);
     }
     else 
       fg_cmd("1");
		
	} 
	/*************************************************/
	else if (!strcmp(cmd, "bg")) 
	{
        int jobNum;
        if (args[1]) //if args1 is not NULL. ie - we're given a job number argument.
            jobNum = atoi(args[1]);
        else
            jobNum = -1; //-1 indicates no job was given.


        bg_cmd(jobNum);  		
	}
	/*************************************************/
	else if (!strcmp(cmd, "quit"))
	{
   		quit_cmd();
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
    cout << "Got to external command" << endl;
    pid_t pid = fork();

    if (pid == -1) {
        cout << "Fork has failed. Exiting program" << endl;
        exit(1);
    }

    else if (pid){ //father. Add to jobs list.
        cout << "cmdString is " << cmdString << endl;
        int state;
        // update that this job is currentlly running.
        cmdToString(cmdString);
        update_curJob(cmdToString,int(time(NULL)),pid,""); 
        waitpid(pid, &state, WUNTRACED);
        return; // finish.
    }

    else { //son
        setpgrp();
        execvp(*args,args);


        cout << "errno is: " << strerror(errno) << endl;
        exit(1);

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
        //check if this is also a bg command.
        bool bg = false;
        if (lineSize[strlen(lineSize)-2] == '&')
            bg = true;

        pid_t pid = fork();

        if (pid == -1) {
            cout << "Fork has failed. Exiting program" << endl;
            exit(1);
        }

        else if (pid){ //father.
            if (bg) { //add to jobs list
                string nameString(lineSize); //change the command name from char * to string
                updateJobsList(nameString,pid);
            }            
            else {
                string cmdToString(lineSize);
                update_curJob(cmdToString,int(time(NULL)),pid,""); 
                waitpid(pid, NULL, WUNTRACED); 
            }
            return (0);
        }

        else { //son
            cout << "about to do exec. My pid is: " << getpid() << endl;
            cout << "line size is: " << lineSize << endl;
            setpgrp();
            cout << "my id after chgrp is :" << getpid() << endl;
            execl("/bin/bash", "/bin/bash","-c",lineSize,NULL);
            //char* argsArr[] = {"csh","-f","-c",lineSize,NULL}; 
            //execvp(*argsArr,argsArr);


            cout << "I have continued after exec! my pid is: " << getpid() << endl;
            cout << "errno is: " << strerror(errno) << endl;
            exit(1);

            }
    }
	return (-1);
}
//**************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs
// Returns: 0- BG command -1- if not
//**************************************************************************************
int BgCmd(char* lineSize)
{


	char* delimiters = " \t\n";

	if (lineSize[strlen(lineSize)-2] == '&')
	{
		lineSize[strlen(lineSize)-2] = '\0';

        //Parse linesize:

        char* cmd; 
        char* args[MAX_ARG];
        int i = 0, num_arg = 0;
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

        //Call external command. make sure to add it to bg.
                   
        pid_t pid = fork();

        if (pid == -1) {
            cout << "Fork has failed. Exiting program" << endl;
            exit(1);
        }

        else if (pid){ //father. Add to jobs list.
            string nameString(lineSize); //change the command name from char * to string
            updateJobsList(nameString,pid);
            return (0);
        }

        else { //son
            setpgrp();
            execvp(*args,args);


            cout << "errno is: " << strerror(errno) << endl;
            exit(1);

            }



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
    printf("%s\n",cwdBuf);
}


void history_cmd(){
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

//Shows all jobs.
void jobs_cmd(){
    int i = 1; 
    removeFinishedJobs();// update list before priting it
    //cout << "entered jobs_cmd!" << endl;
    int curTime = int(time(NULL));
    for (list<jobs>::const_iterator it = jobsList.begin() ; it != jobsList.end() ; it++){
        //print all jobs
        int timePassed = curTime - it->startTime;
        cout << "[" << i << "] " << it->name << " : " << it->pid << " " << timePassed << " secs " << it->isSuspended<<endl;
        i++;

    }

}


void updateJobsList(string name, pid_t pid){
    //check if pid exists. Otherwise don't enter it.
    if (waitpid(pid,NULL,WNOHANG)) //if process is dead
        return; //return if pid doesnt exist.
    
    removeFinishedJobs();
    if (jobsList.size() >= MAX_JOBS){
        cerr << "There are more than " << MAX_JOBS << "job isn't added to jobs List" << endl;
        return;
        }
    //chomp \n form string 
    if (!name.empty() && name[name.length()-1]== '\n')
        name.erase(name.length()-1); 
    jobs newJob(name, pid);
    //cout << "new job created. job name is:" << newJob.name << " pid is: " << newJob.pid << endl;
    jobsList.push_back(newJob);

}

void removeFinishedJobs(){
    // iterate through jobsList and remove finished jobs.    
    
    list<jobs>::iterator it = jobsList.begin();
    while (it != jobsList.end()){
        //check if a process still runs, if a kill with signal 0 has a return value
        //that is different than 0 then the process doesn't exist. signal 0 only checks if a 
        //process g.
        //if (!kill(it->pid, 0))

        cout << "wait pid on" << it -> pid << " is: " << waitpid(it->pid, NULL,WNOHANG) << endl;
        if (!waitpid(it->pid, NULL,WNOHANG))
            it++;
        //else - if this process dosn't exist - remove it.
        else  
            jobsList.erase(it++); // remove element.
                }     

}



void kill_cmd(int signal, int jobNum){
    //send signal to process.
    //Prase the command.
    // comd syntax: kill -<signun> <job number>

    jobs* curJob = findJob(jobNum);
    if (!curJob){
        cout << "smash error:> kill " << jobNum << " - job does not exist" << endl;
        return;
    }
    //cout << "pid of the killed process is : " << curJob->pid << endl;
    if (kill(curJob->pid,signal)) //returns non zero if failed:
        cout << "smash error:> kill " << jobNum << " - cannot send signal" << endl;
    return;
}

 
     
//return a pointer to job jobNum in jobslist. or null if not found.
jobs* findJob(int jobNum){
    int count = 1;
    for (list<jobs>::iterator it = jobsList.begin() ; it != jobsList.end() ; it++){
        if (count == jobNum){
            return (&(*it)); //jobs are sorted.
            count++;
        }
    }
    return(NULL); //job wasn't found
}

bool cd_cmd(const char* path)
{
	char buf[MAX_BUF];
	//size_t size=MAX_BUF;
	char* tmp_dir=getcwd(buf,MAX_BUF);
	if(path!=NULL && strcmp(path,"-")==0)
	{
		chdir(prev_dir);
		strcpy(prev_dir,tmp_dir);
		return false;
	}
	else
	{
		if(opendir(path))
		{
			chdir(path);
			strcpy(prev_dir,tmp_dir);
			return false;
		}
		else
		{
			return true;
		}
	}
}

void fg_cmd(char* ser)
{
   int state;
	 removeFinishedJobs();
   printf("%s\n",ser);
   const char* constSer=(const char*)ser;
   int serInt=atoi(constSer);
  if (findJob(serInt)==NULL)
	{
		printf("Error: No such job\n");
	}
	else
	{   
     update_curJob(findJob(serInt)->name,findJob(serInt)->startTime, findJob(serInt)->pid, findJob(serInt)->isSuspended);
     waitpid(findJob(serInt)->pid, &state, WUNTRACED);
	}
}

void quit_cmd()
{
  exit(1);
}

void update_curJob(string name,int startTime, pid_t pid, string isSuspended)
{
    //cur_job->name =  name;
 //   cur_job->startTime = startTime;
   // cur_job->pid = pid;
   // cur_job->isSuspended= isSuspended;
}


void bg_cmd(int jobNum){

    jobs* curJob;
    // jobNum = -1 means no job num argument was given. 
   if (jobNum == -1){ //no job was given.
       //find last suspended job and run it.
         
        list<jobs>::iterator it = jobsList.begin();
        while ((++it) != jobsList.end()) //get to one after last elemnt.
            break;
        it--; //return it to point last elemnt.
        curJob = &(*it);
   } 
   else
        curJob = findJob(jobNum); 

   if (!curJob){ // job was not found.
        cerr << "job number: " << jobNum  << "wasn't found. bg failed" << endl;
        return;
   }    

    //job was found.

    kill(curJob->pid,18); //Send sigcont
    curJob->unsuspend();


}




string sigNumToName (int sigNum){


string sigName[]={"INVALID", "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT", "SIGBUS", "SIGFPE", "SIGKILL", "SIGUSR1", "SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM", "SIGSTKFLT", "SIGCHLD", "SIGCONT", "SIGSTOP", "SIGTSTP", "SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU", "SIGXFSZ", "SIGVTALRM", "SIGPROF", "SIGWINCH", "SIGPOLL", "SIGPWR", "SIGSYS", NULL};

return (sigName[sigNum]);

}

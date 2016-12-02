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
        kill_cmd(string(lineSize));    		
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
    cout << "Got to external command" << endl;
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
        bool bg = false;
        //check if this is also a bg command.
        if (lineSize[strlen(lineSize)-2] == '&')
            bg = true;
        //run the command
       
       //Prepare commands:
        char* argsArray[] = {"csh","-f","-c",lineSize, NULL}; //Create args array.


        pid_t childPid = fork(); 
        
        if (childPid == -1){
            cerr << "smash error: " << lineSize << endl;
            return(1);
        }

        if (!childPid){ //if you're the son.
        
        //execute command:
        int excReturncode  = execvp(*argsArray, argsArray);

        if (excReturncode == -1){
            cerr << "smash error: " << lineSize << endl;
            exit(-1);
            } 
        }
        
        //if it's the father:

        if (bg){ //add to jobs list
            string nameString(lineSize); //change the command name from char * to string
            updateJobsList(nameString,childPid);
        }            
        return(0);

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
    int i = 0; 
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
        //process exists.
        if (!kill(it->pid, 0))
            it++;
        //else - if this process dosn't exist - remove it.
        else  
            jobsList.erase(it++); // remove element.
         

    }
         

}



void kill_cmd(string cmd){
    //send signal to process.
    //Prase the command.
    // comd syntax: kill -<signun> <job number>
    
    char delim = ' '; 

    vector<string> elems;
    stringstream ss;
    ss.str(cmd);
    string item;
    while (getline(ss, item, delim)) 
        elems.push_back(item);
    if (elems.size() < 3){
        cout << "smash error:> kill commands parameters are illegal" << endl;
        return;
    }
    int signal = atoi(elems[1].erase(0,1).c_str()); 
    int jobNum = atoi(elems[2].c_str()); 
    jobs* curJob = findJob(jobNum);
    if (!curJob){
        cout << "smash error:> kill " << jobNum << " - job does not exist" << endl;
        return;
    }

    if (kill(curJob->pid,signal)) //returns non zero if failed:
        cout << "smash error:> kill " << jobNum << " - cannot send signal" << endl;
    return;
}

 
     
//return a pointer to job jobNum in jobslist.
jobs* findJob(int jobNum){
    int count = 0;
    for (list<jobs>::iterator it = jobsList.begin() ; it != jobsList.end() ; it++){
        if (count == jobNum){
            return (&(*it)); //jobs are sorted.
            count++;
        }
    }
    return(NULL); //job wasn't found
}



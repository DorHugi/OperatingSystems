// signals.c
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_cntlc
   Synopsis: handle the Control-C */
#include "signals.h"
extern jobs cur_job;
void signal_handler(int signum)
{
    if(cur_job.pid!=-1 && waitpid(cur_job.pid,NULL,WNOHANG)==0){
        if(signum == SIGINT)
        {
            send_signal(cur_job.pid,signum);
            update_curJob("",-1, -1, "");                
            printf("\n");
            
        }
        else if(signum == SIGTSTP || signum == SIGSTOP)
        {
            pid_t pid=cur_job.pid;
            updateJobsList(cur_job.name, pid);
            update_curJob("",-1, -1, "");        
            send_signal(pid,signum);    
            printf("\n");
            
        }  
    }
    
}

bool send_signal(pid_t pid, int signum)
{
jobs* curJob = findJobByPid(pid);
    
    int rc = kill(pid, signum);
    if(rc!=0)
    {
      printf("tried to send signal and failed\n");
      return (false);
    }
    else
    {
        if ((curJob!=NULL) && (signum == SIGTSTP || signum == SIGSTOP)) //i.e - SIGTSTP - ctrl Z:
            curJob->suspend();    //print that this process is suspended.
        if ((curJob!=NULL) && (signum == SIGCONT)) //i.e - SIGTSTP - ctrl Z:
            curJob->unsuspend();    //print that this process is suspended.
    char* sig;
    sig = (char *)alloca(sigNumToName(signum).size() + 1);
    memcpy(sig, sigNumToName(signum).c_str(), sigNumToName(signum).size() + 1);
        printf("signal: %s was sent to pid %d\n",sig,(int)pid);
    }    
    removeFinishedJobs();
    return (true);
}

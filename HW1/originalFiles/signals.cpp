// signals.c
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_cntlc
   Synopsis: handle the Control-C */
#include "signals.h"

void signal_handler(int signum)
{
    if(cur_job!=NULL && cur_job.pid!=-1 && waitpid(cur_job.pid,NULL,WNOHANG)){
        if(signum == SIGINT)
        {
            update_curJob("",-1, -1, "");            
            send_signal(pid,signum);
            
        }
        else if(signum == SIGTSTP)
        {
            pid_t pid=cur_job.pid
            updateJobsList(cur_job.name, pid);
            update_curJob("",-1, -1, "");        
            send_signal(pid,signum);    
            
        }  
    }
    else
    {
        printf("\n");
    }
}

void send_signal(pid_t pid, int signum)
{
    printf("signal: %s was sent to pid %d", /*add signal name*/,(int)pid);
}

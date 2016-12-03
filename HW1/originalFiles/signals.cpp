// signals.c
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_cntlc
   Synopsis: handle the Control-C */
#include "signals.h"

void signal_handler(int signum)
{
  //  if(cur_job!=NULL && waitpid(cur_job->pid,NULL,WNOHANG)){
        if(signum == SIGINT)
        {
            
        }
        else if(signum == SIGTSTP)
        {
            
        }  
   // }
}

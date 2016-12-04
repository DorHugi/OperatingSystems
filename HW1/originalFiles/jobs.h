#ifndef _JOBS
#define _JOBS
using namespace std;
#include <string>
void send_signal(pid_t pid, int signum);
void update_curJob(string name,int startTime, pid_t pid, string isSuspended);

void updateJobsList(string name, pid_t pid);
string sigNumToName (int sigNum);

class jobs {
    public:
        //Class variables.
        string name;
        int startTime;
        pid_t pid; 
        string isSuspended;//This string is set to "(Stopped)" if the process is suspended.
                           //and empty string otherwise (default).
        //functions:
        
        jobs(string _name, pid_t _pid):name(_name),pid(_pid),isSuspended(""){
            startTime = int(time(NULL));   

        }
        jobs():name(""),startTime(-1),pid(-1),isSuspended(""){}
        
        void suspend() {isSuspended = "(Stopped)";}
        void unsuspend() {isSuspended = "";}
};


jobs* findJobByPid (pid_t pid);

#endif

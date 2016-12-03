#ifndef _JOBS
#define _JOBS
using namespace std;
#include <string>
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
        jobs():name(""),pid(-1),isSuspended(""),startTime(-1){}
        
        void suspend() {isSuspended = "(Stopped)";}
        void unsuspend() {isSuspended = "";}
};



#endif

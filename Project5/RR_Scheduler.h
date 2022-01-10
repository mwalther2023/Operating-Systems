#ifndef RR_SCHEDULER_H
#define RR_SCHEDULER_H
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include "Process.h"
#include <algorithm>
class RR_Scheduler
{
private:
    std::list<Process> processes; // arriving 
    // ready, blocked and finished
    std::list<Process> ready;
    std::list<Process> blocked;
    std::list<Process> finished;
    int32_t block_duration;
//    int32_t quantum = 0;
    int32_t sim_time;
    int32_t timer = 0;
    typedef struct RunResult RunResult;
    RunResult TryRunFor(Process* p, int32_t t);
    int32_t CheckForArrivals();
    int32_t CheckForUnblocked();
    void Unblock(int32_t t);
public:
    RR_Scheduler(std::list<Process> p, int32_t b, int32_t q);
    ~RR_Scheduler();
    virtual void run();
    
};

#endif // RR_SCHEDULER_H

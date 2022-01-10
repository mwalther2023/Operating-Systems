#ifndef PROCESS_H
#define PROCESS_H
#include <fstream>
#include <iostream>
#include <string>
class Process
{
private:
    std::string name;
    int32_t arrival;
    int32_t total;
    int32_t burst;
    
public:
    int32_t elapsed; // total time currently elapsed
    int32_t till_next_block; // time to elapse before blocking 
    int32_t blocked_for; // how long currently blocked for 
    int32_t finished_at = -1; // -1 if not finished 
    Process(std::string n, int32_t arrival, int32_t total, int32_t burst);
    Process();
    ~Process();
    std::string getName();
    int32_t getArrival();
    int32_t getTotal();
    int32_t getBurst();
    int32_t remaining();// calculate remaining run time
    int32_t turnaround();// calculate turnaround time
    
};

#endif // PROCESS_H

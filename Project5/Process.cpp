#include "Process.h"

Process::Process(std::string n, int32_t a, int32_t t, int32_t b){
    name = n;
    arrival = a;
    total = t;
    burst = b;
    till_next_block = b;
}
Process::Process(){
    
}
Process::~Process(){
//    std::cout << "Process Deconstructor" << std::endl;
}
std::string Process::getName(){
    return name;
}
int32_t Process::getArrival(){
    return arrival;
}
int32_t Process::getTotal(){
    return total;
}
int32_t Process::getBurst(){
    return burst;
}
int32_t Process::remaining(){
    return total-elapsed;
}
int32_t Process::turnaround(){
    return finished_at-arrival;
}

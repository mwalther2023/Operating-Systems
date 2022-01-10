#ifndef DEADLOCKDETECTOR_H
#define DEADLOCKDETECTOR_H
#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>
class DeadlockDetector
{
private:
    std::ifstream file;
    typedef struct data_line data_line;
    std::list<data_line> data;
    std::list<data_line> alloc;
    std::list<data_line> request;
    std::vector<int32_t> exist;
    std::vector<int32_t> avail;
    int32_t processes;
    int32_t resources;
    std::list<int32_t> finished;
    std::vector<int32_t> available(std::vector<int32_t> a);
    void compute(data_line d, int index, bool mark[]);
public:
    DeadlockDetector(std::string file_name);
    ~DeadlockDetector();
    void run();
    
};

#endif // DEADLOCKDETECTOR_H

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include "MemoryChunk.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
class MemoryManager
{
private:
    std::list<MemoryChunk> mem;
    int32_t total_space;
    int32_t used_space = 0;
    std::ifstream file;
    void load(MemoryChunk p);
    void unload(std::string n);
    void condense();
    void print();
public:
    MemoryManager(std::string f);
    ~MemoryManager();
    void run();
};

#endif // MEMORYMANAGER_H

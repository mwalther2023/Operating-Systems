#ifndef PROCESS_H
#define PROCESS_H
#include "Counter.h"
#include "PageTableEntry.h"
#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
#include <vector>
class Process
{
private:
    std::vector<Counter> aging;
    std::vector<PageTableEntry> page_table;
    uint32_t p;
    uint32_t f;
    
public:
    Process(uint32_t num_pages, uint32_t num_frames);
    ~Process();
    std::vector<PageTableEntry> getPageTable();
    std::vector<Counter> getCounter();
    void setPageTable(uint32_t pt, uint32_t index);
    void setCounter(uint8_t c, uint32_t index);
    void swapProcess(Process temp);
};

#endif // PROCESS_H

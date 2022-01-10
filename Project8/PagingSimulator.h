#ifndef PAGINGSIMULATOR_H
#define PAGINGSIMULATOR_H
#include "Counter.h"
#include "Process.h"
#include "PageTableEntry.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
#include <bitset>
class PagingSimulator
{
private:
    std::ifstream file;
    int32_t v_pages;
    int32_t page_frames;
    int32_t size;
    int32_t processes;
    int32_t vir_mem;
    int32_t phy_mem;
    uint32_t current_frame;
    uint32_t last_frame = 0;
    int32_t frames_used = 0;
    std::list<Process> data;
    void print();
    void compute(uint32_t pro, std::string act, uint32_t p, uint32_t frame_loc);
    void age(bool flag);
    void evict();

public:
    PagingSimulator(std::string f);
    ~PagingSimulator();
    void run();
};

#endif // PAGINGSIMULATOR_H

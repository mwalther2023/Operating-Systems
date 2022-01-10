#ifndef PAGETABLEENTRY_H
#define PAGETABLEENTRY_H
#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <list>
#include <sstream>
class PageTableEntry
{
private:
    uint32_t entry;
    uint32_t frame_bits;
    
public:
    PageTableEntry(int32_t b);
    ~PageTableEntry();
    uint32_t getEntry();
    uint32_t getFrameBits();
    void setEntry(uint32_t e);
};

#endif // PAGETABLEENTRY_H

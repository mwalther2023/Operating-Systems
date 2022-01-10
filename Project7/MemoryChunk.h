#ifndef MEMORYCHUNK_H
#define MEMORYCHUNK_H
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
class MemoryChunk
{
private:
    std::string name;
    int32_t start;
    int32_t size;
public:
    MemoryChunk(std::string n, int32_t st, int32_t sz);
    ~MemoryChunk();
    std::string getName();
    int32_t getStart();
    int32_t getSize();
    void setName(std::string n);
    void setStart(int32_t s);
    void setSize(int32_t s);
};

#endif // MEMORYCHUNK_H

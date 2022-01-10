#ifndef COUNTER_H
#define COUNTER_H
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
class Counter
{
private:
    uint8_t counter;
    
    
public:
    Counter();
    ~Counter();
    uint8_t getCounter();
    void setCounter(uint8_t c);

};

#endif // COUNTER_H

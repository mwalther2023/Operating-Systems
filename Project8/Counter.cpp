#include "Counter.h"

Counter::Counter(){
    counter = 0;
}

Counter::~Counter(){
    
}
uint8_t Counter::getCounter(){
    return counter;
}
void Counter::setCounter(uint8_t c){
    counter = c;
}

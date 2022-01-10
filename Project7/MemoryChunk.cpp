#include "MemoryChunk.h"

MemoryChunk::MemoryChunk(std::string n, int32_t st, int32_t sz){
    name = n;
    start = st;
    size = sz;
}

MemoryChunk::~MemoryChunk(){
    
}
std::string MemoryChunk::getName(){
    return name;
}
int32_t MemoryChunk::getStart(){
    return start;
}
int32_t MemoryChunk::getSize(){
    return size;
}
void MemoryChunk::setName(std::string n){
    name = n;
}
void MemoryChunk::setStart(int32_t s){
    start = s;
}
void MemoryChunk::setSize(int32_t s){
    size = s;
}
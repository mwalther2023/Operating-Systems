#include "PageTableEntry.h"

PageTableEntry::PageTableEntry(int32_t b){
    frame_bits = b;
    entry = 0;
}

PageTableEntry::~PageTableEntry(){
    
}
uint32_t PageTableEntry::getEntry(){
    return entry;
}
uint32_t PageTableEntry::getFrameBits(){
    return frame_bits;
}
void PageTableEntry::setEntry(uint32_t e){
    std::bitset<32> o(e);
//    std::cout<<"Entry Setting to: "<<o<<std::endl;
    entry = e;
}



#include "Process.h"

Process::Process(uint32_t num_pages, uint32_t num_frames){
    p = num_pages;
    f = num_frames;
    for(uint32_t i = 0; i<p; i++){
        PageTableEntry e(f/2);
        page_table.push_back(e);
    }
    for(uint32_t i = 0; i<f; i++){
        Counter c;
        aging.push_back(c);
    }
}

Process::~Process(){
    
}

std::vector<PageTableEntry> Process::getPageTable(){
    return page_table;
}
void Process::setPageTable(uint32_t pt, uint32_t index){
    std::vector<PageTableEntry>::iterator i = page_table.begin();
    for(uint32_t j = 0; j<index; j++){
        i++;
    }
    i->setEntry(pt);
//    for(std::vector<PageTableEntry>::iterator o = page_table.begin(); o!=page_table.end();o++){
//        if(o->getEntry() != 0){
//            std::bitset<32> o2 = o->getEntry();
//            std::cout<<o2<<std::endl;
//        }
//    }
//    std::bitset<32> e(pt);
//    std::cout<<"Setting "<<index<<": "<<e<<std::endl;
}
std::vector<Counter> Process::getCounter(){
    return aging;
}
void Process::setCounter(uint8_t c, uint32_t index){
    std::vector<Counter>::iterator i = aging.begin();
    for(uint32_t j = 0; j<index; j++){
        i++;
    }
    i->setCounter(c);
}
void Process::swapProcess(Process temp){
    std::vector<Counter> tC = temp.getCounter();
    std::vector<PageTableEntry> tP = temp.getPageTable();
    aging.swap(tC);
    page_table.swap(tP);
}
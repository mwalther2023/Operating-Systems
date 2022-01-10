#include "PageTableEntry.h"
#include "Counter.h"
#include "PagingSimulator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
int main(int argc, char* argv[]){
    

    if(argc == 2){
        std::string s(argv[1]);
        PagingSimulator p(s);
        p.run();
    }
    else{
        std::cout<<"Usage error: ./Project8 <inputFile>\n";
        return 1;
    }
    return 0;
}
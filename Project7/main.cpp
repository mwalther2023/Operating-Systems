#include "MemoryChunk.h"
#include "MemoryManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
int main(int argc, char* argv[]){
    if(argc == 2){
        std::string f = argv[1];
        MemoryManager* m = new MemoryManager(f);
        m->run();
    }
    else{
        std::cout<<"Usage Error\n";
        return 1;
    }
//    MemoryManager* m = new MemoryManager("/media/sf_Operating_Systems/Op_Sys_Workspace/Project7/first_fit_test.txt");
//    MemoryManager* m = new MemoryManager("/media/sf_Operating_Systems/Op_Sys_Workspace/Project7/best_fit_test.txt");
//    MemoryManager* m = new MemoryManager("/media/sf_Operating_Systems/Op_Sys_Workspace/Project7/worst_fit_test.txt");

//    m->run();
    return 0;
}
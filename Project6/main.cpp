#include "DeadlockDetector.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
int main(int argc, char* argv[]){
//    std::string file = "/media/sf_Operating_Systems/Op_Sys_Workspace/Project6/input1.txt";
//    std::string file = "/media/sf_Operating_Systems/Op_Sys_Workspace/Project6/input2.txt";
//    std::string file = "/media/sf_Operating_Systems/Op_Sys_Workspace/Project6/input3.txt";
    if(argc == 2){
        std::string file = argv[1];
        DeadlockDetector* d = new DeadlockDetector(file);
        d->run();
    }
    else{
        std::cout<<"Usage Error: ./Project6 <input_file>\n";
        return 1;
    }
    return 0;
}
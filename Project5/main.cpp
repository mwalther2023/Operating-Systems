#include "Process.h"
#include "RR_Scheduler.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
int main(int argc, char* argv[]){
//        std::ifstream file("/media/sf_Operating_Systems/Op_Sys_Workspace/Project5/processlist1.txt");
//        int block = 30;
//        int quantum = 20;
//        std::ifstream file;
        if(argc == 4){
            std::string f = argv[1];
            std::ifstream file(f.c_str());
            int32_t block;
            int32_t quantum;
            std::stringstream b(argv[2]);
            std::stringstream q(argv[3]);
            b >> block;
            q >> quantum;
            std::string des;
            Process* p;
            std::list<Process> list;
            while(getline(file,des)){
                std::istringstream iss(des);
                std::string n;
                int t;
                int total;
                int burst;
                iss >> n;
                iss >> t;
                iss >> total;
                iss >> burst;
                p = new Process(n,t,total,burst);
                list.push_back(*p);
                
            }
            RR_Scheduler* schedule = new RR_Scheduler(list,block, quantum);
            schedule->run();
        }
        else{
            std::cout << "Invalid arguments" << std::endl;
            return 1;
        }
        
        
        
        
    return 0;
}
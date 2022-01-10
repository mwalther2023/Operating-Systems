#include <iostream>
#include <fstream>
#include <string>
#include "HexHistogram.h"
#include <iomanip>
int main(int argc, char* argv[]){
//    std::ifstream in_file (argv[1]);
//    std::ifstream in_file ("/media/sf_Operating_Systems/Op_Sys_Workspace/Project2/data1.txt");
//    std::string file_name  = "/media/sf_Operating_Systems/Op_Sys_Workspace/Project2/data2.txt";
    std::string file_name  = "/media/sf_Operating_Systems/Op_Sys_Workspace/Project2/data1.txt";
//    HexHistogram* hist = new HexHistogram(file_name);
    if(argc > 2 || argc < 2){
        std::cerr << "Usage: ./Project2 <inputfile>" << std::endl;
        return 1;
    }
    HexHistogram* hist = new HexHistogram(argv[1]);
    int num = hist->get_value_count();
    std::cout << "Number of values read: " << num << std::endl;
    int u = hist->get_unique_value_count();
    std::cout << "Number of unique numbers read: " << u << std::endl;
    int lin = hist->get_line_count();
    std::cout << "Number of lines read: " << lin << std::endl;
    std::cout << "\nSmallest number on each line"<< std::endl;
    for(int i = lin; i>0; i--){
        std::string small = hist->get_smallest_number(i);
        std::cout.width(4); std::cout << std::right << i << ":\t";
        std::cout.width(8); std::cout << std::right << small << std::endl;
    }
    hist->print();
    return 0;
}

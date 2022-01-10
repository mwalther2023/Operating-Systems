#include "HexHistogram.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <list>
#include <sstream>
#include <map>
#include <iterator>
#include <algorithm>
#include <ostream>
HexHistogram::HexHistogram(std::string file_name){
//    file(file_name.c_str());
//    file = f;
    
    
    try{
        std::ifstream f(file_name);
        if(f.fail()){
//            std::cout << "Input file not found: "<<file_name<<std::endl;
            throw std::runtime_error("Runtime Error");
        }
        file.swap(f);
    
    
        std::list<std::string> line;
        num_values = 0;
        std::string des;
        std::list<unsigned int> num = {};
        std::list<unsigned int>::iterator it = num.begin();
        

        std::map<unsigned int,int>::iterator map_it = histo.begin();
        while(std::getline(file,des)){
            //Counts Lines scanned
            lines++;

            std::istringstream iss(des);
            unsigned int n;
            std::string temp;
            while(iss>>temp){
                std::istringstream temp_iss(temp);
                temp_iss>>std::hex>>n;
                
                //Find Number of values
                num.insert(it,n);
                ++it;

                num_values++;
                
                //Create the Histogram on a map
                map_it = histo.find(n);
                if(map_it != histo.end()){
                    histo[n]++;
                }
                else{
                    histo[n] = 1;
                    unique++;
                }
            }
            
            //Creates map of lowest value in each line
            unsigned int n_min;
            std::istringstream min_iss(des);
            while(min_iss>>std::hex>>n_min){
                if(n_min < min){
                    min = n_min;
                }
            }
            line_map[lines] = min;
            min = 4294967295;
            file.clear();
            
        }
        file.close();
    }
    catch(std::runtime_error &e){
        std::cout << "Input file not found: "<<file_name<<std::endl;
        
    }
}

HexHistogram::~HexHistogram(){
    std::cout << "HexHistogram Deconstructor" << std::endl;
}
int HexHistogram::get_value_count(){
    return num_values;
}
int HexHistogram::get_unique_value_count(){
    return unique;
}
int HexHistogram::get_line_count(){
    
    return lines;
}
std::string HexHistogram::get_smallest_number(int line_num){
    if(line_num <= lines && line_num >0){
        min = line_map[line_num];
    }
    else{
//        std::cerr<< std::logic_error << "Line number invalid\n";
        throw std::logic_error("Line number invalid\n");
    }
    std::stringstream o;
    o << std::hex << min;
    return o.str();
}
void HexHistogram::print(){
    std::cout << "\nHistogram" << std::endl;
    
    std::map<unsigned int,int>::iterator map_it = histo.begin();
    
    unsigned int n;
//    std::list<std::string>::iterator list_it = hex.begin();
    while(map_it != histo.end()){
        std::stringstream output;
        n = map_it->first;
        output << std::hex << n;
        std::cout.width(8); std::cout << std::right << output.str() << ":\t";
        std::cout.width(8); std::cout << std::right << histo[n] << "\n"; 
        map_it++;
    }
    
}
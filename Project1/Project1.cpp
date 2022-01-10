//Matthew Walther
//Project 1

#include <iostream>
#include <fstream>
#include <string>

int const INT_MAX = 2147483647;

int main(int argc, char* argv[]){
    if(argc == 1|| argc > 3){
        std::cerr << "Usage: ./Project1 <input filename> [output filename]\n";
        return 1;
    }
    if(argv[1] == argv[2]){
        std::cerr << "File names cannot be the same\n";
        return 1;
    }
    std::ifstream in_file (argv[1]);
    if(in_file.fail()){
        std::cerr << "Input file cannot be opened";
        return 1;
    }
    bool output = true;
    char* s = (char*)malloc(999*sizeof(char));
    std::string str[10000];
    int n = 0;
    
    while(in_file.getline(s, 1000)){
        str[n] = s;
        n++;
        in_file.clear();
    }
    std::string o[n];
    std::ofstream out(argv[2]);
    if(argv[2] != NULL){
            if(out.fail()){
                std::cerr << "Output file cannot be opened";
                return 1;
            }
            output = false;
    }
    for(int i = 0; i<n; i++){
        o[i] = str[n-i-1];
        
        if(!output){
            out << o[i];
        }
        else{
            std::cout << o[i] << std::endl;
        }
    }
    in_file.close();
    out.close();
}
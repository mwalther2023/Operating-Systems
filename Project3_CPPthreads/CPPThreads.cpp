#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>

std::mutex epiLock;
uint64_t sum;
int num_factors;
uint64_t factor_list[100];

void perfect(uint64_t start, uint64_t stop, uint64_t num){
        
    for (uint64_t i=start; i<=stop; i++){
        
        if (num%i == 0 && i != num){
            epiLock.lock();
                sum += i;
                num_factors++;
                factor_list[num_factors] = i;
            epiLock.unlock();
        }
        
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    uint64_t n = 1;
    int nth = 1;
    
    std::cout << "Enter number: ";
    std::cin >> n;
    std::cout << "Number of Threads: ";
    std::cin >> nth;
    
    std::thread* ths[nth];
    
    for(int i = 0; i<nth; i++){
        int start = (n/nth)*i+1;
        int stop = (n/nth)*(i+1);
        ths[i] = new std::thread(perfect, start, stop, n);
    }
    
    for(int i = 0; i<nth; i++){
        ths[i]->join();
    }
    std::cout << "\nNumber of factors is: " << num_factors<< std::endl;
    for(uint64_t i = 1; i<num_factors; i++){
        if(factor_list[i] > 0)
            std::cout << factor_list[i] << std::endl;
    }
    if(sum == n){
        std::cout << "\n" << n << " is a Perfect Number" << std::endl;
      
    }
    else{
        std::cout << "\n" << n << " is NOT a Perfect Number" << std::endl;
    }
    return 0;
}
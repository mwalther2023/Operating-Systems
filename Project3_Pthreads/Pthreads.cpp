#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>
#include <mutex>

int NUM_THREADS = 1;
std::mutex epiLock;

uint64_t num = 1;
uint64_t factor_list[100];

struct thread_data{
    uint64_t start;
    uint64_t stop;
    uint64_t sum;
    uint64_t n;
    int factor;
};
void *perfect(void *thread_arg){
    struct thread_data *data = (struct thread_data*) thread_arg;
    
    
    for (uint64_t i=data->start; i<=data->stop; i++){
        
        if (data->n%i==0 && i != data->n){
            data->sum+=i;
            data->factor++;
            factor_list[data->factor] = i;
        }
        
    }

    pthread_exit(NULL);
}
int main(int argc, char* argv[]){
    std::cout << "Enter number: ";
    std::cin >> num;
    std::cout << "Number of Threads: ";
    std::cin >> NUM_THREADS;
    
    
    pthread_t threads[NUM_THREADS];
    struct thread_data td[NUM_THREADS];
    pthread_attr_t attr;
    void *status;
    
    int rc;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for(int i = 0; i<NUM_THREADS; i++){

        td[i].start = ((num/NUM_THREADS)*i+1);

        td[i].stop = (num/NUM_THREADS)*(i+1);
        td[i].sum = 0;
        td[i].factor = 0;
        td[i].n = num;
        rc = pthread_create(&threads[i], NULL, perfect, (void *)&td[i]);
      
        if (rc) {
            std::cout << "Error:unable to create thread," << rc << std::endl;
            exit(-1);
        }
    }
    uint64_t local_sum = 0;
    int num_factors = 0;
    pthread_attr_destroy(&attr);
    for(int i = 0; i < NUM_THREADS; i++ ) {
      rc = pthread_join(threads[i], &status);
      if (rc) {
         std::cout << "Error:unable to join," << rc << std::endl;
         exit(-1);
      }
      local_sum += td[i].sum;
      num_factors += td[i].factor;
    }
    
    std::cout << "\nNumber of factors is: " << num_factors<< std::endl;
    for(uint64_t i = 1; i<100; i++){
        if(factor_list[i] > 0)
            std::cout << factor_list[i] << std::endl;
    }
    
    if(local_sum == num){
        std::cout << "\n" << num << " is a Perfect Number" << std::endl;
      
    }
    else{
        std::cout << "\n" << num << " is NOT a Perfect Number" << std::endl;
    }
    
    return 0;
}
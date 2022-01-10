#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <mutex>

std::mutex epiLock;
std::mutex db;
std::mutex outLock;
const int NUM_READS = 3;
const int NUM_WRITES = 2;
const int READERS = 3;
const int WRITERS = 2;
int NUM = rand()%100+1;
//int thread_num[10];// = {0,1,2,3,4,5,6,7,8,9};
int crit_reader = 0;
int t = 0;
void *read(void *r){
    int n = (int)r;
    for(int i = 0; i<NUM_READS; i++){
        epiLock.lock();
        t += 1;
        if(t == 1){
            //Database lock
            db.lock();
        }
        epiLock.unlock();
        crit_reader++;
        usleep(rand()%100+10);
        int reading = NUM;
        epiLock.lock();
        t -= 1;
        outLock.lock();
        std::cout << "reader "<<n<<" read ";
        std::cout.width(4); std::cout<< std::right<<reading;
        std::cout<< std::right<<" "<<crit_reader<<" reader(s)"<<std::endl;
        outLock.unlock();
        crit_reader--;
        if(t == 0){
            db.unlock();
        }
        
        epiLock.unlock();
    }
    
    
    pthread_exit(NULL);
}
void *write(void *w){
    int n = (int)w;
    for(int i = 0; i<NUM_WRITES; i++){
        int temp = rand() %100+1;
        db.lock();
        usleep(rand()%100+10);
        NUM = temp;
        db.unlock();
        outLock.lock();
        std::cout << "writer "<<n<<" wrote ";
        std::cout.width(3); std::cout<< std::right<<NUM;
        std::cout.width(3); std::cout<< std::right<<" 0 reader(s)"<<std::endl;
        outLock.unlock();
    }
    
    
    pthread_exit(NULL);
}
int main(int argc, char* argv[]){
    pthread_t threads[READERS+WRITERS];
    pthread_attr_t attr;
    void *status;
    int thread_num[READERS+WRITERS];
    for(int i = 0; i<READERS+WRITERS; i++){
        thread_num[i] = i;
    }
    int rc;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    for(int i = 0; i<READERS; i++){
        rc = pthread_create(&threads[i], NULL, read, (void *)thread_num[i]);
      
        if (rc) {
            std::cout << "Error:unable to create thread," << rc << std::endl;
            exit(-1);
        }
    }
    for(int i = 0; i<WRITERS; i++){
        rc = pthread_create(&threads[i+READERS], NULL, write, (void *)thread_num[i+READERS-1]);
      
        if (rc) {
            std::cout << "Error:unable to create thread," << rc << std::endl;
            exit(-1);
        }
    }
    
    
    pthread_attr_destroy(&attr);
    for(int i = 0; i < READERS+WRITERS; i++ ) {
      rc = pthread_join(threads[i], &status);
      if (rc) {
         std::cout << "Error:unable to join," << rc << std::endl;
         exit(-1);
      }
    }
    return 0;
}
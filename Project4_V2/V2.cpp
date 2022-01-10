#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <mutex>

std::mutex writeL;
std::mutex readL;
std::mutex outLock;
std::mutex buff;
pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
const int NUM_READS = 3;
const int NUM_WRITES = 3;
const int READERS = 5;
const int WRITERS = 2;

int NUM = rand() % 100 + 1;
int crit_reader = 0;
int read_wait = 0;
int write_wait = 0;
int act_write = 0;
int t = 0;

int wcnt = 0;
int rcnt = 0;
void* read(void* r) {
    int n = (int)r;
    for (int i = 0; i < NUM_READS; i++) {
        pthread_mutex_lock(&the_mutex);
        if (wcnt == 1 || write_wait > 0) {
            read_wait++;
            pthread_cond_wait(&condc, &the_mutex);
            read_wait--;
        }
        rcnt++;
        crit_reader++;
        
        pthread_mutex_unlock(&the_mutex);
        pthread_cond_broadcast(&condc);

        int reading = NUM;
        outLock.lock();
        std::cout << "reader " << n << " read ";
        std::cout.width(4); std::cout << std::right << reading;
        std::cout << std::right << " " << crit_reader << " reader(s),";
        std::cout << std::right << " " << read_wait << " reader(s) waiting,";
        std::cout << std::right << " " << write_wait << " writer(s) waiting," << std::endl;
        outLock.unlock();

        pthread_mutex_lock(&the_mutex);
        crit_reader--;
        if (--rcnt == 0) {
            pthread_cond_signal(&condp);
        }
        pthread_mutex_unlock(&the_mutex);
    }


    pthread_exit(NULL);
}
void* write(void* w) {
    int n = (int)w;
    for (int i = 0; i < NUM_WRITES; i++) {
        pthread_mutex_lock(&the_mutex);
        if (rcnt > 0 || act_write == 1) {
            write_wait++;
            pthread_cond_wait(&condp, &the_mutex);
            write_wait--;
        }
        wcnt = 1;
        act_write++;
        pthread_mutex_unlock(&the_mutex);
        NUM = rand() % 100 + 1;
        outLock.lock();
        std::cout << "writer " << n << " wrote ";
        std::cout.width(3); std::cout << std::right << NUM;
        std::cout << std::right << " " << crit_reader << " reader(s),";
        std::cout << std::right << " " << read_wait << " reader(s) waiting,";
        std::cout << std::right << " " << write_wait << " writer(s) waiting," << std::endl;
        outLock.unlock();

        pthread_mutex_lock(&the_mutex);
        wcnt=0;
        act_write--;
        if (write_wait > 0) {
            pthread_cond_signal(&condp);
        }
        else {
            pthread_cond_broadcast(&condc);
        }
        pthread_mutex_unlock(&the_mutex);

    }
    pthread_exit(NULL);
}
int main(int argc, char* argv[]) {
    pthread_t threads[READERS + WRITERS];
    pthread_attr_t attr;

    pthread_mutex_init(&the_mutex, 0);
    pthread_cond_init(&condc, 0);
    pthread_cond_init(&condp, 0);

    void* status;
    int thread_num[READERS + WRITERS];
    for (int i = 0; i < READERS + WRITERS; i++) {
        thread_num[i] = i;
    }
    int rc;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (int i = 0; i < READERS; i++) {
        rc = pthread_create(&threads[i], NULL, read, (void*)thread_num[i]);

        if (rc) {
            std::cout << "Error:unable to create thread," << rc << std::endl;
            exit(-1);
        }
    }
    for (int i = 0; i < WRITERS; i++) {
        rc = pthread_create(&threads[i + READERS], NULL, write, (void*)thread_num[i + READERS - 1]);

        if (rc) {
            std::cout << "Error:unable to create thread," << rc << std::endl;
            exit(-1);
        }
    }

    pthread_attr_destroy(&attr);
    for (int i = 0; i < READERS + WRITERS; i++) {
        rc = pthread_join(threads[i], &status);
        if (rc) {
            std::cout << "Error:unable to join," << rc << std::endl;
            exit(-1);
        }
    }
    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);
    return 0;
}
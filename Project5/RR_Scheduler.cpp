#include "RR_Scheduler.h"

#define FINISHED 0 
#define READY 1
#define BLOCKED 2
// No process selected
#define IDLE 3
int32_t quantum;
RR_Scheduler::RR_Scheduler(std::list<Process> p, int b, int q){
    
    processes = p; // arriving processes
    // need ready process list
//    ready;
    // need blocked process list
//    blocked;
    block_duration = b;
    quantum = q;
}

RR_Scheduler::~RR_Scheduler(){
    std::cout << "RR_Scheduler Deconstructor" << std::endl;
}


struct RunResult {
    int32_t mode; // how the process released control back to the OS
    int32_t time; // how many cycles ran before releasing control 
};
/// Attempt to run process for up to `time` cycles
RunResult RR_Scheduler::TryRunFor(Process* p, int32_t t) {
    // result should have READY, BLOCKED, or FINISHED
    // may run process for not entire quantum-
    RunResult out;
//    std::cout<<"Runner: " << p->till_next_block<< " | "<<t<<std::endl;
//    std::cout <<"\t"<<p->remaining()<< " | "<<ready.size()<<std::endl;
    if(p->till_next_block < t){
        if(p->remaining()<t){
            out.mode = FINISHED;
            out.time = p->remaining();
            p->elapsed += p->remaining();
//            p->total -= p->remaining();
//            std::cout << "1st Finish " << p->remaining() << std::endl;

        }
//        else if(p->elapsed+p->remaining() == p->getTotal()){
//            out.mode = FINISHED;
//            out.time = p->remaining();
//            p->elapsed += p->remaining();
//        }
        else if(p->till_next_block <= quantum){
//            std::cout<<"Blocked 1: "<< p->till_next_block << "\t"<<t<<std::endl;
            out.mode = BLOCKED;
            out.time = p->till_next_block;
            p->elapsed += p->till_next_block;
            p->till_next_block = p->getBurst(); //Should be 0 not block_duration
            p->blocked_for = block_duration;
//            p->total -= p->till_next_block;
        }
        else if(p->till_next_block > quantum){
            out.mode = READY;
            out.time = t;
            p->elapsed += t;
//            std::cout << "R\n";
            p->till_next_block -= t;
//            p->total -= t;
        }
//        else if(p->till_next_block == quantum{
//            
//        }
        
    }
    else if(p->remaining()<t){
        out.mode = FINISHED;
        out.time = p->remaining();
        p->elapsed += p->remaining();
//        std::cout << "2nd Finish\n";
    }
//    else if((ready.size() == 0 || ready.size() == 1) && blocked.size() == 0){
    else if(ready.size() + blocked.size() < 1){
        out.mode = BLOCKED;
        out.time = p->getBurst();
        p->elapsed += p->getBurst();
//        std::cout <<"2nd BLOCKED: "<<ready.size()<< "\t" << blocked.size()<<"\t";
//        std::cout << p->remaining()<<std::endl;
        if(p->remaining() == 0){
            out.mode = FINISHED;
            p->elapsed += p->remaining();
        }
        else{
            
            p->till_next_block = p->getBurst();
            p->blocked_for = block_duration;
        }
    }
    else if(p->remaining() == 0){
        out.mode = FINISHED;
        out.time = p->remaining();
        p->elapsed += p->remaining();
//        std::cout << "3rd Finish\n";
    }
    else{
        out.mode = READY;
        out.time = t;
        p->elapsed += t;
        std::cout << "R2: "<< t<<"\t"<<p->till_next_block<<"\n";
        p->till_next_block -= t;
//        std::cout << p->getName()<<"\t"<<p->till_next_block<<"\n";
        if(p->remaining() == 0){
            out.mode = FINISHED;
            p->elapsed += p->remaining();
        }
        else if(p->till_next_block == 0){
            out.mode = BLOCKED;
            p->till_next_block = p->getBurst();
            p->blocked_for = block_duration;
        }
        
    }
    
    return out;
}
//bool operator== (const Process &p1, const Process &p2){
//    return *p1->getArrival() == *p2->getArrival();
//}
/// Check for arrivals during the last run
int32_t RR_Scheduler::CheckForArrivals() {
    // check arriving processes for any that arrived since last quantum
    int32_t out = 999999999;
    Process fin;
    std::list<Process>::iterator t;
//    while(t < processes.size()){
    if(!processes.empty()){
        for(std::list<Process>::iterator i = processes.begin(); i!=processes.end(); ++i){
//            std::cout << i->getName() << "\t" << i->getArrival() << "\t" << i->getTotal() << "\t" << i->getTotal() << std::endl;
            Process temp = *i;
//            if(timer >= i->getArrival() && std::find(ready.cbegin(),ready.cend(),temp.getName())!=ready.cend()){
            if(out>temp.getArrival()){
                out = temp.getArrival();
                fin = *i;
                t = i;
            }
//            if(timer >= i->getArrival()){
//                ready.push_back(*i);
//                std::cout << i->getName() << " Has Arrived\n";
//                i = processes.erase(i);
//            }
//            std::cout << t <<std::endl;
//            t++;
//            if(t> processes.size())
//                break;
        }
        if(timer == fin.getArrival()){
            t->till_next_block = t->getBurst();
            ready.push_back(fin);
            processes.erase(t);
//            std::cout << "Erased: " << t->getName() << std::endl;
        }
    }
    else{
        return CheckForUnblocked();
    }
//    }
    // return the time until the next arrival 
//    std::cout <<"Arrival Test\n";
    return fin.getArrival();
}
// check for any processes that unblocked during the last run
int32_t RR_Scheduler::CheckForUnblocked() {
    int32_t out = 999999999;
    // goes over unblocked collection, sees if any should have unblocked
    for(std::list<Process>::iterator i = blocked.begin(); i!=blocked.end(); ++i){
        if(i->blocked_for == 0){
            out = 0;
            Process* p = &(*i);
            ready.push_back(*p);
            i = blocked.erase(i);
//            i--;
//            break;
//            std::cout <<"CheckForUnblock UNBLOCK\n";
        }
        else{
            int temp = i->blocked_for;
            if(out > temp){
                out = temp;
            }
        }
    }
//    std::cout <<"Block test\n";
    // return the time until the next process unblocks
    return out;
}
void RR_Scheduler::Unblock(int32_t t){
    for(std::list<Process>::iterator i = blocked.begin(); i!=blocked.end(); ++i){
        Process p = *i;
//        std::cout << "TEST: "<<p.getName() << "\t" << p.blocked_for << "\t"<<t<<std::endl;
        if(i->blocked_for == 0){
            p = *i;
            i = blocked.erase(i);
            ready.push_back(p);
            
//            std::cout <<"UNBLOCK 1.1\n";
        }
        else if(i->blocked_for < t){
//            p.blocked_for = 0;
            i->blocked_for = 0;
            p = *i;
            i = blocked.erase(i);
//            i--;
            ready.push_back(p);
//            std::cout <<"UNBLOCK 2.1\n";
        }
        else{
//            std::cout << "Unblock1: "<<p.getName() << "\t" << i->blocked_for << "\t"<<t<<std::endl;
//            p.blocked_for -= t;
            i->blocked_for -= t;
            p = *i;
//            std::cout << "Unblock2: "<<p.getName() << "\t" << i->blocked_for << "\t"<<t<<std::endl;
            if(i->blocked_for <= 0){
                i->blocked_for = 0;
                p = *i;
                ready.push_back(p);
                i = blocked.erase(i);
                i--;
//                p.blocked_for = -1;
//                std::cout <<"UNBLOCKING 3\t" << p.getName()<<std::endl;
            }
//            std::cout << "Unblock4: "<<p.getName() << "\t" << i->blocked_for << "\t"<<t<<std::endl;
        }
//        std::cout << "UnblockEND: "<<p.getName() << "\t" << i->blocked_for << "\t"<<t<<std::endl;
    }
}
void RR_Scheduler::run(){
    std::cout << block_duration<< " "<< quantum<<std::endl;
    int32_t n = processes.size();
//    int bt[n];
//    std::string p[n];
//    int temp = 0;
//    int arrival[n];
//    int left[n];
    int32_t currentQuantum = 0; // time for the current quantum
    
    // while (there are processes remaining) {
    while(finished.size() < n){
        
        // check for arrivals, store time until next arrival
        int32_t next_arrival = CheckForArrivals();
        // check for unblocked, store time until next unblock
        int32_t next_unblocked = CheckForUnblocked();
        // figure out next process from ready queue
//        std::cout << next_arrival << " | "<< next_unblocked<<std::endl;
//        std::cout<<"\tTOP UNBLOCK\n";
//        std::cout << "TOP Ready Size: "<<ready.size() <<"\t";
//        std::cout << "Block Size: "<<blocked.size() <<std::endl;
        Process p;
        if(!ready.empty()){
//            std::cout << "TOP1\n";
            p = ready.front();
        }
        else if(!blocked.empty()){
            Unblock(quantum);
//            std::cout << "TOP2\n";
            p = ready.front();
        }
        else{
//            std::cout << "TOP3\n";
            p = blocked.front();
            blocked.pop_front();
        }
        RunResult state;
        currentQuantum = quantum;
//        std::cout << "TEST\n";
        // try to run that process for the given quantum
            // (or idle if no process is ready)
        // figure out time to run process for
        // might be entire remaining quantum, 
        // or just a fraction 
        // (if a process arrives, or unblocks sooner than the end of the quantum)
        // try to run for the lowest between remaining quantum time, 
        //          unblock time and arrival time 
//        std::cout << "TEMP TOP\n";
        if(!ready.empty()){
//            std::cout<<"here\n";
            p = ready.front();
            ready.pop_front();
            if(p.getBurst()<currentQuantum){
                state = TryRunFor(&p, p.getBurst());
//                std::cout << "TEMP RUN: "<<state.time<<std::endl;
                
                currentQuantum -= state.time;
//                timer += state.time;
            }
            else{
                state = TryRunFor(&p, currentQuantum);
                currentQuantum -= state.time;
//                timer += state.time;
            }
        
        }
        else{
            state.mode = IDLE;
        }
        
        
        // based on mode:
        // READY - process is still ready to run, 
        //  if quantum has remaining time, run it again (place in front of ready)
        //  otherwise, put back in ready (place at back of ready)
        // BLOCKED - process has blocked for IO, put in blocked collection
        //   update process with its block duration, put into blocked list
        // FINISHED - process has finished.
        //   mark finished time, place in finished list
        if(state.mode == READY){
            if(currentQuantum > 0){
                ready.push_front(p);
//                Unblock(currentQuantum);
//                std::cout << "READY 1\n";
                next_unblocked = CheckForUnblocked();
            }
            else{
//                int32_t t1_size = blocked.size();
                Unblock(quantum);
//                if(t1_size != blocked.size()){
                    std::cout << timer<< "\there" << p.getName() << "\t" << quantum << "\tQ\n";
                    timer += quantum;
//                }
//                else{
//                    std::cout << timer<< "\there" << p.getName() << "\t" << quantum+p.till_next_block << "\tQ\n";
//                    timer += p.till_next_block;
//                    Unblock(quantum-p.till_next_block);
//                }
                
                next_arrival = CheckForArrivals();
                
                ready.push_back(p);
//                std::cout << "READY 2\n";
//                next_unblocked = CheckForUnblocked();
            }
        }
        else if(state.mode == BLOCKED){
            
            p.blocked_for = block_duration;
            std::cout << timer << "\t" << p.getName() << "\t" << state.time << "\tB\n";
//            <<p.remaining()<<std::endl;
            currentQuantum -= state.time;
            timer += state.time;
//            if(blocked.size() > 1)
                Unblock(state.time);
            blocked.push_back(p);
            next_unblocked = CheckForUnblocked();
            
        }
        else if(state.mode == FINISHED){
            
            std::cout << timer << "\t" << p.getName() << "\t" << state.time << "\tT\n";
            timer += state.time;
            p.finished_at = timer;
            finished.push_back(p);
            Unblock(state.time);
//            std::cout <<finished.size()<< "\tFINISHED\n";
            next_unblocked = CheckForUnblocked();
        }
        if((int32_t)finished.size() == n){
            std::cout<<timer<<"\t[END]\n";
            break;
        }
//        std::cout << "BOTTOM Ready Size: "<<ready.size() <<"\t";
//        std::cout << "Block Size: "<<blocked.size() <<std::endl;
        if(ready.empty()){
//            next_arrival = CheckForArrivals();
            next_unblocked = CheckForUnblocked();
//            std::cout <<"[IDLE]: (" << next_arrival << ", "<<next_unblocked<<")\n";
            if(next_arrival==0){
                std::cout << timer << "\t[IDLE]\t" << next_unblocked << "\tI\n";
                timer += next_unblocked;
//                p.till_next_block = p.getBurst();
//                std::cout << "IDLE 1\n";
                Unblock(next_unblocked);
            }
            else{
                int l = next_arrival - timer;
                if(l>0 && l<next_unblocked){
                    std::cout << timer << "\t[IDLE]\t" << l << "\tI\n";
                    timer += l;
//                    std::cout << "IDLE 2\n";
                    Unblock(l);
                }
                else{
                    std::cout << timer << "\t[IDLE]\t" << next_unblocked << "\tI\n";
                    timer += next_unblocked;
    //                p.till_next_block = p.getBurst();
//                    std::cout << "IDLE 3\n";
                    Unblock(next_unblocked);
                }
            }
//            std::cout << "REAL BOTTOM Ready Size: "<<ready.size() <<"\t";
//            std::cout << "Block Size: "<<blocked.size() <<std::endl;

        }
        
        
    }
    double turn = 0;
    for(std::list<Process>::iterator i = finished.begin(); i!=finished.end();i++){
        Process p = *i;
        std::cout << p.getName() << "\t" << p.turnaround() << std::endl;
        turn += p.turnaround();
    }
    std::cout<<turn/finished.size()<<std::endl;
}
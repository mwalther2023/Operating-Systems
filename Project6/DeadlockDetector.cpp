#include "DeadlockDetector.h"

DeadlockDetector::DeadlockDetector(std::string file_name){
    std::ifstream f(file_name);
    file.swap(f);
}

DeadlockDetector::~DeadlockDetector(){
    std::cout <<"Deconstructor\n";
}
struct data_line{
    std::list<int32_t> line;
};
void DeadlockDetector::run(){
    std::string des;
    getline(file,des);
    std::stringstream s(des);
    s >> processes;
    s >> resources;
//    std::cout << processes << " "<<resources << std::endl;
    std::cout << "Initial Values:\n";
    std::cout << "Number of Processes: "<<processes<<std::endl;
    std::cout << "Number of Resources: "<<resources<<std::endl;
    bool marked[processes];
    
    for(int i = 0; i<processes; i++){
        marked[i] = true;
    }
    while(getline(file,des)){
        std::stringstream d(des);
        int32_t r;
        data_line l;
        int32_t i = 0;
        while(d >> r){
            l.line.push_back(r);
            i++;
        }

        data.push_back(l);
    }


    for(std::list<data_line>::iterator i = data.begin(); i!= data.end(); ++i){
        data_line t = *i;
        std::cout << "Existing Resource Vector\n";
        for(std::list<int32_t>::iterator j = t.line.begin(); j!=t.line.end();j++){
            std::cout << *j << " ";
            exist.push_back(*j);
        }
        std::cout << "\n";
//        exist.push_back(t);
        i++;
        t = *i;
        int temp = 0;
        std::cout << "Current Allocation Vector\n";
        while(temp < processes){
            for(std::list<int32_t>::iterator j = t.line.begin(); j!=t.line.end();j++){
                std::cout << *j << " ";
            }
            std::cout << "\n";
            alloc.push_back(t);
            i++;
            t = *i;
            temp++;
        }
        temp = 0;
        std::cout << "Request Matrix\n";
        while(temp < processes){
//        for(int x = 0; x<processes; x++){
            for(std::list<int32_t>::iterator j = t.line.begin(); j!=t.line.end();j++){
                std::cout << *j << " ";
            }
            std::cout << "\n";
            request.push_back(t);
            if(temp+1 < processes){
                i++;
                t = *i;
                
                temp++;
//                std::cout << temp<<std::endl;
            }
            else{
                break;
            }
//            std::cout << temp<<std::endl;
        }
        
    }
    std::cout << "Available Resource Vector\n";
    avail = available(exist);
    for(std::vector<int32_t>::iterator i = avail.begin();i!=avail.end();i++){
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    std::list<int32_t> o;
    int32_t size = o.size();
    int index = 0;
    for(int32_t dead = 0; dead<processes; dead++){
        index = 0;
        for(std::list<data_line>::iterator i = request.begin(); i!=request.end(); ++i){
            data_line t = *i;
            marked[index] = true;
            compute(t, index, marked);
            bool flag = false;
            for(std::list<int32_t>::iterator fin = finished.begin(); fin!=finished.end(); fin++){
                if(*fin == index){
                    flag = true;
//                    std::cout<<"Run Flagged @ "<<index<<std::endl;
                }
                
            }
//            std::cout<<"Run Marked @ "<<index<<" | \t"<<marked[index]<<std::endl;
//            std::cout<<"Run Flagged2: "<<flag<<std::endl;
            if(marked[index] && !flag){
//                    finished.push_back(index);
                std::cout<<"\nProcess "<<index<<" marked\n";
                std::cout <<"Available Resource Vector\n";
                for(std::vector<int32_t>::iterator i = avail.begin();i!=avail.end();i++){
                    std::cout << *i << " ";
                }
                std::cout << "\n";
                finished.push_back(index);
//                std::cout<<"Finished: "<<index<<std::endl;
            }
//                std::cout<<"Index: "<<index<<std::endl;
                
            index++;
        }
    
    }
//    std::cout<<finished.size()<<std::endl;
    for(int i = 0; i<processes; i++){
        if(!marked[i]){
            o.push_back(i);
        }
    }
//    std::cout<<"Extra checks\n";
//    int32_t extra_start = o.size();
//    int32_t extra_end = 0;
//    for(std::list<int32_t>::iterator i = o.begin(); i!=o.end(); i++){
//        std::list<data_line>::iterator req = request.begin();
//        for(int j = 0; j<*i;j++){
//            req++;
//        }
////    std::list<int32_t>::iterator paused = o.begin();
////    for(std::list<data_line>::iterator i = request.begin(); i!=request.end(); ++i){
//        data_line t = *req;
//        marked[*i] = true;
//        compute(t, *i, marked);
//        std::cout<<finished.size()<<std::endl;
//        if(marked[*i]){
//            std::cout<<"\nProcess "<<*i<<" marked\n";
//            std::cout <<"Available Resource Vector\n";
//            for(std::vector<int32_t>::iterator i = avail.begin();i!=avail.end();i++){
//                std::cout << *i << " ";
//            }
//            std::cout << "\n";
//            o.erase(i);
//            i--;
//            extra_end = o.size();
//        }
//    }
//    std::cout<<"here\n";
    if(o.size() != 0){
        std::cout << "System is deadlocked\n";
        std::cout << "Deadlocked processes: ";
        for(std::list<int32_t>::iterator i = o.begin(); i!=o.end(); i++){
            std::cout << *i << " ";
        }
        std::cout << std::endl;
    }
    else{
        std::cout << "System is not deadlocked\n";
    }
    
    
}
void DeadlockDetector::compute(data_line d, int index, bool mark[]){
//    std::cout<<"Compute: "<<index<<std::endl;
    std::vector<int32_t>::iterator a = avail.begin();
//    std::cout<<"Compute 2: "<<avail.size()<<std::endl;
    for(std::list<int32_t>::iterator i = d.line.begin(); i!=d.line.end(); i++){
        if(*i > *a){
            mark[index] = false;
//            std::cout<<"False @ "<<index<<std::endl;
        }
        a++;
    }
    
    if (mark[index]) {
//        std::cout<<"True @ "<<index<<std::endl;
        int32_t pass = 0;
        bool flag;
        for(std::list<int32_t>::iterator fin = finished.begin(); fin!=finished.end(); fin++){
            if(*fin == index){
                flag = true;
//                std::cout<<"Flagged @ "<<index<<std::endl;
            }
            
        }
        if(!flag){
            std::vector<int32_t>::iterator e = avail.begin();
            std::list<data_line>::iterator a = alloc.begin();
            for (int k = 0; k < index; k++) {
                a++;
            }
            data_line t = *a;

            std::vector<int32_t> holding;
            for (std::list<int32_t>::iterator i = t.line.begin(); i != t.line.end(); i++) {
                pass = *e + *i;
                holding.push_back(pass);
                e++;
            }
            avail.swap(holding);
            
        }
    }
}

std::vector<int32_t> DeadlockDetector::available(std::vector<int32_t> a){
    int32_t num[resources];
    for(int32_t i = 0; i<resources; i++){
        num[i] = 0;
    }
    int32_t index = 0;
    std::vector<int32_t> out;
    for(std::list<data_line>::iterator i = alloc.begin(); i!=alloc.end();i++){
        data_line t = *i;
        for(std::list<int32_t>::iterator j = t.line.begin(); j!=t.line.end();j++){
            num[index] += *j;
            index++;
        }
        index = 0;
    }    
    for(std::vector<int32_t>::iterator i = a.begin(); i!=a.end();i++){
        int32_t n = *i - num[index];
        out.push_back(n);
        index++;
    }
    
    
    return out;
}



#include "MemoryManager.h"
const std::string LOAD = "load";
const std::string UNLOAD = "unload";
const std::string FIRST = "firstFit";
const std::string BEST = "bestFit";
const std::string WORST = "worstFit";
bool F = false;
bool B = false;
bool W = false;
MemoryManager::MemoryManager(std::string f){
    std::ifstream constr_file(f);
    file.swap(constr_file);
}

MemoryManager::~MemoryManager(){
    
}
void MemoryManager::run(){
    std::string des;
    getline(file,des);
    std::stringstream hole(des);
    std::string fit;
    int32_t hole_size;
    hole>>fit;
    hole>>hole_size;
    total_space = hole_size;
    if(fit.compare(FIRST) == 0){
        F = true;
    }
    else if(fit.compare(BEST) == 0){
        B = true;
    }
    else if(fit.compare(WORST) == 0){
        W = true;
    }
    MemoryChunk h("hole",0,hole_size);
    std::cout<<h.getName() << ": start " << h.getStart() << ", size " << h.getSize()<<std::endl<<std::endl;
    mem.push_front(h);
    
    while(getline(file,des)){
        std::cout<<des<<std::endl;
        std::stringstream s(des);
        std::string process;
        std::string name;
        int32_t size;
        s >> process;
        s >> name;
        if(process.compare(LOAD) == 0){
            s >> size;
            if(used_space + size > total_space){
                std::cout<<"Unable to load process "<<name<<std::endl;
            }
            else{
                MemoryChunk p(name, used_space, size);
                used_space += size;
                load(p);
            }
        }
        else{
            unload(name);
//            condense();
        }
        print();
        std::cout<<std::endl;
    }
}
void MemoryManager::load(MemoryChunk p){

    if(F){
//        bool flag = false;
//        for(std::list<MemoryChunk>::iterator i = mem.begin(); i!=mem.end(); i++){
//            if(i->getName().compare("hole")==0 && !flag){
//                if(i->getSize() >= p.getSize()){
//                    p.setStart(i->getStart());
//                    i->setStart(p.getStart()+p.getSize());
//                    i->setSize(i->getSize()-p.getSize());
//                    if(i->getSize() == 0){
//                        i = mem.erase(i);
//                    }
//                    mem.insert(i,1,p);
//                    flag = true;
//                }
//            }
//        }
        bool flag = false;
        std::list<MemoryChunk>::iterator first_hole = mem.begin();
        for(std::list<MemoryChunk>::iterator i = mem.begin(); i!=mem.end(); i++){
            if(i->getName().compare("hole")==0 && !flag){
                first_hole = i;
                break;
                flag = true;
            }
        }
        p.setStart(first_hole->getStart());
        first_hole->setStart(p.getStart()+p.getSize());
        first_hole->setSize(first_hole->getSize()-p.getSize());
        if(first_hole->getSize() == 0){
            first_hole = mem.erase(first_hole);
        }
        mem.insert(first_hole,1,p);
    }
    else if(B){
//        bool flag = false;
        int32_t best_size = 99999999;
        std::list<MemoryChunk>::iterator best_fit = mem.begin();
        for(std::list<MemoryChunk>::iterator i = mem.begin(); i!=mem.end(); i++){
            if(i->getName().compare("hole")==0){
                if(best_size > i->getSize() && i->getSize() >= p.getSize()){
                    best_size = i->getSize();
                    best_fit = i;
                }
            }
        }
        p.setStart(best_fit->getStart());
        best_fit->setStart(p.getStart()+p.getSize());
        best_fit->setSize(best_fit->getSize()-p.getSize());
        if(best_fit->getSize() == 0){
            best_fit = mem.erase(best_fit);
        }
        mem.insert(best_fit,1,p);
    }
    else if(W){
        int32_t max_hole = 0;
        std::list<MemoryChunk>::iterator max = mem.begin();
        for(std::list<MemoryChunk>::iterator i = mem.begin(); i!=mem.end(); i++){
            if(i->getName().compare("hole")==0){
                if(max_hole < i->getSize()){
                    max_hole = i->getSize();
                    max = i;
                }
            }
        }
        p.setStart(max->getStart());
        max->setStart(p.getStart()+p.getSize());
        max->setSize(max->getSize()-p.getSize());
        if(max->getSize() == 0){
            max = mem.erase(max);
        }
        mem.insert(max,1,p);
    }
//        MemoryChunk back = mem.back();
//        mem.pop_back();
//        p.setStart(back.getStart());
//        back.setStart(p.getStart()+p.getSize());
//        back.setSize(back.getSize()-p.getSize());
//        mem.push_back(p);
////        back.setStart(used_space);
////        back.setSize(total_space-used_space);
//        if(total_space-used_space>0){
//            mem.push_back(back);
//        }
}
void MemoryManager::unload(std::string n){
    for(std::list<MemoryChunk>::iterator i = mem.begin(); i!=mem.end(); i++){
        if(i->getName().compare(n) == 0){
//            MemoryChunk h("hole",i->getStart(),i->getSize());
            i->setName("hole");
            used_space -= i->getSize();
            if(i==mem.begin()){
                MemoryChunk current = *i;
                MemoryChunk right = *std::next(i,1);
                if(right.getName().compare("hole") == 0){
                    current.setSize(current.getSize()+right.getSize());
                    i = mem.erase(++i);
                    i--;
                }
            }
            else if(std::next(i,1) == mem.end()){
//                i--;
                std::cout<<"TEST\n";
                MemoryChunk current = *i;
                i--;
                if(i->getName().compare("hole") == 0){
                    i->setSize(current.getSize()+i->getSize());
                    i = mem.erase(i++);
                    i--;
                }
            }
            else if(std::next(i,1)->getName().compare("hole") == 0 && std::prev(i,1)->getName().compare("hole") == 0){
                std::list<MemoryChunk>::iterator n = std::next(i,1);
                std::list<MemoryChunk>::iterator p = std::prev(i,1);
                p->setSize(i->getSize()+p->getSize()+n->getSize());
                n = mem.erase(n);
                n--;
                i = mem.erase(i);
                i--;
            }
            else if(std::next(i,1)->getName().compare("hole") == 0){
                MemoryChunk current = *i;
                MemoryChunk right = *std::next(i,1);
                if(right.getName().compare("hole") == 0){
                    i->setSize(current.getSize()+right.getSize());
                    
                    i = mem.erase(++i);
                    i--;
                }
            }
            else if(std::prev(i,1)->getName().compare("hole") == 0){
                MemoryChunk current = *i;
                MemoryChunk pre = *std::prev(i,1);
                if(pre.getName().compare("hole") == 0){
                    std::prev(i,1)->setSize(current.getSize()+pre.getSize());
                    i = mem.erase(i);
                    i--;
                }
            }
        }
    }
}
void MemoryManager::condense(){ //Not supposed to loop through whole list to combine holes
    int32_t index = 0;
    for(std::list<MemoryChunk>::iterator i = mem.begin(); i!=mem.end(); index++){
        std::list<MemoryChunk>::iterator j = i;
        i++;
        if(index == (int32_t)mem.size()-1){
            break;
        }
//        std::cout<<j->getName() <<" | " <<i->getName()<<" | " <<index<<std::endl;
        if(i!=mem.end()){
            if(i->getName().compare("hole") == 0 && j->getName().compare("hole") == 0){
                MemoryChunk combined("hole",j->getStart(),j->getSize()+i->getSize());
                i = mem.erase(i);
                i--;
                index--;
                j->setSize(combined.getSize());
//                std::cout<< j->getName() << ": start " << j->getStart() << ", size " << j->getSize()<<std::endl;
            }
        }
//        index++;
    }
//    std::cout<<"END\n";
}
void MemoryManager::print(){
    for(std::list<MemoryChunk>::iterator i = mem.begin(); i!=mem.end(); i++){
        std::cout<< i->getName() << ": start " << i->getStart() << ", size " << i->getSize()<<std::endl;
    }
}
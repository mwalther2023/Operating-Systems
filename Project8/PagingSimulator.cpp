#include "PagingSimulator.h"
PagingSimulator::PagingSimulator(std::string f){
    std::ifstream t(f);
    file.swap(t);
}

PagingSimulator::~PagingSimulator(){
}

void PagingSimulator::run(){
    std::string des;
    getline(file,des);
    std::stringstream s(des);
    s >> v_pages;
    s >> page_frames;
    s >> size;
    vir_mem = size * v_pages;
    phy_mem = size * page_frames;
    getline(file,des);
    std::stringstream s2(des);
    s2 >> processes;
    for(int i = 0; i<processes; i++){
        Process p(v_pages+1,page_frames);
        data.push_back(p);
    }
    std::cout<<"INITIAL TABLE SETUP:\n";
    std::cout<<"Virtual Memory Size: "<<vir_mem<<std::endl;
    std::cout<<"Physical Memory Size: "<<phy_mem<<std::endl;
    std::cout<<"Page Size: "<<size<<std::endl;
    std::cout<<"Number of Processes: "<<processes<<std::endl;
    std::cout<<"Number of Pages: "<<v_pages<<std::endl;
    std::cout<<"Number of Frames: "<<page_frames<<std::endl;
    std::cout<<"Page Tables (with aging status)\n";
    print();
    
    int32_t frame_loc = 0;
    int32_t ager = 1;
    
    while(getline(file,des)){
        bool flag = false;
        current_frame = frame_loc;
        last_frame = frame_loc;
        std::stringstream in(des);
        int32_t p_id;
        std::string action;
        int32_t loc;
        in>>p_id;
        in>>action;
        in>>loc;
        std::cout<<"\nProcess "<<p_id<<" requests "<<action<<" "<<loc<<std::endl;
        std::cout<<"Page number: "<<loc/size<<std::endl;
        compute(p_id, action, loc, frame_loc);
        
        std::cout<<"Frame number: "<<current_frame<<std::endl;
        int32_t pg = loc/size;
        std::cout<<"Physical address: "<<(current_frame*size)+(loc-size*pg)<<std::endl;
        std::cout<<"Page Tables (with aging status)\n";
        print();
        if(last_frame != current_frame){
            current_frame = last_frame;
            frame_loc = current_frame;
        }
        else{
            frame_loc++;
        }
        if(frame_loc%4 == 0){
            frame_loc = 0;
            flag = true;
        }
        if(ager == 2){
            std::cout<<"\nAging the counters ... \n";
            ager++;
            age(flag);
            
        }
        else if(ager%4 == 0 && ager != 0){
            std::cout<<"\nAging the counters ... \n";
            ager = 1;
            age(flag);
            
        }
        else{
            ager++;
        }
        
    }
}
void PagingSimulator::compute(uint32_t pro, std::string act, uint32_t loc, uint32_t frame_loc){    
    uint32_t pg = loc/size;
    uint32_t pro_index = 0;
    std::list<Process>::iterator i = data.begin();

        while(pro_index != pro){
            i++;
            pro_index++;
        }

    std::vector<PageTableEntry>::iterator pt = i->getPageTable().begin();
    uint32_t index = 0;
    while(index <= pg){
        pt++;
        index++;
    }
    uint32_t e = pt->getEntry();

    uint32_t R = 1;
    uint32_t M = 0;
    uint32_t P = 1;
    
    uint32_t OP = e>>29&1;
    if(OP == 0){
        std::cout<<"Page fault ...\n";
        if(frames_used >= page_frames){
            evict();
            last_frame = frame_loc;
            frame_loc = current_frame;
        }
        std::cout << "Loading page "<<loc/size<<" of process "<<pro<<" into frame "<<frame_loc<<std::endl;
        frames_used++;
    }
    else{
        last_frame = frame_loc;
        frame_loc = (e<<(32-pt->getFrameBits()))>>(32-pt->getFrameBits());
        current_frame = frame_loc;
    }
    if(act.compare("w") == 0){
        M = 1;
    }
    e = R<<31 | e;
    e = M<<30 | e;
    e = P<<29 | e;
    e = e | frame_loc;
    pt->setEntry(e);    
    i->setPageTable(e,index);
}
void PagingSimulator::print(){
    int32_t index = 0;
    
    for(std::list<Process>::iterator i = data.begin(); i!=data.end(); i++){
        std::cout<<"Process "<<index<<std::endl;
        std::cout<<"page#\tR\tM\tP\tframe#\taging\n";
        std::vector<PageTableEntry>::iterator pt = i->getPageTable().begin();
        pt++;
        for(int j = 0;j<v_pages;j++){
            uint32_t e = pt->getEntry();

            uint32_t R = e>>31&1;
            uint32_t M = e>>30&1;
            uint32_t P = e>>29&1;
            uint32_t s = pt->getFrameBits();
            uint32_t F = (e<<(32-s))>>(32-s);
            if(P == 1){
                std::vector<Counter>::iterator ag = i->getCounter().begin();
                for(uint32_t l = 0; l<F; l++){
                    ag++;
                }
                std::bitset<8> t(ag->getCounter());
                std::cout<<j<<":\t"<<R<<"\t"<<M<<"\t"<<P<<"\t"<<F<<"\t"<<t<<"\n";
            }
            else{
                std::cout<<j<<":\t"<<R<<"\t"<<M<<"\t"<<P<<"\t-\t\n";
            }
            pt++;

        }
        index++;
    }
}
void PagingSimulator::age(bool flag){
    
    for(std::list<Process>::iterator i = data.begin(); i!=data.end(); i++){
        
        uint32_t index = 0;
        for(std::vector<PageTableEntry>::iterator pt = i->getPageTable().begin(); pt!=i->getPageTable().end(); pt++){

            std::vector<Counter>::iterator ag = i->getCounter().begin();
            uint32_t e = pt->getEntry();
            
            uint8_t R = e>>31&1;
            uint32_t P = e>>29&1;
            uint32_t s = pt->getFrameBits();
            uint32_t F = (e<<(32-s))>>(32-s);
            if(P == 1){
                for(uint32_t j = 0; j<F;j++){
                    ag++;
                }
                uint8_t c = ag->getCounter();
                if(c!=0)
                    c = (c>>1) | (R<<7);
                else{
                    c = R<<7;
                }

                ag->setCounter(c);
            }
            if(R == 1){
                e = (e<<1)>>1;
                pt->setEntry(e);

            }
            i->setPageTable(e,index);
            i->setCounter(ag->getCounter(),F);
            index++;
        }
    }


}

void PagingSimulator::evict(){
    uint8_t min = 255;
    int32_t pro_index = 0;
    int32_t frame_index = 0;
    int32_t j =0;
    std::list<Process>::iterator i = data.begin();
    for(std::vector<Counter>::iterator ag = i->getCounter().begin(); ag != i->getCounter().end();ag++){
        uint8_t c = ag->getCounter();
        if(c<min){
            min = c;
            frame_index = j;
        }
        j++;
    }
    std::vector<Counter>::iterator ag = i->getCounter().begin();
    for(int32_t j = 0; j<frame_index; j++){
        ag++;
    }
    ag->setCounter(0);
    uint32_t page_index = 0;
    uint32_t temp_index = 0;
    bool mod = false;
    bool flag = false;
    for(i = data.begin(); i!= data.end(); i++){
        page_index = 0;
        temp_index = 0;
        for(std::vector<PageTableEntry>::iterator pt = i->getPageTable().begin(); pt != i->getPageTable().end();pt++){
            uint32_t e = pt->getEntry();
            uint32_t P = e>>29&1;
            uint32_t M = e>>30&1;
            uint32_t s = pt->getFrameBits();
            uint32_t F = (e<<(32-s))>>(32-s);
            if(F == frame_index && P == 1){
                if(M == 1){
                    mod = true;
                }
                page_index = temp_index;
                pt->setEntry(0);
                flag = true;
            }
            temp_index++;
        }
        if(!flag){
            pro_index++;
        }
    }
    std::cout<<"Evicting process "<<pro_index<<" page "<<page_index-1<<std::endl;//page_index -1 if doing <= pg in compute
    if(mod){
        std::cout<<"Writing frame "<<frame_index<<" back to disk:\n";
    }
    current_frame = frame_index;
    frames_used--;
    i = data.begin();
    for(int32_t p = 0; p<pro_index; p++){
        i++;
    }
    i->setCounter(0,frame_index);
    i->setPageTable(0,page_index);
}

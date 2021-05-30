//
//  CORE.h
//  ECMS
//
//  Created by Guglielmo Incisa di Camerana on 28/05/2021.
//

#ifndef CORE_h
#define CORE_h
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <queue>

#include "UTIL.h"
#include "TECH_Q.h"
#include "DELTA.h"
#include "PROV_ACT.h"


#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

class CORE{
    
private:
    
    mutex mtx,mtxQ;
    condition_variable cv;
    queue<PROV_ACT*> p_a;
    
    //Extract
    PROV_ACT* getP_A(){
        mtxQ.lock();
        PROV_ACT* z = p_a.front();
        p_a.pop();
        mtxQ.unlock();
        return z;
    }
  
public:
    
    void runP_A (int id) {
      while(true){
          unique_lock<mutex> lck(mtx);
          while(p_a.empty()){
              cout<<id<<" waiting"<<endl;
              cv.wait(lck);
          }
          PROV_ACT* z = getQ();
          cout << ">>>DOING" << z <<".." << id<< endl;
          lck.unlock();
          usleep(400000);
          cout << "<<<DONE"<< z <<".." << id<< endl;

          }
      }

    //Insert
    void dispatchP_A(PROV_ACT* _p_a){
        mtxQ.lock();
        q.push(_p_a);
        cv.notify_all();
        mtxQ.unlock();
    }
    
    CORE::CORE(){
        int MT=10;
        std::thread threads[MT];
      
        for (int i=0; i<MT; ++i)
        threads[i] = thread(print_id,i);

    }

}
#endif CORE_h

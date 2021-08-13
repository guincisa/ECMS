//
//  DELTA.h
//  rcme
//
//  Created by Guglielmo Incisa di Camerana on 27/05/2021.
//

#ifndef DELTA_h
#define DELTA_h

#include <list>
#include <mutex>
#include <map>
#include <thread>
#include "PROV_Q.h"

using namespace std;

class DELTA_MGR;

class DELTA {
        
private:

    //Payload
    pair<void*, int>* Code;
    
    //Dependency
    list<DELTA*> Dependency;

    string State;
    string Condition;
    mutex MtxCondition;
    bool payloadLocked = false;

    //In which Prov_q has been executed
    //list<pair<PROV_Q*,int> > Prov_History;
    
    void conditionChangeIdle(void){
        lock_guard<mutex> guard(MtxCondition);
        Condition = delta_c_idle;
    }
    
    void conditionChangeExec(void){
        lock_guard<mutex> guard(MtxCondition);
        Condition = delta_c_exec;
    }
    


public:
    
    friend DELTA_MGR;
    
    DELTA(void){
        State = delta_s_new;
        conditionChangeIdle();
    }
    
    pair<void*, int>* getPayLoad(void){
        return Code;
    }
    
    int setDependency(DELTA* _d){
        
        //check we are not cycling?
        
        Dependency.push_back(_d);
        return result_ok;
    }
    
    int removeDependency(DELTA* _d){
        Dependency.remove(_d);
        return result_ok;
    }
    
    list<DELTA*> getDependency(void){
        //better an address??
        return Dependency;
    }

    //move it to temporary condition of exec
    //only if state is closed or tested
    int loadOn(PROV_Q* _pq) {
        if (State != delta_s_closed && State != delta_s_intest) {
            return result_nok;
        }
        else {
            _pq->loadDelta(this);
            return result_ok;
        }
    }

    int insertPayLoad( pair<void*, int>* _code) {
        if (State != delta_s_new && State != delta_s_open && payloadLocked)
            return result_nok;
        
        State = delta_s_open;
        Code = _code;
        return result_ok;
    }
    
    int lockPayLoad() {
        if (State != delta_s_open)
            return result_nok;
        
        payloadLocked = true;
        return result_ok;
    }
    
    int unlockPayLoad() {
        if (State != delta_s_open)
            return result_nok;
        
        payloadLocked = true;
        return result_ok;
    }

    bool getLockStatus(void){
        return payloadLocked;
    }
    
    int close(){
        if (State == delta_s_new || State == delta_s_open){
            State = delta_s_closed;
            return result_ok;
        }else{
            return result_nok;
        }
    }
    
    int inTest(){
        if (State == delta_s_closed){
            State = delta_s_intest;
            return result_ok;
        }else{
            return result_nok;
        }
    }
    
    int freeze(){
        if (State == delta_s_intest){
            State = delta_s_frozen;
            return result_ok;
        }else{
            return result_nok;
        }
    }
    
    int archive(){
        //need to ingest the payload to avoid loss
        if (State == delta_s_frozen){
            State = delta_s_archived;
            return result_ok;
        }else{
            return result_nok;
        }
    }
    
    int open(){
        //need to ingest the payload to avoid loss
        if (State == delta_s_frozen || State == delta_s_intest){
            State = delta_s_open;
            return result_ok;
        }else{
            return result_nok;
        }
    }


};

#endif /* DELTA_h */

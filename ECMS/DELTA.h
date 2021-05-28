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


using namespace std;

class DELTA {
    
private:
    string State;
    
    string Condition;
    mutex mtxCondition;

    //Payload
    list<string> Code;
    
    //In which Prov_q has been executed
    map<PROV_Q*, string> Prov_History;
    
    //Dependency, string is not used
    map<DELTA, string> Prov_Channel;

    
public:
    
    DELTA(void){
        State = delta_s_new;
        conditionChangeIdle();
    }
    
    void conditionChangeIdle(void){
        lock_guard<mutex> guard(mtxCondition);
        Condition = delta_c_idle;
    }
    
    void conditionChangeExec(void){
        lock_guard<mutex> guard(mtxCondition);
        Condition = delta_c_exec;
    }
    
    list<string>* getPayload(void){
        return &Code;
    }
    
    //move it to temporary condition of exec
    //only if state is closed or tested
    int launchOn(PROV_Q* _pq) {
        if (State != delta_s_closed && State != delta_s_intest) {
            return result_nok;
        }
        else {
            conditionChangeExec();
            Prov_History.insert(pair<PROV_Q*, string>(_pq, delta_r_inprogress));
            return result_ok;
        }
    }
    //move the condition back to idle
    //once the CE has finished to execute the payload
    int endlaunch(PROV_Q* _pq, string _result) {
        Prov_History.insert(pair<PROV_Q*, string>(_pq, delta_c_idle));
        conditionChangeIdle();
        return result_ok;
    }

    void insert(string _s){
        Code.push_back(_s);
    };

};

#endif /* DELTA_h */

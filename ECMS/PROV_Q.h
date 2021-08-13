//
//  PROV_Q.h
//  rcme
//
//  Created by Guglielmo Incisa di Camerana on 27/05/2021.
//

#ifndef PROV_Q_h
#define PROV_Q_h
#include <queue>

using namespace std;

class DELTA;

class PROV_Q {
    
private:
    string State;
    string Connection;
    
    string Condition;
    mutex MtxCondition;
    
    deque<DELTA*> provQ;
    
public:
    
    int loadDelta(DELTA* _d){
        if (State != provq_s_steady){
            return result_nok;
        }
        lock_guard<mutex> guard(MtxCondition);
        if (Condition == provq_c_free){
            Condition = provq_c_busy;
            provQ.push_front(_d);
            Condition = provq_c_free;
            return result_ok;
        }
        return result_nok;
    }

    
};
#endif /* PROV_Q_h */

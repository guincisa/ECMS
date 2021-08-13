//
//  DELTA_MGR.h
//  ECMS
//
//  Created by Guglielmo Incisa di Camerana on 13/08/2021.
//

#ifndef DELTA_MGR_h
#define DELTA_MGR_h

#include <stdio.h>

using namespace std;

//check if references/address/type copy are consistent
//https://refactoring.guru/design-patterns/singleton/cpp/example
class DELTA_MGR {
    
private:
    
    mutex MtxCondition;
    const int MAXITER = 5;
    int ITER;
    
    deque<DELTA*> explodeDependency(DELTA* _d){
        
        DEBUG("explodeDependency")
        deque<DELTA*> _executionOrder;
        DEBUG("")
        
        if(ITER >= MAXITER){
            DEBUG("Iterations Exceeded")
            return _executionOrder;
        }
        ITER ++;
        
        for (list<DELTA*>::iterator it=_d->Dependency.begin(); it != _d->Dependency.end(); ++it)
        {
            DEBUG("")
            if ((*it)->getDependency().size() == 0){
                _executionOrder.push_back(*it);
            }
            else{
                deque<DELTA*> _sq = explodeDependency(*it);
                while (!_sq.empty())
                {
                    _executionOrder.push_back(_sq.front());
                    _sq.pop_front();
                  }
            }
            DEBUG("")
        }
        _executionOrder.push_back(_d);
        return _executionOrder;
    }
    
public:
    deque<DELTA*> getExecutionOrder(DELTA* _d){
        lock_guard<mutex> guard(MtxCondition);
        ITER  = 0;
        deque<DELTA*> _q = explodeDependency(_d);
        ITER = 0;
        return _q;
    }


};
#endif /* DELTA_MGR_h */

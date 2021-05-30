//
//  main.cpp
//  rcme
//
//  Created by Guglielmo Incisa di Camerana on 28/05/2021.
//

#include <iostream>

#include "UTIL.h"
#include "PROV_Q.h"
#include "DELTA.h"


using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    DELTA d;
    
    //CORE* e = new CORE(10);
    
    d.insert("ss");
    
    cout << " inserito ss "<< endl;
    
    list<string>* _s = d.getPayload();
    _s->push_back("xxx");
    cout<< _s->front()<<endl;
    
    
    //
    // CLASS a - a is full class
    // CLASS* a - a is address of class
    //
    int* a;
    *a  = 1;
    cout << *a << endl;
    
    int b = 2;
    cout << b << endl;

    return 0;
    
}


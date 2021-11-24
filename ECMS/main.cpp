//
//  main.cpp
//  rcme
//
//  Created by Guglielmo Incisa di Camerana on 28/05/2021.
//
// Test repository

#include <iostream>

#include "UTIL.h"
#include "DELTA.h"
#include "DELTA_MGR.h"
#include "PROV_Q.h"


using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    
    //DELTA TEST
    DELTA d1;
    
    string* aa = new string("aa");
    
    pair<void*, int>* p = new pair<void*, int>;
    p->first = (void*)aa;
    p->second = 1;
    d1.insertPayLoad(p);
    
    
    pair<void*, int>* _s = d1.getPayLoad();
    cout<<" aa "<< *(string*)(_s->first) << endl;
    cout<<" aa "<< (_s->second) << endl;

    
    d1.close();
    //Delta TEST END
    
    DELTA d2;

    int* bb = new int();
    *bb = 99;
    
    pair<void*, int>* p2 = new pair<void*, int>;
    p2->first = (void*)bb;
    p2->second = 2;
    d2.insertPayLoad(p2);
    
    pair<void*, int>* _s2 = d2.getPayLoad();
    cout<<" 99 " << *(int*)(_s2->first) << endl;
    cout<<" 99 "<< (_s2->second) << endl;

    d2.close();
    //Depenency
    DELTA d3;

    string* cc = new string("ccc");
    
    pair<void*, int>* p3 = new pair<void*, int>;
    p3->first = (void*)cc;
    p3->second = 1;
    d3.insertPayLoad(p3);
    d3.setDependency(&d2);
    
    pair<void*, int>* _s3 = d3.getPayLoad();
    cout<<" ccc " << *(string*)(_s3->first) << endl;
    cout<<" ccc "<< (_s3->second) << endl;

    d3.close();
    
    DELTA x1,x2,x3,x4,x5,x6,x7;
    string* xx1 = new string("xx1");
    string* xx2 = new string("xx2");
    string* xx3 = new string("xx3");
    string* xx4 = new string("xx4");
    string* xx5 = new string("xx5");
    string* xx6 = new string("xx6");
    string* xx7 = new string("xx7");
    pair<void*, int>* px1 = new pair<void*, int>;
    pair<void*, int>* px2 = new pair<void*, int>;
    pair<void*, int>* px3 = new pair<void*, int>;
    pair<void*, int>* px4 = new pair<void*, int>;
    pair<void*, int>* px5 = new pair<void*, int>;
    pair<void*, int>* px6 = new pair<void*, int>;
    pair<void*, int>* px7 = new pair<void*, int>;
    px1->first = (void*)xx1;
    px2->first = (void*)xx2;
    px3->first = (void*)xx3;
    px4->first = (void*)xx4;
    px5->first = (void*)xx5;
    px6->first = (void*)xx6;
    px7->first = (void*)xx7;
    px1->second = 1;
    px2->second = 2;
    px3->second = 2;
    px4->second = 4;
    px5->second = 5;
    px6->second = 6;
    px7->second = 7;
    
    x1.insertPayLoad(px1);
    x2.insertPayLoad(px2);
    x3.insertPayLoad(px3);
    x4.insertPayLoad(px4);
    x5.insertPayLoad(px5);
    x6.insertPayLoad(px6);
    x7.insertPayLoad(px7);

    /*
     xx1
     |   \
     xx2  xx3
     |
     xx4
     |  \  \
     xx5 xx6 xx7
     */

    x1.setDependency(&x2);
    x1.setDependency(&x3);
    x2.setDependency(&x4);
    x4.setDependency(&x5);
    x4.setDependency(&x6);
    x4.setDependency(&x7);
    //x4.setDependency(&x1);

    DELTA_MGR _dm;

    //ordine
    //[xx5 xx6 xx7] xx4 [xx2 xx3] xx1
    deque<DELTA*> dequex = _dm.getExecutionOrder(&x1);
    while (!dequex.empty())
    {
        cout<< *(string*)(dequex.front()->getPayLoad()->first)  << endl;
        dequex.pop_front();
    }

    //
    // CLASS a - a is full class
    // CLASS* a - a is address of class
    //
    int* a = new(int);
    *a = 1;
    cout << *a << endl;
    
    int b = 2;
    cout << b << endl;

    return 0;
    
}


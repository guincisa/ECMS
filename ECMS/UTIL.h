//
//  UTIL.h
//  rcme
//
//  Created by Guglielmo Incisa di Camerana on 27/05/2021.
//

#ifndef UTIL_h
#define UTIL_h

using namespace std;

class ThreadWrapper {
    public:
        pthread_t thread;
        //pthread_mutex_t mutex;
        ThreadWrapper(void) {
            //pthread_mutex_init(&mutex, NULL);
            return;
    };};

#define DEBUG_ON
#ifdef DEBUG_ON
#define DEBUG(x) cout << "{\"logname\": \"DEBUG\",\"payload\": {\"message\":\"" <<__LINE__<<" "<<__FILE__<< " " << x << "\"}}" << endl;
#else
#define DEBUG(x) 
#endif

//{
//    "logname": "DEBUG",
//    "payload": {
//        "message": "hahaha"
//    }
//}


//DELTA
static const string delta_s_new = "ds_new";
static const string delta_s_open = "ds_open";
static const string delta_s_closed = "ds_closed";
static const string delta_s_intest = "ds_intest";
static const string delta_s_frozen = "ds_frozen";
static const string delta_s_archived = "ds_archived";

static const string delta_r_inprogress = "r_inprog";
static const string delta_r_success = "r_success";
static const string delta_r_failed = "r_failed";
    
static const string delta_c_exec = "dc_execution";
static const string delta_c_idle = "dc_idle";
    
//PROVQ
static const string provq_s_steady = "qs_steady";
static const string provq_s_undefined = "qs_undefined";

static const string provq_c_busy = "qc_busy";
static const string provq_c_free = "qc_free";


//GENERIC RESULT
static int result_ok = 0;
static int result_nok = -1;
static int result_undef = -2;


#endif /* UTIL_h */

//
//  UTIL.h
//  rcme
//
//  Created by Guglielmo Incisa di Camerana on 27/05/2021.
//

#ifndef UTIL_h
#define UTIL_h

using namespace std;

static const string delta_s_new = "s_new";
static const string delta_s_devt = "s_develop";
static const string delta_s_closed = "s_closed";
static const string delta_s_intest = "s_intest";
static const string delta_s_exec = "s_execute";
static const string delta_s_frozen = "s_frozen";
static const string delta_s_arch = "s_archives";

static const string delta_r_inprogress = "r_inprog";
static const string delta_r_success = "r_success";
static const string delta_r_failed = "r_failed";
    
static const string delta_c_exec = "c_execution";
static const string delta_c_idle = "c_idle";
    
static int result_ok = 0;
static int result_nok = -1;
static int result_undef = -2;

#endif /* UTIL_h */

/**
 * 作者:evilbinary on 4/16/16.
 * 邮箱:rootdebug@163.com 
 */

#ifndef RSCHEME_MAIN_H
#define RSCHEME_MAIN_H

#include <stdlib.h>
#include <string.h>
#include <rscheme/api.h>
#include <rscheme/osglue.h>
#include <rscheme/stdmodul.h>
#include <rscheme/rlseconf.h>
//#include <rscheme/pkgs/syscalls.h>
//#include <rscheme/pkgs/unixm.h>
//#include <rscheme/pkgs/rs_sys_threads_manager.h>
//#include <rscheme/pkgs/rs_db_lss.h>
//#include <rscheme/pkgs/fasl.h>

#include <rscheme/scheme.h>
#include <rscheme/smemory.h>
#include <rscheme/allocns.h>
#include <jni.h>
void rs_init( int argc, const char **argv );
obj rs_eval(char *str);

char* jstringTostring(JNIEnv* env, jstring jstr);
jstring strToJstring(JNIEnv* env, const char* pat) ;

#endif //RSCHEME_MAIN_H

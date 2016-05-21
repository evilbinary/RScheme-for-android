/**
 * 作者:evilbinary on 4/16/16.
 * 邮箱:rootdebug@163.com 
 */

#include "main.h"
#include <jni.h>
#include "org_evilbinary_rs_Rs.h"
#include <stdlib.h>
#include <stdio.h>

#if ANDROID

#ifndef  LOG_TAG
#define  LOG_TAG    "native-rs"
#endif

#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,LOG_TAG , __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#define LOGV(...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__))
#else
#define LOGI(...)
#define LOGW(...)
#define LOGE(...)
#endif


#define DEFAULT_IMG "/sys.img"
#define INSTALL_DIR "/data/data/org.evilbinary.rs"

extern int bci_trace_flag;

struct module_descr *(std_modules[]) = {
//        &module_syscalls,
//        &module_unixm,
//        &module_rs_sys_threads_manager,
//        &module_rs_db_lss,
//        &module_fasl,
        STD_MODULES_DECL };
obj eval_proc;
int init=-1;

void rs_init( int argc, const char **argv ) {
    char temp[1024];
    obj start, args, rc;
    rs_bool verbose = YES;
    rs_bool is_script = NO;

    if(init<0) {
        LOGI("rs_init");

        rs_install_dir = getenv("RS_INSTALL_DIR");
        //LOGI("RS_INSTALL_DIR=%s", rs_install_dir);

        if (!rs_install_dir)
            rs_install_dir = INSTALL_DIR;

        sprintf(temp, "%s" DEFAULT_IMG, rs_install_dir);
        if (!os_file_exists_p(temp) && strstr(temp, ".fas")) {
            strcpy(strstr(temp, ".fas"), ".orig.fas");
        }
        LOGI("init file %s",temp);
        init_dynamic_link( argv[0]);
        start = init_scheme(argc, argv, temp, verbose, std_modules);
        if (EQ(start, FALSE_OBJ)) {
            fprintf(stderr, "initialization from %s failed\n", temp);
            LOGE("initialization from %s failed\n", temp);
            exit(1);
        }
        LOGI("rs_init start.");
        rc = call_scheme(start, 3, NIL_OBJ, FALSE_OBJ, FALSE_OBJ);
        eval_proc = rc;
        LOGI("rs_init done.");
    }
    init=1;

}
obj rs_eval(char *str){
    return call_scheme( eval_proc, 1, make_string(str) );
}
void rs_exit(){


}


obj result;
//jni function
JNIEXPORT jstring JNICALL Java_org_evilbinary_rs_Rs_eval(JNIEnv * env, jobject obj, jstring str) {
    jstring ret;

    char * eval_str = (*env)->GetStringUTFChars(env, str, NULL);
    LOGI("eval=%s",eval_str);
    result=rs_eval(eval_str);
    LOGI("eval end.");

    ret=strToJstring(env,unicode_string_text(result));

    //    ret=(*env)->NewStringUTF(env,unicode_string_text(result) );

    (*env)->ReleaseStringUTFChars(env,str, eval_str);
    return ret;

}
//init
JNIEXPORT void JNICALL Java_org_evilbinary_rs_Rs_init(JNIEnv* env, jobject thiz) {
    jclass cls = (*env)->GetObjectClass(env, thiz);
    LOGI("init");
    assert(cls);

    //get home path
    jfieldID fieldHome= (*env)->GetFieldID(env, cls, "homePath", "Ljava/lang/String;");
    assert(fieldHome);
    jstring homePath = (*env)->GetObjectField(env, thiz, fieldHome);
    const char *home_dir = (*env)->GetStringUTFChars(env, homePath, NULL);
    setenv("RS_INSTALL_DIR", home_dir, 1);
    LOGI("RS_INSTALL_DIR:%s",home_dir);

    //get args
    jfieldID fieldArgs= (*env)->GetFieldID(env, cls, "args", "[Ljava/lang/String;");
    assert(fieldArgs);
    jobjectArray args=(*env)->GetObjectField(env, thiz, fieldArgs);
    int size = (*env)->GetArrayLength(env,args);

    LOGI("argv:%d",size);

    char **argv=malloc(size*sizeof(char*));
    int i=0;
    for(i=0;i<size;i++){
        jstring obj = (*env)->GetObjectArrayElement(env,args,i);
        assert(obj);
        if(obj!=NULL){
            const char *chars = (*env)->GetStringUTFChars(env, obj, NULL);
            //LOGI("str:%s", chars);
            char *str = malloc(strlen(chars));
            strcpy(str, chars);
            argv[i]=str;
        }
    }

    rs_init(size,argv);

}





JNIEXPORT void JNICALL Java_org_evilbinary_rs_Rs_exit(JNIEnv * env, jobject obj) {
    rs_exit();
}



char* jstringTostring(JNIEnv* env, jstring jstr) {
    char* rtn = NULL;
    jclass clsstring = (*env)->FindClass(env,"java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env,"UTF-8");
    jmethodID mid = (*env)->GetMethodID(env,clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr= (jbyteArray)(*env)->CallObjectMethod(env,jstr, mid, strencode);
    jsize alen = (*env)->GetArrayLength(env,barr);
    jbyte* ba = (*env)->GetByteArrayElements(env,barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char*)malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env,barr, ba, 0);
    return rtn;
}

jstring strToJstring(JNIEnv* env, const char* pat) {
    jclass strClass = (*env)->FindClass(env,"java/lang/String");
    jmethodID ctorID = (*env)->GetMethodID(env,strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = (*env)->NewByteArray(env,strlen(pat));
    (*env)->SetByteArrayRegion(env,bytes, 0, strlen(pat), (jbyte*)pat);
    jstring encoding = (*env)->NewStringUTF(env,"UTF-8");
    return (jstring)(*env)->NewObject(env,strClass, ctorID, bytes, encoding);
}
BASE_PATH := $(call my-dir)

include $(CLEAR_VARS)

RSCHEME_HOME := $(BASE_PATH)

ifeq ($(TARGET_ARCH),x86)
    PLATFORM := androidx86
    include $(CLEAR_VARS)
    LOCAL_MODULE := librs
    LOCAL_SRC_FILES :=  $(RSCHEME_HOME)/lib/x86/librs.a
    include $(PREBUILT_STATIC_LIBRARY)
else
    PLATFORM := android
    include $(CLEAR_VARS)
    LOCAL_MODULE := librs
    LOCAL_SRC_FILES :=  $(RSCHEME_HOME)/lib/armeabi/librs.a
    include $(PREBUILT_STATIC_LIBRARY)

endif



#include $(CLEAR_VARS)
#LOCAL_MODULE := liblss
#LOCAL_SRC_FILES :=  $(RSCHEME_HOME)/lib/liblss.a
#include $(PREBUILT_STATIC_LIBRARY)
#
#include $(CLEAR_VARS)
#LOCAL_MODULE := libpackages
#LOCAL_SRC_FILES :=  $(RSCHEME_HOME)/lib/libpackages.a
##LOCAL_STATIC_LIBRARIES :=  $(RSCHEME_HOME)/lib/liblss.a
#include $(PREBUILT_STATIC_LIBRARY)

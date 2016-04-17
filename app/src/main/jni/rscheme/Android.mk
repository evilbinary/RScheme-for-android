LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(TARGET_ARCH),x86)
PLATFORM := androidx86
else
PLATFORM := android
endif

RSCHEME_HOME := $(LOCAL_PATH)/../librs

LOCAL_MODULE    := myrs
#LOCAL_PATH := $(LOCAL_PATH)
LOCAL_SRC_FILES := main.c
LOCAL_CFLAGS += -I$(RSCHEME_HOME)/include
LOCAL_CFLAGS += -g -Wall -DANDROID  -O -DINLINES -DGC_MACROS
LOCAL_LDLIBS := -lz
LOCAL_LDLIBS += -llog
LOCAL_STATIC_LIBRARIES :=   libpackages liblss librs
#LOCAL_SHARED_LIBRARIES :=
include $(BUILD_SHARED_LIBRARY)





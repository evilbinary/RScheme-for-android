BASE_PATH := $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(TARGET_ARCH),x86)
PLATFORM := androidx86
else
PLATFORM := android
endif

RSCHEME_HOME := $(BASE_PATH)

include $(CLEAR_VARS)
LOCAL_MODULE := librs
LOCAL_SRC_FILES :=  $(RSCHEME_HOME)/lib/librs.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := liblss
LOCAL_SRC_FILES :=  $(RSCHEME_HOME)/lib/liblss.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libpackages
LOCAL_SRC_FILES :=  $(RSCHEME_HOME)/lib/libpackages.a
#LOCAL_STATIC_LIBRARIES :=  $(RSCHEME_HOME)/lib/liblss.a
include $(PREBUILT_STATIC_LIBRARY)

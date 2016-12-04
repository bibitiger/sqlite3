LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := sqlite3_static

LOCAL_SRC_FILES := src/sqlite3.c\
					mainForNode.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_CFLAGS := -std=c99
                                 
include $(BUILD_EXECUTABLE)

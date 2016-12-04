#NDK_TOOLCHAIN_VERSION = 4.6
NDK_DEBUG=0

#LOCAL_PATH := $(call my-dir)

APP_STL := stlport_static
APP_CPPFLAGS := -fexceptions -frtti
#APP_CPPFLAGS += -std=c++11
APP_CPPFLAGS += -fpermissive

APP_ABI := armeabi
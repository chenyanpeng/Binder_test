LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
	Server.cpp

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    libutils \
    libbinder 

LOCAL_MODULE:= Server
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
	Client.cpp

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    libutils \
    libbinder 

LOCAL_MODULE:= Clinet
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)
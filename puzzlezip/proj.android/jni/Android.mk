LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

CPP_DIRECTORY += $(LOCAL_PATH)/hellocpp
CPP_DIRECTORY += $(LOCAL_PATH)/../../Classes

CPP_FILES += $(shell find $(CPP_DIRECTORY) -name *.c)
CPP_FILES += $(shell find $(CPP_DIRECTORY) -name *.cpp)

TOTAL_CPP_FILES = $(filter-out $(DELETE_FILES), $(CPP_FILES))
TOTAL_CPP_FILES := $(sort $(TOTAL_CPP_FILES))
TOTAL_CPP_FILES := $(subst $(LOCAL_PATH)/,,$(TOTAL_CPP_FILES))

LOCAL_SRC_FILES := $(TOTAL_CPP_FILES)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

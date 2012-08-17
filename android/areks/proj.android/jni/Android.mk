LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := $(LOCAL_PATH)/main.cpp \
                   $(wildcard $(LOCAL_PATH)../../../../client/*.cpp) \
                   $(wildcard $(LOCAL_PATH)../../../../common/*.cpp) 
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)../../../../cocos2dx/cocos2dx \
                    (LOCAL_PATH)../../../../cocos2dx/ \
                    (LOCAL_PATH)../../../../cocos2dx/cocos2dx/platform/third_party/android/curl \
                    (LOCAL_PATH)../../../../cocos2dx/cocos2dx/platform \
                    (LOCAL_PATH)../../../../cocos2dx/cocos2dx/include \
                    (LOCAL_PATH)../../../../cocos2dx/CocosDenshion/include \
                    (LOCAL_PATH)../../../../cocos2dx/cocos2dx/lua_support 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static box2d_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) $(call import-module,cocos2dx) $(call import-module,Box2D)

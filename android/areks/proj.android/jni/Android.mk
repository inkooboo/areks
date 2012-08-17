LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := main.cpp \
                   $(wildcard ../../../client/*.cpp) \
                   $(wildcard ../../../common/*.cpp) 
                   
LOCAL_C_INCLUDES := \
                    ../../../client \
                    ../../../common \
                    ../../../cocos2dx/cocos2dx \
                    ../../../cocos2dx/ \
                    ../../../cocos2dx/cocos2dx/platform/third_party/android/curl \
                    ../../../cocos2dx/cocos2dx/platform \
                    ../../../cocos2dx/cocos2dx/include \
                    ../../../cocos2dx/CocosDenshion/include \
                    ../../../cocos2dx/cocos2dx/lua_support 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static box2d_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) $(call import-module,cocos2dx) $(call import-module,Box2D)

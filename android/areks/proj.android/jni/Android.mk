LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := main.cpp \
                   ../../../../json/json_reader.cpp \
                   ../../../../json/json_value.cpp \
                   ../../../../json/json_writer.cpp \
                   ../../../../client/effects/arrow.cpp \
                   ../../../../client/effects/effect_base.cpp \
                   ../../../../client/effects/flying_text.cpp \
                   ../../../../client/animation.cpp \
                   ../../../../client/body_definitions.cpp \
                   ../../../../client/effect_manager.cpp \
                   ../../../../client/loading_screen.cpp \
                   ../../../../client/main_menu.cpp \
                   ../../../../client/polygon_sprite.cpp \
                   ../../../../client/splash_screen.cpp \
                   ../../../../client/triangulator.cpp \
                   ../../../../client/action_handler.cpp \
                   ../../../../client/app_delegate.cpp \
                   ../../../../client/game_logic.cpp \
                   ../../../../client/level_manager.cpp \
                   ../../../../client/loop.cpp \
                   ../../../../client/object_manager.cpp \
                   ../../../../client/physics.cpp \
                   ../../../../client/primitives.cpp \
                   ../../../../client/view.cpp \
                   ../../../../client/player.cpp \
                   ../../../../client/resource_utils.cpp \
                   ../../../../client/objects/background.cpp \
                   ../../../../client/objects/enemy.cpp \
                   ../../../../client/objects/player/body.cpp \
                   ../../../../client/objects/player/head.cpp \
                   ../../../../client/objects/player/neck.cpp \
                   ../../../../client/objects/player/neck2.cpp \
                   ../../../../client/objects/ball.cpp \
                   ../../../../client/objects/base_object.cpp \
                   ../../../../client/objects/object_interfaces.cpp \
                   ../../../../client/objects/platform.cpp \
                   ../../../../client/objects/rope.cpp 
                   
LOCAL_C_INCLUDES := \
                    ../../.. \
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

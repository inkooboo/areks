#include "app_delegate.h"

#include "defs.hpp"

#include "object_manager.hpp"
#include "physics.hpp"
#include "level_manager/lm_view.hpp"
#include "loop.hpp"
#include "level_loader.hpp"
#include "player.hpp"
#include "effect_manager.hpp"
#include "level_manager/action_handler.hpp"
#include "resource_utils.hpp"
#include "level_manager/tool_manager.hpp"

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    cc::CCDirector *pDirector = cc::CCDirector::sharedDirector();
    pDirector->setOpenGLView(&cc::CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
//     pDirector->enableRetinaDisplay(true);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    //init master
    m_master_ptr.reset( new master_t);

    m_master_ptr->add_external_subsystem<AppDelegate>(this);
    m_master_ptr->add_external_subsystem<cd::SimpleAudioEngine>(CocosDenshion::SimpleAudioEngine::sharedEngine());
    m_master_ptr->add_unmanaged_subsystem<ToolManager>();
    m_master_ptr->add_managed_subsystem<ObjectManager>();
    m_master_ptr->add_managed_subsystem<Physics>();
    m_master_ptr->add_managed_subsystem<View,LMView>();
    m_master_ptr->add_managed_subsystem<Loop>();
    m_master_ptr->add_managed_subsystem<LevelLoader>();
    m_master_ptr->add_managed_subsystem<Player>();
	m_master_ptr->add_managed_subsystem<ActionHandler>();
	m_master_ptr->add_managed_subsystem<EffectManager>();

    // run
    m_master_ptr->start();
    
    cc::CCDirector::sharedDirector()->runWithScene(master_t::subsystem<View>().scene());
    master_t::subsystem<LevelLoader>().loadLevel("test_level");    
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    cc::CCDirector::sharedDirector()->stopAnimation();

    master_t::subsystem<cd::SimpleAudioEngine>().pauseBackgroundMusic();
    master_t::subsystem<cd::SimpleAudioEngine>().pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    cc::CCDirector::sharedDirector()->startAnimation();

    master_t::subsystem<cd::SimpleAudioEngine>().resumeBackgroundMusic();
    master_t::subsystem<cd::SimpleAudioEngine>().resumeAllEffects();
}

void AppDelegate::end_application()
{
    master_t::subsystem<cd::SimpleAudioEngine>().end();
    
    m_master_ptr->stop();
    
    cc::CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
#include "app_delegate.h"

#include "defs.hpp"

#include "config.hpp"

#include "object_manager.hpp"
#include "physics.hpp"
#include "view.hpp"
#include "loop.hpp"
#include "action_handler.hpp"
#include "game_logic.hpp"
#include "level_manager.hpp"
#include "splash_screen.hpp"

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

    //init config_t
    const char *full_path = cc::CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config.txt");
    unsigned char *data = 0;
    unsigned long size = 0;
    data = cc::CCFileUtils::sharedFileUtils()->getFileData(full_path, "r", &size);
    
    std::string cfg_str;
    if (data && size)
    {
        cfg_str.assign((char *)data, size);
    }
    
    //init master
    m_master_ptr.reset( new master_t);

    m_master_ptr->add_external_subsystem<AppDelegate>(this);
    m_master_ptr->add_external_subsystem<cd::SimpleAudioEngine>(CocosDenshion::SimpleAudioEngine::sharedEngine());
    m_master_ptr->add_unmanaged_subsystem<config_t>(cfg_str);
    m_master_ptr->add_managed_subsystem<ObjectManager>();
    m_master_ptr->add_managed_subsystem<Physics>();
    m_master_ptr->add_managed_subsystem<View>();
    m_master_ptr->add_managed_subsystem<Loop>();
    m_master_ptr->add_managed_subsystem<ActionHandler>();
    m_master_ptr->add_managed_subsystem<LevelManager>();
    m_master_ptr->add_managed_subsystem<SplashScreen>();

    m_master_ptr->add_managed_subsystem<GameLogic>(); //should be last

    // run
    m_master_ptr->start();
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
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "SimpleAudioEngine.h"
#include "config.hpp"

#include "ObjectManager.hpp"
#include "Physics.hpp"
#include "View.hpp"
#include "Loop.hpp"
#include "ActionHandler.hpp"
#include "GameLogic.hpp"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
//     pDirector->enableRetinaDisplay(true);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    //init config_t
    const char *full_path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config.txt");
    unsigned char *data = 0;
    unsigned long size = 0;
    data = CCFileUtils::sharedFileUtils()->getFileData(full_path, "r", &size);
    
    std::string cfg_str;
    if (data && size)
    {
        cfg_str.assign((char *)data, size);
    }
    
    //init master
    m_master_ptr.reset( new master_t);

    m_master_ptr->add_external_subsystem<AppDelegate>(this);
    m_master_ptr->add_unmanaged_subsystem<config_t>(cfg_str);
    m_master_ptr->add_managed_subsystem<ObjectManager>();
    m_master_ptr->add_managed_subsystem<Physics>();
    m_master_ptr->add_managed_subsystem<View>();
    m_master_ptr->add_managed_subsystem<Loop>();
    m_master_ptr->add_managed_subsystem<ActionHandler>();
    m_master_ptr->add_managed_subsystem<GameLogic>();

    // run
    m_master_ptr->start();
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::end_application()
{
    m_master_ptr->stop();
    
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
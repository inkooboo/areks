#include "AppDelegate.h"
#include "CCEGLView.h"
#include "SimpleAudioEngine.h"
#include "config.hpp"

#include "Physics.hpp"
#include "View.hpp"
#include "Loop.hpp"
#include "ActionHandler.hpp"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    _master.stop();
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

    //init master
    _master.add_managed_subsystem<Physics>();
    _master.add_managed_subsystem<View>();
    _master.add_managed_subsystem<Loop>();
    _master.add_managed_subsystem<ActionHandler>();

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
    _master.add_unmanaged_subsystem<config_t>(cfg_str);
    

    // run
    _master.start();
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

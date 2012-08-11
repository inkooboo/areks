#include "cocos_scene.hpp"

#include "master.hpp"
#include "config.hpp"
#include "game_layer.hpp"

#include "CCFileUtils.h"

#include <cstdlib>
#include <ctime>

USING_NS_CC;

CCScene* cocos_scene_t::scene()
{
    // 'scene' is an autorelease object
    cocos_scene_t *scene = cocos_scene_t::create();
    
    srand((unsigned int)time(NULL));

    //// initialize subsystems
    const char *full_path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config.txt");
    unsigned char *data = 0;
    unsigned long size = 0;
    data = CCFileUtils::sharedFileUtils()->getFileData(full_path, "r", &size);
    
    std::string cfg_str;
    if (data && size)
    {
        cfg_str.assign((char *)data, size);
    }
    
    
    scene->m_master.add_external_subsystem<cocos_scene_t>(scene);
    scene->m_master.add_unmanaged_subsystem<config_t>(cfg_str);
    scene->m_master.add_managed_subsystem<game_layer_t>();
    
    scene->m_master.start();

    ////// schedule game loop
    scene->schedule(schedule_selector(cocos_scene_t::tick), 1.f/60.f);

    // return the scene
    return scene;
}

void cocos_scene_t::tick(cocos2d::CCTime dt)
{
    m_master.subsystem<game_layer_t>().update_scene();
}

void cocos_scene_t::end_scene()
{
    m_master.stop();

    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//
//  level_manager.cpp
//  areks
//
//  Created by inkooboo on 8/15/12.
//
//

#include "level_manager.hpp"

#include "view.hpp"
#include "physics.hpp"
#include "object_manager.hpp"

#include "resource_utils.hpp"

#include "objects/background.hpp"
#include "objects/platform.hpp"
#include "objects/ball.hpp"
#include "objects/rope.hpp"

void LevelManager::start()
{
    //read from config current level info
}

void LevelManager::stop()
{
    
}

LevelManager::LevelManager()
{
    
}

void LevelManager::loadLevel(const char *level_name)
{
    // 0. Show loading splash screen
    // TODO
    
    // 1. Clear all objects
    master_t::subsystem<ObjectManager>().reloadObjectManager();
    
    // 2. Load background
    const std::string bg_name = res::picture("HelloWorld_big");
    
    cc::CCSprite *bg = cc::CCSprite::create(bg_name.c_str());
    cc::CCSize bg_size = bg->getContentSize();
    bg->release();
    
    // 3. Load world params
    pr::Vec2 world_size(48.f, 32.f);
    
    master_t::subsystem<Physics>().reloadWorldParams(world_size);
    
    // 4. Reload view parameters
    
    master_t::subsystem<View>().reloadViewParams(bg_size, world_size);
    
    // 5. Preload background music
    if (!master_t::subsystem<cd::SimpleAudioEngine>().isBackgroundMusicPlaying())
    {
        const std::string bg_music_file = res::background_sound("test_bg_music");
        master_t::subsystem<cd::SimpleAudioEngine>().preloadBackgroundMusic(bg_music_file.c_str());
        master_t::subsystem<cd::SimpleAudioEngine>().playBackgroundMusic(bg_music_file.c_str(), true);
        master_t::subsystem<cd::SimpleAudioEngine>().pauseBackgroundMusic();
        master_t::subsystem<cd::SimpleAudioEngine>().setBackgroundMusicVolume(float(0.1));
    }
    
    // 6. Create level objects
    auto background = objects::Background::create(bg_name);

    auto platform = objects::Platform::create( pr::Vec2(15, 10), pr::Vec2(10, 1) );
    auto ball = objects::Ball::create( pr::Vec2(22, 15) );
    auto rope = objects::Rope::create( pr::Vec2(15, 10), platform, pr::Vec2(22, 15.5), ball );
    //auto rope = objects::Rope::create( pr::Vec2(7, 11), ball, pr::Vec2(10, 14.5), platform );
}

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
#include "objects/enemy.hpp"

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
    const std::string bg_name_base = res::picture("test_background_base");
    const std::string bg_name_lvl_1 = res::picture("test_background_lvl_1");
    
    cc::CCSprite *bg = cc::CCSprite::create(bg_name_base.c_str());
    cc::CCSize bg_size = bg->getContentSize();
    bg->release();
    
    // 3. Load world params
    pr::Vec2 world_size(96.f, 32.f);
    
    master_t::subsystem<Physics>().reloadWorldParams(world_size);
    
    // 4. Reload view parameters
    
    master_t::subsystem<View>().reloadViewParams(bg_size, world_size);
    
    // 5. Preload background music
    const std::string bg_music_file = res::background_sound("wow_trek_7");
    master_t::subsystem<cd::SimpleAudioEngine>().preloadBackgroundMusic(bg_music_file.c_str());
    master_t::subsystem<cd::SimpleAudioEngine>().playBackgroundMusic(bg_music_file.c_str(), true);
    master_t::subsystem<cd::SimpleAudioEngine>().pauseBackgroundMusic();
    master_t::subsystem<cd::SimpleAudioEngine>().setBackgroundMusicVolume(float(0.1));
    
    // 6. Create level objects
    auto background = objects::Background::create(bg_name_base, bg_name_lvl_1);
    
//    auto enemy1 = objects::Enemy::create(pr::Vec2(48.f, 16.f));

    //auto platform00 = objects::Platform::create( pr::Vec2(0, 0), pr::Vec2(1, 1) );
    //auto platformx0 = objects::Platform::create( pr::Vec2(world_size.x, 0), pr::Vec2(1, 1) );
    //auto platform0y = objects::Platform::create( pr::Vec2(0, world_size.y), pr::Vec2(1, 1) );
    //auto platformxy = objects::Platform::create( pr::Vec2(world_size.x, world_size.y), pr::Vec2(1, 1) );
    
    //auto platform1 = objects::Platform::create( pr::Vec2(47, 19), pr::Vec2(10, 1) );
    //auto platform2 = objects::Platform::create( pr::Vec2(17, 10), pr::Vec2(13, 4) );
    //auto platform3 = objects::Platform::create( pr::Vec2(77, 12), pr::Vec2(17, 2) );
    //auto ball = objects::Ball::create( pr::Vec2(60, 15) );
    //auto rope = objects::Rope::create( pr::Vec2(47, 17.5), platform1, pr::Vec2(60, 15.5), ball );

    //pr::Vec2* vertices = new pr::Vec2[4];
    //vertices[0] = pr::Vec2(10,20);
    //vertices[1] = pr::Vec2(10,10);
    //vertices[2] = pr::Vec2(20,10);
    //vertices[3] = pr::Vec2(20,20);
    //auto platform = objects::Platform::create( vertices, 4 );
    //delete[] vertices;
    //auto ball = objects::Ball::create( pr::Vec2(22, 15) );
    //auto rope = objects::Rope::create( pr::Vec2(15, 10), platform, pr::Vec2(22, 15.5), ball );

    //auto rope = objects::Rope::create( pr::Vec2(7, 11), ball, pr::Vec2(10, 14.5), platform );
}

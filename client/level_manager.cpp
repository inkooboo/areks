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
#include "player.hpp"
#include "loop.hpp"

#include "resource_utils.hpp"

#include "objects/background.hpp"
#include "objects/platform.hpp"
#include "objects/ball.hpp"
#include "objects/rope.hpp"
#include "objects/enemy.hpp"


//for testing
#include <time.h>

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
    // 0. Unschedule all
    master_t::subsystem<Loop>().reload();
    
    // 1. Clear all objects
    master_t::subsystem<ObjectManager>().reloadObjectManager();
    master_t::subsystem<Player>().reloadPlayer();
    
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
#ifndef NO_SOUND
    const std::string bg_music_file = res::background_sound("wow_trek_7");
    master_t::subsystem<cd::SimpleAudioEngine>().preloadBackgroundMusic(bg_music_file.c_str());
    master_t::subsystem<cd::SimpleAudioEngine>().playBackgroundMusic(bg_music_file.c_str(), true);
    master_t::subsystem<cd::SimpleAudioEngine>().pauseBackgroundMusic();
    master_t::subsystem<cd::SimpleAudioEngine>().setBackgroundMusicVolume(float(0.1));
#endif
    
    // 6. Create level objects
    auto background = objects::Background::create(bg_name_base, bg_name_lvl_1);
    
    auto enemy1 = objects::Enemy::create(pr::Vec2(40.5f, 9.5f));

	//need using CCW winding for platform description!
	std::vector<pr::Vec2> points;
	points.push_back( pr::Vec2(40, 30) );
	points.push_back( pr::Vec2(37.5, 25) );
	points.push_back( pr::Vec2(32.5, 22.5) );
	points.push_back( pr::Vec2(37.5, 20) );
	points.push_back( pr::Vec2(40, 15) );
	points.push_back( pr::Vec2(42.5, 20) );
	points.push_back( pr::Vec2(47.5, 22.5) );
	points.push_back( pr::Vec2(42.5, 25) );

	auto platform1 = objects::Platform::create( points );
	auto ball1 = objects::Ball::create( pr::Vec2(40, 40) );
	auto ball2 = objects::Ball::create( pr::Vec2(41, 40) );
	auto ball3 = objects::Ball::create( pr::Vec2(42, 40) );
	auto ball4 = objects::Ball::create( pr::Vec2(43, 40) );
	auto ball5 = objects::Ball::create( pr::Vec2(44, 40) );
	auto ball6 = objects::Ball::create( pr::Vec2(45, 40) );

	for( auto it = points.begin(), end = points.end(); it!=end; ++it )
	{
		it->x+=15;
		it->y-=7;
	}

	auto platform2 = objects::Platform::create( points );

	points.clear();

	pr::Vec2 ground_begin(10, 7);
	float ground_length = 60;
	pr::Vec2 ground_coord = ground_begin;
	points.push_back( ground_coord );

	ground_coord.y -= 4;
	points.push_back( ground_coord );

	ground_coord.x += ground_length;
	points.push_back( ground_coord );

	std::srand( time(0) );

	size_t min_ground_y = 7;
	for( float x = ground_coord.x - 5; x > ground_begin.x; x-=5 )
	{
		points.push_back( pr::Vec2( x, (float(rand() % 2) / 2.f + min_ground_y + 1) ) );
	}

	auto platform3 = objects::Platform::create( points );

	master_t::subsystem<Player>().createAvatar( pr::Vec2(ground_begin.x + 40.f, min_ground_y + 8) );

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

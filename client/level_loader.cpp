//
//  level_manager.cpp
//  areks
//
//  Created by inkooboo on 8/15/12.
//
//

#include "level_loader.hpp"

#include "view.hpp"
#include "physics.hpp"
#include "object_manager.hpp"
#include "player.hpp"
#include "loop.hpp"
#include "effect_manager.hpp"

#include "resource_utils.hpp"

#include "objects/background.hpp"
#include "objects/platform.hpp"

#include <json/json.h>

void LevelLoader::start()
{
}

void LevelLoader::stop()
{
    
}

LevelLoader::LevelLoader()
{
}

void LevelLoader::loadLevel(const char *level_name)
{
    log() << "Begin loading of level \"" << level_name << "\"";
    std::string level_description_str = res::load_file_content(res::level_description(level_name));
    
    Json::Value description;
    Json::Reader parser;
    parser.parse(level_description_str, description);
    
    log() << "reload scheduler";
    master_t::subsystem<Loop>().reload();
    
    log() << "reload effects";
    master_t::subsystem<EffectManager>().reload();
    
    log() << "clear old objects";
    master_t::subsystem<ObjectManager>().reload();
    log() << "reload avatar";
    master_t::subsystem<Player>().reload();
    

    log() << "load background";
    const std::string bg_name_base = res::picture(description["background_base"].asCString());
    const std::string bg_name_parallax = res::picture(description["background_parallax"].asCString());
    log() << "background base picture = " << bg_name_base;
    log() << "background parallax picture = " << bg_name_parallax;
    
    cc::CCSprite *bg = cc::CCSprite::create(bg_name_base.c_str());
    cc::CCSize bg_size = bg->getContentSize();
    bg->release();
    
    log() << "load world size";
    const Json::Value &world_size_descr = description["world_size"];
    float world_size_x = world_size_descr["width"].asFloat();
    float world_size_y = world_size_descr["height"].asFloat();
    pr::Vec2 world_size = pr::Vec2(world_size_x, world_size_y);
    log() << "world size = {" << world_size_x << "," << world_size_y << "}";
    
    log() << "reload physics";
    master_t::subsystem<Physics>().reload(world_size);
    
    log() << "reload view parameters";
    master_t::subsystem<View>().reload(bg_size, world_size);
    
#ifndef NO_SOUND
    log() << "preload background music";
    const std::string bg_music_file = res::background_sound(description["background_trek"].asCString());
    log() << "background music file = " << bg_music_file;
    master_t::subsystem<cd::SimpleAudioEngine>().preloadBackgroundMusic(bg_music_file.c_str());
    master_t::subsystem<cd::SimpleAudioEngine>().playBackgroundMusic(bg_music_file.c_str(), true);
    master_t::subsystem<cd::SimpleAudioEngine>().pauseBackgroundMusic();
    master_t::subsystem<cd::SimpleAudioEngine>().setBackgroundMusicVolume(float(0.3));
#endif
    
    log() << "create background";
    objects::Background::create(bg_name_base, bg_name_parallax);
    
    
    log() << "create platforms";
    const Json::Value &platforms = description["platforms"];
    for (auto it = platforms.begin(); it != platforms.end(); ++it)
    {
        const Json::Value &platform = *it;
        
        std::vector<pr::Vec2> points;
        for (unsigned int i = 0; i < platform.size(); ++i)
        {
            const Json::Value &point = platform[i];
            points.push_back(pr::Vec2(point["x"].asFloat(), point["y"].asFloat()));
        }
        objects::Platform::create(points);
    }
    
    log() << "create objects";
    const Json::Value objects = description["objects"];
    auto obj_names = objects.getMemberNames();
    for (auto it = obj_names.begin(); it != obj_names.end(); ++it)
    {
        log() << "    " << *it;
        const Json::Value obj = objects[*it];
        master_t::subsystem<ObjectManager>().create_object_factory(obj);
    }
    
    log() << "create player avatar";
    const Json::Value &player_position = description["player_start_position"];
	master_t::subsystem<Player>().createAvatar( pr::Vec2(player_position["x"].asFloat(), player_position["y"].asFloat()) );
}

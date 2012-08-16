//
//  level_manager.cpp
//  areks
//
//  Created by inkooboo on 8/15/12.
//
//

#include "level_manager.hpp"

void LevelManager::start()
{
    //read from config current level
}

void LevelManager::stop()
{
    
}

LevelManager::LevelManager()
{
    
}

const char * LevelManager::backgroundName() const
{
//    return "HelloWorld_very_big.png";
    return "HelloWorld_big.png";
//    return "HelloWorld.png";
//    return "HelloWorld_small.png";
}

pr::Vec2 LevelManager::worldSize() const
{
    return pr::Vec2(48.f, 32.f);
}

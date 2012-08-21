#include "game_logic.hpp"

#include "level_manager.hpp"

void GameLogic::start()
{
    master_t::subsystem<LevelManager>().loadLevel("");
    
    master_t::subsystem<cd::SimpleAudioEngine>().resumeBackgroundMusic();
}

void GameLogic::stop()
{
}

GameLogic::GameLogic()
{
}

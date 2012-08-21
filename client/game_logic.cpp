#include "game_logic.hpp"

#include "level_manager.hpp"

void GameLogic::start()
{
    master_t::subsystem<LevelManager>().loadLevel("");
}

void GameLogic::stop()
{
}

GameLogic::GameLogic()
{
}

#include "game_logic.hpp"

#include "physics.hpp"
#include "level_manager.hpp"
#include "objects/background.hpp"
#include "objects/platform.hpp"

void GameLogic::start()
{
    this->CreateExampleLevel();
}

void GameLogic::stop()
{
}

GameLogic::GameLogic()
{
}

//just for testing
void GameLogic::CreateExampleLevel()
{
    auto background = new objects::Background(master_t::subsystem<LevelManager>().backgroundName());
    
    pr::Vec2 w_size = master_t::subsystem<Physics>().worldSize();

    auto obj = objects::Platform::create( pr::Vec2(10, 4), pr::Vec2(10, 1) );

}
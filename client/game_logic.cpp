#include "game_logic.hpp"

#include "physics.hpp"
#include "level_manager.hpp"

#include "objects/background.hpp"
#include "objects/platform.hpp"
#include "objects/ball.hpp"
#include "objects/rope.hpp"

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
    auto background = objects::Background::create(master_t::subsystem<LevelManager>().backgroundName());
    
    pr::Vec2 w_size = master_t::subsystem<Physics>().worldSize();

    auto platform = objects::Platform::create( pr::Vec2(15, 10), pr::Vec2(10, 1) );
    auto ball = objects::Ball::create( pr::Vec2(22, 15) );
    auto rope = objects::Rope::create( pr::Vec2(15, 10), platform, pr::Vec2(22, 15.5), ball );
    //auto rope = objects::Rope::create( pr::Vec2(7, 11), ball, pr::Vec2(10, 14.5), platform );
}
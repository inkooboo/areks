#include "GameLogic.hpp"

#include "Physics.hpp"
#include "objects/Platform.hpp"
#include "master.hpp"


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
    pr::Vec2 w_size = master_t::subsystem<Physics>().worldSize();
    w_size.x() /= 2;
    w_size.y() /= 2;

    auto obj = objects::Platform::create( w_size, pr::Vec2( w_size.x()/2, w_size.y()/4 ) );

}
#ifndef _AREKS_GAME_LOGIC_HPP_
#define _AREKS_GAME_LOGIC_HPP_

#include "subsystem.hpp"

class GameLogic : public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;

public:
    GameLogic();

    //just for testing
    void CreateExampleLevel();
};

#endif
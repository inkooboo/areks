#ifndef _AREKS_GAME_LOGIC_HPP_
#define _AREKS_GAME_LOGIC_HPP_

# include "subsystem.hpp"
# include "defs.hpp"

class GameLogic : public cc::CCObject, public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;

public:
    GameLogic();
    
    void loadScene(cc::CCScene *scene, float delay = 0);

    void onLoadScene(float);
    void onEndLoading(float);
    
private:
    void transitScene(cc::CCScene *scene);
    
    cc::CCScene *m_current_scene;
};

#endif

#ifndef _GAME_LAYER_HPP_
# define _GAME_LAYER_HPP_

# include "master.hpp"

# include <cocos2d.h>

class game_layer_t : public cocos2d::CCLayer, public subsystem_t
{
    virtual void start();
    virtual void stop();

public:
    game_layer_t();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // a selector callback
    void menuOpenCallback(cocos2d::CCObject* pSender);

    void show();
    void hide();

    void update_scene();

private:
    cocos2d::CCSize m_size;

    cocos2d::CCMenu *m_menu;
};

#endif //_GAME_LAYER_HPP_
#include "game_logic.hpp"

#include "splash_screen.hpp"
#include "view.hpp"
#include "main_menu.hpp"
#include "level_manager.hpp"
#include "loop.hpp"
#include "loading_screen.hpp"

void GameLogic::start()
{
    m_current_scene = master_t::subsystem<SplashScreen>().scene();
	cc::CCDirector::sharedDirector()->runWithScene(m_current_scene);

    loadScene(master_t::subsystem<MainMenu>().scene(), 1.f);
}

void GameLogic::stop()
{
    master_t::subsystem<cd::SimpleAudioEngine>().pauseBackgroundMusic();
}

GameLogic::GameLogic()
{
}

void GameLogic::loadScene(cc::CCScene *scene, float delay)
{
    using namespace cocos2d;
    
    m_new_scene = scene;

    if (m_current_scene == master_t::subsystem<View>().scene())
    {
        master_t::subsystem<cd::SimpleAudioEngine>().pauseBackgroundMusic();
    }

    if (scene == master_t::subsystem<LoadingScreen>().scene())
    {
        cc::CCDirector::sharedDirector()->replaceScene(m_new_scene);
        
        m_new_scene = master_t::subsystem<View>().scene();
    }
    
    master_t::subsystem<Loop>().scheduleSelector( schedule_selector(GameLogic::onLoadScene), this, 0, false, 0, delay);
}


void GameLogic::onLoadScene(cc::CCObject *)
{
    if (m_new_scene == master_t::subsystem<View>().scene())
    {
        master_t::subsystem<LevelManager>().loadLevel("");
        
        master_t::subsystem<cd::SimpleAudioEngine>().resumeBackgroundMusic();
    }
    
    cc::CCDirector::sharedDirector()->replaceScene(m_new_scene);
    
    m_current_scene = m_new_scene;
}



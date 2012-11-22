#include "game_logic.hpp"

#include "splash_screen.hpp"
#include "view.hpp"
#include "main_menu.hpp"
#include "level_loader.hpp"
#include "loop.hpp"
#include "loading_screen.hpp"

const static float TRANSITION_TIME = .5f;

void GameLogic::start()
{
#ifdef NO_MENU
    m_current_scene = master_t::subsystem<SplashScreen>().scene();
	cc::CCDirector::sharedDirector()->runWithScene(m_current_scene);
    loadScene(master_t::subsystem<LoadingScreen>().scene());
#else
    m_current_scene = master_t::subsystem<SplashScreen>().scene();
	cc::CCDirector::sharedDirector()->runWithScene(m_current_scene);
    loadScene(master_t::subsystem<MainMenu>().scene(), 1.f);
#endif

}

void GameLogic::stop()
{
#ifndef NO_SOUND
    master_t::subsystem<cd::SimpleAudioEngine>().pauseBackgroundMusic();
#endif
}

GameLogic::GameLogic()
{
}

void GameLogic::loadScene(cc::CCScene *new_scene, float delay)
{
    using namespace cocos2d;
    
    if (m_current_scene == master_t::subsystem<View>().scene())
    {
#ifndef NO_SOUND
        master_t::subsystem<cd::SimpleAudioEngine>().pauseBackgroundMusic();
#endif
    }

    m_current_scene = new_scene;
    cc::CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GameLogic::onLoadScene), this, 0, false, 0, delay);
}

void GameLogic::onLoadScene(float)
{
    using namespace cocos2d;

    transitScene(m_current_scene);

    if (m_current_scene == master_t::subsystem<LoadingScreen>().scene())
    {
        m_current_scene = master_t::subsystem<View>().scene();
        cc::CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GameLogic::onEndLoading), this, 0, false, 0, TRANSITION_TIME*2);
    }
}

void GameLogic::onEndLoading(float)
{
    transitScene(m_current_scene);
    
    master_t::subsystem<LevelLoader>().loadLevel("test_level");
    
#ifndef NO_SOUND
    master_t::subsystem<cd::SimpleAudioEngine>().resumeBackgroundMusic();
#endif
}

void GameLogic::transitScene(cc::CCScene *scene)
{
    cc::CCTransitionScene *transition = cc::CCTransitionFade::create(TRANSITION_TIME, scene);
    
    cc::CCDirector::sharedDirector()->replaceScene(transition);
}



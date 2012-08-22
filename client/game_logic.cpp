#include "game_logic.hpp"

#include "splash_screen.hpp"
#include "view.hpp"
#include "level_manager.hpp"

void GameLogic::start()
{
	cc::CCDirector::sharedDirector()->runWithScene(master_t::subsystem<SplashScreen>().scene());

	master_t::subsystem<LevelManager>().loadLevel("");


	    
//    cc::CCTransitionScene *transition_effect = cc::CCTransitionCrossFade::create(2.f, master_t::subsystem<View>().scene());//, cc::ccRED);
//    cc::CCDirector::sharedDirector()->replaceScene(transition_effect);

    cc::CCDirector::sharedDirector()->replaceScene(master_t::subsystem<View>().scene());

    master_t::subsystem<cd::SimpleAudioEngine>().resumeBackgroundMusic();
}

void GameLogic::stop()
{
    master_t::subsystem<cd::SimpleAudioEngine>().pauseBackgroundMusic();
}

GameLogic::GameLogic()
{
}

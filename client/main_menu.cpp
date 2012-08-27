//
//  main_menu.cpp
//  areks
//
//  Created by inkooboo on 8/23/12.
//
//

#include "main_menu.hpp"
#include "master.hpp"
#include "resource_utils.hpp"
#include "game_logic.hpp"
#include "view.hpp"
#include "loading_screen.hpp"
#include "app_delegate.h"

void MainMenu::start()
{
    using namespace cocos2d;
    
    m_menu = cc::CCMenu::create();
    
    cc::CCSize size = cc::CCDirector::sharedDirector()->getWinSize();
    
    cc::CCMenuItemFont *start = cc::CCMenuItemFont::create("START", this,  menu_selector(MainMenu::onStart));
    m_menu->addChild(start);
    
    cc::CCMenuItemFont *exit = cc::CCMenuItemFont::create("EXIT", this,  menu_selector(MainMenu::onExit));
    m_menu->addChild(exit);
    
    m_menu->alignItemsVertically();
    
    m_scene->addChild(m_menu);
}

void MainMenu::stop()
{
    m_scene->removeChild(m_menu, true);
}

MainMenu::MainMenu()
{
    m_scene = new cc::CCScene();
    m_scene->init();
}

MainMenu::~MainMenu()
{
}

cc::CCScene * MainMenu::scene()
{
    return m_scene;
}

void MainMenu::onStart(cc::CCObject *)
{
    master_t::subsystem<GameLogic>().loadScene(master_t::subsystem<LoadingScreen>().scene(), 1);
}

void MainMenu::onExit(cc::CCObject *)
{
    master_t::subsystem<AppDelegate>().end_application();    
}

//
//  loading_screen.cpp
//  areks
//
//  Created by inkooboo on 8/23/12.
//
//

#include "loading_screen.hpp"
#include "master.hpp"
#include "resource_utils.hpp"

void LoadingScreen::start()
{
    m_layer = cc::CCLayer::create();
    
    cc::CCLabelTTF *loading = cc::CCLabelTTF::create("Loading...", "", 32);
    
    m_layer->addChild(loading);
    
    cc::CCSize size = cc::CCDirector::sharedDirector()->getWinSize();
    loading->setPosition(ccp(size.width/2, size.height/2));
    
    m_scene->addChild(m_layer);
}

void LoadingScreen::stop()
{
    m_scene->removeChild(m_layer, true);
}

LoadingScreen::LoadingScreen()
{
    m_scene = new cc::CCScene();
    m_scene->init();
}

LoadingScreen::~LoadingScreen()
{
}

cc::CCScene * LoadingScreen::scene()
{
    return m_scene;
}

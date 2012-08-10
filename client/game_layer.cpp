#include "game_layer.hpp"
#include "cocos_scene.hpp"

USING_NS_CC;

game_layer_t::game_layer_t()
{
    init();
}

void game_layer_t::start()
{
    // add layer as a child to scene
    master_t::subsystem<cocos_scene_t>().addChild(this);
}

void game_layer_t::stop()
{
    master_t::subsystem<cocos_scene_t>().removeChild(this, false);
}


// on "init" you need to initialize your instance
bool game_layer_t::init()
{
    if (!CCLayer::init())
    {
        return false;
    }

    this->setTouchEnabled(true);
    
    m_size = CCDirector::sharedDirector()->getWinSize();

    CCSprite *background = CCSprite::create("HelloWorld.png");

    cocos2d::CCSize bg_size = background->getContentSize();
    float bg_scale_x = m_size.width / bg_size.width;
    float bg_scale_y = m_size.height / bg_size.height;
    background->setScaleX(bg_scale_x);
    background->setScaleY(bg_scale_y);
    background->setPosition( ccp(m_size.width/2, m_size.height/2) );
    this->addChild(background, 0);
    
    
    CCMenuItemImage *pMenuItem = CCMenuItemImage::create(
                                        "shesterenka.png",
                                        "shesterenka_p.png",
                                        this,
                                        menu_selector(game_layer_t::menuOpenCallback) );
    pMenuItem->setPosition( ccp(m_size.width - 27, 28) );

    m_menu = CCMenu::create(pMenuItem, NULL);
    m_menu->setPosition( CCPointZero );
    m_menu->setVisible(true);
    this->addChild(m_menu, 1);

    return true;
}

void game_layer_t::menuOpenCallback(CCObject* pSender)
{
    master_t::subsystem<cocos_scene_t>().end_scene();
}

void game_layer_t::show()
{
    m_menu->setVisible(true);
}

void game_layer_t::hide()
{
    m_menu->setVisible(false);
}

void game_layer_t::update_scene()
{

}



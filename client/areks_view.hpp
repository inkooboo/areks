//
//  arek_view.hpp
//  areks
//
//  Created by inkooboo on 11/22/12.
//
//

#ifndef areks_arek_view_hpp
#define areks_arek_view_hpp

#include "defs.hpp"
#include "master.hpp"
#include "resource_utils.hpp"
#include "view.hpp"
#include "game_logic.hpp"
#include "main_menu.hpp"
#include "player.hpp"
#include "objects/player/body.hpp"

#include "effects/flying_text.hpp"


struct AreksView : public cc::CCObject, public View
{
    virtual void start() override
    {
        View::start();
        
        using namespace cocos2d;
        
        cc::CCMenuItemImage *pClose = cc::CCMenuItemImage::create(
                                                                  res::picture("CloseNormal").c_str(),
                                                                  res::picture("CloseSelected").c_str(),
                                                                  this,
                                                                  menu_selector(AreksView::menuExit) );
        
        pClose->setPosition( ccp(m_size.width - 27, m_size.height - 28) );
        
        cc::CCMenuItemImage *pReload = cc::CCMenuItemImage::create(
                                                                   res::picture("shesterenka").c_str(),
                                                                   res::picture("shesterenka_p").c_str(),
                                                                   this,
                                                                   menu_selector(AreksView::menuTest) );
        
        pReload->setPosition( ccp(m_size.width - 27, 28) );
        
        createGameLayerMenu(cc::CCArray::create(pClose, pReload, NULL));
    }
    
    void menuExit(cc::CCObject*)
    {
        master_t::subsystem<GameLogic>().loadScene(master_t::subsystem<MainMenu>().scene());
    }
    
    void menuTest(cc::CCObject*)
    {
        /// test sound fx. Remove it.
#ifndef NO_SOUND
        master_t::subsystem<cd::SimpleAudioEngine>().playEffect(res::sound_effect("046").c_str());
#endif
        ///
        
        /// test effects. Remove it.
        pr::Vec2 world_size = master_t::subsystem<Physics>().worldSize();
        world_size *= .5f;
        
        effects::FlyingText::create(world_size, m_game_layer, "Test Text", 14, cc::ccc3(190, 255, 190), 5.f);
        ///
        
    }
    
    virtual void manageCameraPositionAndScale(float t) override
    {
        Player &player = master_t::subsystem<Player>();
        
        if (player.isAvatarCreated())
        {
            pr::Vec2 body_postion = player.getBody()->getPosition();
            
            m_cur_positon = body_postion;
        }
        
        validateScale();
        validatePosition();
    }
    
};

#endif
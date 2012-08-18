//
//  background.cpp
//  areks
//
//  Created by inkooboo on 8/15/12.
//
//

#include "background.hpp"

#include "view.hpp"
#include "physics.hpp"

namespace objects
{

    Background* Background::create(const std::string &file_name)
    {
        return new Background( file_name );
    }
    
    Background::Background(const std::string &file_name)
    {
        pr::Vec2 world_size = master_t::subsystem<Physics>().worldSize();
        
        _sprite = cocos2d::CCSprite::create(file_name.c_str());
        cc::ccBlendFunc func={GL_ONE, GL_ZERO};
        _sprite->setBlendFunc( func );
        _position = world_size;
        _position *= .5;

        draw();
        master_t::subsystem<View>().gameLayer()->addChild( _sprite );
    }

    Background::~Background()
    {
        _sprite->removeFromParentAndCleanup(true);
        _sprite->release();
        //master_t::subsystem<Physics>().worldEngine()->DestroyBody(_body);
    }
        
    void Background::draw()
    {
        draw_sprite_helper(_sprite, _position, 0);
    }

    b2Body* Background::getBody()
    {
        //TODO
        return 0;
    }

} //namespace objects
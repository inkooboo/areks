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
    
    Background::Background(const std::string &file_name)
    {
        pr::Vec2 world_size = master_t::subsystem<Physics>().worldSize();
        
        const static b2Vec2 topLeft_c(0, world_size.y);
        const static b2Vec2 topRight_c(world_size.x, world_size.y);
        const static b2Vec2 bottomLeft_c(0, 0);
        const static b2Vec2 bottomRight_c(world_size.x, 0);
        
        // Creates sides
        b2BodyDef sideBodyDef;
        b2EdgeShape sideShape;
        b2FixtureDef sideFixtureDef;
        
        sideBodyDef.position.Set(0, 0);
        sideFixtureDef.shape = &sideShape;
        
        sideShape.Set(topLeft_c, topRight_c);
        sideShape.Set(bottomLeft_c, topLeft_c);
        sideShape.Set(bottomLeft_c, bottomRight_c);
        sideShape.Set(bottomRight_c, topRight_c);
        
        _body = master_t::subsystem<Physics>().worldEngine()->CreateBody(&sideBodyDef);
        
        _body->CreateFixture(&sideFixtureDef);

        _sprite = cocos2d::CCSprite::create(file_name.c_str());
        _sprite->setUserData((void *)this);
        _position = world_size;
        _position *= .5;

        draw();
        master_t::subsystem<View>().gameLayer()->addChild( _sprite );
    }

    Background::~Background()
    {
        _sprite->removeFromParentAndCleanup(true);
        _sprite->release();
        master_t::subsystem<Physics>().worldEngine()->DestroyBody(_body);
    }
        
    void Background::draw()
    {
        _sprite->setPosition(master_t::subsystem<View>().toScreenCoordinates(_position));
        _sprite->setScale(master_t::subsystem<View>().pixel_scale());
    }

} //namespace objects
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

        //
        //init physics
        //

        defs::st::OneShapeDef def;
        def.setUserData( (void*)this );
        float sea_level = world_size.y/25;
        def.setShapeEdge( b2Vec2(-world_size.x, sea_level), b2Vec2(world_size.x * 3, sea_level) );
        def.setSensor(true);
        _body = master_t::subsystem<Physics>().CreateBody( def );

        //
        //init view
        //
        
        _sprite = cocos2d::CCSprite::create(file_name.c_str());
        cc::ccBlendFunc func = {GL_ONE, GL_ZERO};
        _sprite->setBlendFunc( func );
        _position = world_size;
        _position *= .5;

        draw();
        addSprite(_sprite);
    }

    Background::~Background()
    {
        removeSprite(_sprite);
        //master_t::subsystem<Physics>().worldEngine()->DestroyBody(_body);
    }
        
    void Background::draw()
    {
        drawSpriteHelper(_sprite, _position, 0);
    }

    b2Body* Background::getBody()
    {
        //TODO
        return 0;
    }

    void Background::collide( BaseObject* other )
    {
        other->destroy();
    }

} //namespace objects
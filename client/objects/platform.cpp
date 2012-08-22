#include "platform.hpp"

#include "master.hpp"

#include "physics.hpp"
#include "view.hpp"

namespace objects
{

    Platform* Platform::create(pr::Vec2 const& coordinates, pr::Vec2 const& size)
    {
        return new Platform(coordinates, size);
    }

    Platform::Platform(pr::Vec2 const& coordinates, pr::Vec2 const& size)
        : _position( coordinates )
    {
        //init physics
        defs::st::OneShapeDef def;
        def.setPosition( _position.tob2Vec2() );
        def.setUserData( (void*)this );
        def.setShapeBox( size.x/2, size.y/2 );
        _body = master_t::subsystem<Physics>().CreateBody( def );

        //init view
        unsigned char color[] = {100, 100, 100};
        cc::CCTexture2D* texture = new cc::CCTexture2D();
        texture->autorelease();
        texture->initWithData(color, cocos2d::kCCTexture2DPixelFormat_RGB888, 1, 1, size.toCCSize() );

        _sprite = cc::CCSprite::create( texture );
        
        addSprite(_sprite);
        draw();
    }

    Platform::~Platform()
    {
        removeSprite(_sprite);
        //master_t::subsystem<Physics>().worldEngine()->DestroyBody(_body);
    }
        
    void Platform::draw()
    {
        drawSpriteHelper(_sprite, _position, 0);
    }

    b2Body* Platform::getBody()
    {
        return _body.get();
    }

}//end namespace objects
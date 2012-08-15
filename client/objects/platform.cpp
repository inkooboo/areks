#include "platform.hpp"

#include "master.hpp"

#include "physics.hpp"

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
        b2BodyDef bodyDef;
        bodyDef.position.Set( _position.x, _position.y );

        _body = master_t::subsystem<Physics>().worldEngine()->CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(size.x/2, size.y/2);

        _body->CreateFixture(&shape, 0.0f);

        //init view
        unsigned char color[] = {100, 100, 100};
        cc::CCTexture2D* texture = new cc::CCTexture2D();
        texture->autorelease();
        texture->initWithData(color, cocos2d::kCCTexture2DPixelFormat_RGB888, 1, 1, size.toCCSize() );

        _sprite = cc::CCSprite::create( texture );
        
        master_t::subsystem<View>().gameLayer()->addChild( _sprite );
    }

    Platform::~Platform()
    {
        _sprite->removeFromParentAndCleanup(true);
        _sprite->release();
        master_t::subsystem<Physics>().worldEngine()->DestroyBody(_body);
    }
        
    void Platform::draw()
    {
        _sprite->setPosition( _position.toCCPoint() );
    }

}//end namespace objects
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

    Background* Background::create(const std::string &file_name_base, const std::string &file_name_lvl_1)
    {
        return new Background( file_name_base, file_name_lvl_1 );
    }
    
    Background::Background(const std::string &file_name_base,  const std::string &file_name_lvl_1)
    {
        pr::Vec2 world_size = master_t::subsystem<Physics>().worldSize();

        //
        //init physics
        //

        defs::st::OneShapeDef def;
        def.setUserData( (void*)this );
        float sea_level = world_size.y/30;
        def.setShapeEdge( b2Vec2(-world_size.x, sea_level), b2Vec2(world_size.x * 3, sea_level) );
        def.setSensor(true);
        _body = master_t::subsystem<Physics>().CreateBody( def );

        //
        //init view
        //
        
        _sprite_base = cocos2d::CCSprite::create(file_name_base.c_str());
        cc::ccBlendFunc func = {GL_ONE, GL_ZERO};
        _sprite_base->setBlendFunc( func );

        addSprite(_sprite_base, -2);

        _sprite_lvl_1 = cocos2d::CCSprite::create(file_name_lvl_1.c_str());
        cc::ccBlendFunc blendFunc = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
        _sprite_lvl_1->setBlendFunc( blendFunc );
        
        addSprite(_sprite_lvl_1, -1);
        draw();
    }

    Background::~Background()
    {
        removeSprite(_sprite_base);
        removeSprite(_sprite_lvl_1);
        //master_t::subsystem<Physics>().worldEngine()->DestroyBody(_body);
    }
        
    void Background::draw()
    {
        pr::Vec2 world_size = master_t::subsystem<Physics>().worldSize();
        world_size *= .5;

        drawSpriteHelper(_sprite_base, world_size, 0);
        
        View &v = master_t::subsystem<View>();

        pr::Vec2 cam_pos = v.currentCameraPosition();
        cam_pos -= world_size;
        cam_pos *= 0.5;
        
        world_size += cam_pos;
        
        const cc::CCPoint &prev_position = _sprite_lvl_1->getPosition();
        cc::CCPoint cur_position = master_t::subsystem<View>().toScreenCoordinates(world_size);
        if (prev_position.x != cur_position.x || prev_position.y != cur_position.y)
        {
            _sprite_lvl_1->setPosition(cur_position);
        }
        
        float prev_scale = _sprite_lvl_1->getScale();
        float cur_scale = master_t::subsystem<View>().pixelScale() * 0.9;
        if (prev_scale != cur_scale)
        {
            _sprite_lvl_1->setScale(cur_scale);
        }
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
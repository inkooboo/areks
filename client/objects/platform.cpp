#include "platform.hpp"

#include "master.hpp"

#include "physics.hpp"
#include "view.hpp"

#include "resource_utils.hpp"
#include "triangulator.hpp"

#include "polygon_sprite.hpp"

namespace objects
{
	static const float PLATFORM_RESTITUTION = 0.2f;
	static const float PLATFORM_FRICTION = 0.3f;

    Platform::Platform(const Json::Value &description)
        : BaseObject(description)
    {
		assert( (description["points"].isArray() && (description["points"].size() > 2)) && "Min vertices count of platform = 3!");

        const Json::Value &points = description["points"];
        std::vector<pr::Vec2> vertices;
        for (unsigned int i = 0; i < points.size(); ++i)
        {
            const Json::Value &point = points[i];
            vertices.push_back(pr::Vec2(point["x"].asFloat(), point["y"].asFloat()));
        }
        
        Vector2dVector triangles;
		Triangulate::Process( vertices, triangles );

		pr::Vec2 lower_bound = vertices[0], upper_bound = vertices[0];
		for( auto it = vertices.begin(), end = vertices.end(); it!=end; ++it )
		{
			lower_bound.x = std::min(it->x, lower_bound.x);
			lower_bound.y = std::min(it->y, lower_bound.y);
			upper_bound.x = std::max(it->x, upper_bound.x);
			upper_bound.y = std::max(it->y, upper_bound.y);
		}
		_center = upper_bound + lower_bound;
		_center /= 2.f;

		//
        //init physics
		//
		b2BodyDef body_def;
		body_def.type = b2_staticBody;
		body_def.position = b2Vec2( _center.tob2Vec2() );
		body_def.userData = (void*)this;

		b2PolygonShape shape;

		b2FixtureDef fixt_def;
		fixt_def.friction = PLATFORM_FRICTION;
		fixt_def.restitution = PLATFORM_RESTITUTION;
		fixt_def.shape = &shape;
		fixt_def.filter.categoryBits = filter::PLATFORMS;
		fixt_def.filter.maskBits = filter::ALL;

		_body = master_t::subsystem<Physics>().worldEngine()->CreateBody( &body_def );

		b2Vec2 v[3];
		for( size_t i=0, count = triangles.size()/3; i<count; ++i )
		{
			v[0] = (triangles[i*3] - _center).tob2Vec2();
			v[1] = (triangles[i*3+1] - _center).tob2Vec2();
			v[2] = (triangles[i*3+2] - _center).tob2Vec2();
			shape.Set( v, 3 );

			_body->CreateFixture( &fixt_def );
		}

		//
        //init view
		//

		//init ground
		cc::CCPoint origin = lower_bound.toCCPoint();
		cc::CCSize rect_size = (upper_bound - lower_bound).toCCSize();
		cc::CCRect rect( origin.x,origin.y, rect_size.width, rect_size.height );

		cc::CCSprite* sprite = cc::CCSprite::create( res::picture("ground").c_str() );
		cc::CCTexture2D* ground_tex = sprite->getTexture();
		
		cc::ccTexParams tex_params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
		ground_tex->setTexParameters( &tex_params );

		_ground_sprite = PolygonSprite::create( ground_tex, triangles, rect );
		//_ground_sprite->setPosition( _center.toCCPoint() );

		//init grass

		sprite = cc::CCSprite::create( res::picture("grass").c_str() );
		cc::CCTexture2D* grass_tex = sprite->getTexture();
		cc::ccTexParams grass_tex_params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_CLAMP_TO_EDGE };
		grass_tex->setTexParameters( &grass_tex_params );
		
		_grass_sprites = cc::CCSpriteBatchNode::create( grass_tex );

		float grass_height = grass_tex->getPixelsHigh();

		auto it_g = vertices.begin(), end_g = vertices.end(), prev_g = vertices.end();
		--prev_g;

		for( ; it_g != end_g; ++it_g )
		{
			//used CCW, so prev - right point and it - left point
			float w_length = pr::distance( *prev_g, *it_g );
			float length = master_t::subsystem<View>().worldToPixel( w_length );

			cc::CCSprite* grass_sprite = cc::CCSprite::create( grass_tex, cc::CCRect( 0, 0, length, grass_height ) );

			_grass_sprites->addChild( grass_sprite );

			_grass_points.push_back(  (*prev_g + *it_g)/2  );
			_grass_angles.push_back( pr::angleAxisX( *prev_g - *it_g ) );

			prev_g = it_g;
		}
        
        master_t::subsystem<View>().addSprite(_ground_sprite);
		master_t::subsystem<View>().addSprite(_grass_sprites, 1);
        draw();
    }

    Platform::~Platform()
    {
        master_t::subsystem<View>().removeSprite(_ground_sprite);
		master_t::subsystem<View>().removeSprite(_grass_sprites);
    }
        
    void Platform::draw()
    {
        master_t::subsystem<View>().drawSpriteHelper(_ground_sprite, _center.toCCPoint(), 0);
		for( unsigned int count = _grass_sprites->getChildren()->count(), i = 0; i < count; ++i )
		{
			cc::CCSprite* sprite = static_cast<cc::CCSprite*>( _grass_sprites->getChildren()->objectAtIndex(i) );
			master_t::subsystem<View>().drawSpriteHelper( sprite, _grass_points[i], _grass_angles[i] );
		}
    }

    b2Body* Platform::getBody()
    {
        return _body.get();
    }

}//end namespace objects
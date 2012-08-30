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

    Platform* Platform::create(std::vector<pr::Vec2> const& vertices)
    {
        return new Platform(vertices);
    }

    Platform::Platform(std::vector<pr::Vec2> const& vertices)
    {
		//convert polygon into triangles
		assert( (vertices.size()>2) && "Min vertices count of platform = 3!");

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
		cc::CCPoint origin = lower_bound.toCCPoint();
		cc::CCSize rect_size = (upper_bound - lower_bound).toCCSize();
		cc::CCRect rect( origin.x,origin.y, rect_size.width, rect_size.height );

		cc::CCSprite* sprite = cc::CCSprite::create( res::picture("ground").c_str() );
		cc::CCTexture2D* tex = sprite->getTexture();
		
		cc::ccTexParams tex_params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
		tex->setTexParameters( &tex_params );

		_sprite = PolygonSprite::create( tex, triangles, rect );
		_sprite->setPosition( _center.toCCPoint() );
        
		addSprite(_sprite);
        draw();
    }

    Platform::~Platform()
    {
        removeSprite(_sprite);
    }
        
    void Platform::draw()
    {
        drawSpriteHelper(_sprite, _center.toCCPoint(), 0);
    }

    b2Body* Platform::getBody()
    {
        return _body.get();
    }

}//end namespace objects
#include "rope.hpp"

#include "master.hpp"
#include <math.h>

#include "physics.hpp"
#include "view.hpp"

#define METER_IN_STICK (float)0.5
#define ROPE_WIDTH (float)0.25
//ROPE_DENSITY - mass of rope
#define ROPE_DENSITY 0.5
#define ROPE_FRICTION (float)0.0

namespace objects
{
   
    Rope::Rope( pr::Vec2 const& a_point, BaseObject* a_body, pr::Vec2 const& b_point, BaseObject* b_body )
        : Rope(a_point, a_body->getBody(), b_point, b_body->getBody())
    {
    }

    Rope::Rope( pr::Vec2 const& a_point, b2Body* a_body, pr::Vec2 const& b_point, b2Body* b_body )
        : BaseObject(Json::Value())
    {
        float distance = pr::distance( a_point, b_point );

        //
        //init physics
        //

        size_t stick_count = distance/METER_IN_STICK; //length of stick: METER_IN_STICK < stick_length < METER_IN_STICK*2
        float stick_length = distance/stick_count;

        //prepare rope sticks

        //calculate angle of sticks
        pr::Vec2 v = a_point - b_point;
        //float angle_y = pr::angle( v, pr::Vec2( 0, 1 ) );
        float angle_y = pr::angleAxisX( v );
        //float angle_x = pr::angle( v, pr::Vec2( 1, 0 ) );
        //if( angle_x > b2_pi/2 ) angle_y = -angle_y;

        //prepare sticks body definition
        b2BodyDef body_def;
        body_def.type = b2_dynamicBody;
        body_def.angle = angle_y;
        body_def.gravityScale = 0.5f;
        body_def.userData = (void*)this;

        b2Body* cur_body;
        b2Body* prev_body;

        //prepare sticks shape definition
        b2PolygonShape stick_shape;
        stick_shape.SetAsBox( stick_length/2, ROPE_WIDTH/2 );

        //prepare revolute joint definition
        b2RevoluteJointDef revolute_def;
        revolute_def.collideConnected = false;

        //prepare distance joint definition
        b2DistanceJointDef distance_def;
        distance_def.collideConnected = false;

        //prepare fixtures definition
        b2FixtureDef fixture_def;
        fixture_def.friction = ROPE_FRICTION;
        fixture_def.density = ROPE_DENSITY;
        fixture_def.shape = &stick_shape;
        fixture_def.filter.categoryBits = 0x0001;
        fixture_def.filter.maskBits = 0x0002;

        //calculate dx and dy for sticks
        float dx = (b_point.x - a_point.x)/stick_count;
        float dy = (b_point.y - a_point.y)/stick_count;

        //float d_height = stick_length * cos( angle_y );
        //float d_width = stick_length * sin( angle_y );

        //if(dx<0) d_width = -d_width;
        //if(dy<0) d_height = -d_height;

        //create rope sticks
        b2World* worldEngine = master_t::subsystem<Physics>().worldEngine();
        prev_body = a_body;
        for( size_t i = 0; i<stick_count; ++i )
        {
            //position - center of body
            body_def.position = b2Vec2( a_point.x + dx*i + dx/2, a_point.y + dy*i + dy/2);
            cur_body = worldEngine->CreateBody( &body_def );
            _sticks_bodies.push_back( cur_body );
            cur_body->CreateFixture( &fixture_def );

            b2Vec2 anchor(a_point.x + dx*i, a_point.y + dy*i);
            revolute_def.Initialize(prev_body, cur_body, anchor);
            _connections_bodies.push_back( worldEngine->CreateJoint( &revolute_def ) );

            distance_def.Initialize( prev_body, cur_body, b2Vec2( a_point.x + dx*i - dx/16, a_point.y + dy*i - dy/16 ), b2Vec2( a_point.x + dx*i + dx/16, a_point.y + dy*i + dy/16 ) );
            //distance_def.Initialize( prev_body, cur_body, prev_body->GetWorldCenter(), cur_body->GetWorldCenter() );
            worldEngine->CreateJoint( &distance_def );

            prev_body = cur_body;                        
        }

        b2Vec2 anchor(b_point.x, b_point.y);
        revolute_def.Initialize(cur_body, b_body, anchor);
        _connections_bodies.push_back( worldEngine->CreateJoint( &revolute_def ) );

        distance_def.Initialize( prev_body, b_body, b2Vec2(anchor.x - dx/16, anchor.y - dy/16), b2Vec2(anchor.x + dx/16, anchor.y + dy/16) );
        worldEngine->CreateJoint( &distance_def );

        ////init RopeJoint for stablizing rope
        //b2RopeJointDef ropeDef;
        //ropeDef.bodyA=a_body; //define bodies
        //ropeDef.bodyB=b_body;
        ////TODO set anchor points
        //ropeDef.localAnchorA = b2Vec2(0,0); //define anchors
        //ropeDef.localAnchorB = b2Vec2(0,0);
        //ropeDef.maxLength= distance + stick_length/3;
        //worldEngine->CreateJoint(&ropeDef); //create joint

        //
        //init view
        //
        {
            auto it = _sticks_bodies.begin();
            auto end = _sticks_bodies.end();

            unsigned char color[] = {100, 100, 100};
            cc::CCTexture2D* texture = new cc::CCTexture2D();
            texture->autorelease();
            texture->initWithData(color, cocos2d::kCCTexture2DPixelFormat_RGB888, 1, 1, pr::Vec2(stick_length, ROPE_WIDTH).toCCSize() );

            for( ; it!=end; ++it )
            {
                _sticks_sprites.push_back(cc::CCSprite::create( texture ));
            }

        }

        {
            auto it = _connections_bodies.begin();
            auto end = _connections_bodies.end();

            unsigned char color[] = {0, 0, 0};
            cc::CCTexture2D* texture = new cc::CCTexture2D();
            texture->autorelease();
            texture->initWithData(color, cocos2d::kCCTexture2DPixelFormat_RGB888, 1, 1, pr::Vec2( (float)0.1, (float)0.1 ).toCCSize() );

            for( ; it!=end; ++it )
            {
                _connections_sprites.push_back(cc::CCSprite::create( texture ));
            }

        }


        {
            auto it = _sticks_sprites.begin();
            auto end = _sticks_sprites.end();
            for( ; it!=end; ++it )
            {
                master_t::subsystem<View>().addSprite(*it);
            }

        }

        {
            auto it = _connections_sprites.begin();
            auto end = _connections_sprites.end();
            for( ; it!=end; ++it )
            {
                master_t::subsystem<View>().addSprite(*it);
            }

        }
        draw();
    }

    void Rope::draw()
    {
        for(size_t i=0; i<_sticks_bodies.size(); ++i)
        {
            master_t::subsystem<View>().drawSpriteHelper( _sticks_sprites[i], _sticks_bodies[i]->GetPosition(), _sticks_bodies[i]->GetAngle() );
        }

        for(size_t i=0; i<_connections_bodies.size(); ++i)
        {
            master_t::subsystem<View>().drawSpriteHelper( _connections_sprites[i], _connections_bodies[i]->GetAnchorA(), 0 );
        }
    }

    void Rope::updateState( float t )
    {
    }

    Rope::~Rope()
    {
        {
            auto it = _sticks_sprites.begin();
            auto end = _sticks_sprites.end();
            for( ; it!=end; ++it )
            {
                master_t::subsystem<View>().removeSprite(*it);
            }
        }
        {
            auto it = _connections_sprites.begin();
            auto end = _connections_sprites.end();
            for( ; it!=end; ++it )
            {
                master_t::subsystem<View>().removeSprite(*it);
            }
        }
        {
            auto it = _sticks_bodies.begin();
            auto end = _sticks_bodies.end();
            for( ; it!=end; ++it )
            {
                master_t::subsystem<Physics>().worldEngine()->DestroyBody(*it);
            }
        }

    }

    b2Body* Rope::getBody()
    {
        return 0;
    }

    void Rope::deleteJoint( b2Joint* joint )
    {
        auto it = std::find( _connections_bodies.begin(), _connections_bodies.end(), joint );
        //assert( it != _connections_bodies.end() );
        if( it != _connections_bodies.end() )
        {
            _connections_bodies.erase( it );
        }
    }

    pr::Vec2 Rope::getPosition() const
    {
        return pr::Vec2(0,0);
    }

}//end namespace objects
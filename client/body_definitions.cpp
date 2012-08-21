#include "body_definitions.hpp"

#include "master.hpp"
#include "physics.hpp"

BodyOwner::~BodyOwner()
{
    if( _body )
    {
        master_t::subsystem<Physics>().worldEngine()->DestroyBody( _body );
    }
}

void BodyOwner::reset( b2Body* body )
{
    master_t::subsystem<Physics>().worldEngine()->DestroyBody( _body );
    _body = body;
}

namespace definitions
{
    void OneShapeBaseDef::setShapeBox( float half_width, float half_height )
    {
        b2PolygonShape* s = new b2PolygonShape();
        s->SetAsBox( half_width, half_height );
        _shape.reset( s );
        _fixture_def.shape = s;
    }

    //void OneShapeBaseDef::setShapePolygon( b2Vec2* mas, size_t count )

    void OneShapeBaseDef::setShapeChain( b2Vec2* vertices, size_t count )
    {
        b2ChainShape* s = new b2ChainShape();
        s->CreateChain( vertices, count );
        _shape.reset( s );
        _fixture_def.shape = s;
    }

    void OneShapeBaseDef::setShapeEdge( b2Vec2 const& a, b2Vec2 const& b )
    {
        b2EdgeShape* s = new b2EdgeShape();
        s->Set( a, b );
        _shape.reset( s );
        _fixture_def.shape = s;
    }

    void OneShapeBaseDef::setShapeLoop( b2Vec2* vertices, size_t count )
    {
        b2ChainShape* s = new b2ChainShape();
        s->CreateLoop( vertices, count );
        _shape.reset( s );
        _fixture_def.shape = s;
    }

    namespace static_body
    {

        bool OneShapeDef::check()
        {
            return true;
        }

    }//end namespace static_body

    namespace dynamic_body
    {

        bool OneShapeDef::check()
        {
            return true;
        }

    }//end namespace dynamic_body

}//end namespace definitions
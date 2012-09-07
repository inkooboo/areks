#ifndef _AREKS_BODY_DEFINITIONS_HPP_
#define _AREKS_BODY_DEFINITIONS_HPP_

#include "defs.hpp"

namespace group
{
    enum
    {
        PLAYER = -1
    };
}

namespace filter
{
    enum
    {
		NONE = 0,
        
        PLATFORMS = 1,
		OBJECTS = 1 << 1,
		HEAD = 1 << 2,
		NECK = 1 << 3,
        
		ALL = 0xffff
    };
}

class BodyOwner
{
public:
    BodyOwner()
    {
    }

    BodyOwner( b2Body* body )
        : _body(body)
    {
    }

    BodyOwner( BodyOwner const& other )
        : _body( other._body )
    {
        other._body = 0;
    }

    BodyOwner& operator=( BodyOwner const& other )
    {
        _body = other._body;
        other._body = 0;
        return *this;
    }

    ~BodyOwner();

    void reset( b2Body* body );

    b2Body* get()
    {
        return _body;
    }

    b2Body* operator->()
    {
        return _body;
    }

    const b2Body* const operator->() const
    {
        return _body;
    }

private:
    mutable b2Body* _body;
};

namespace definitions
{
    class OneShapeBaseDef
    {
    public:
        inline virtual ~OneShapeBaseDef() = 0;

        void setPosition( b2Vec2 const& pos )
        {
            _body_def.position = pos;
        }

        void setAngle( float value )
        {
            _body_def.angle = value;
        }

        void setDensity( float value )
        {
            _fixture_def.density = value;
        }

        void setFriction( float value )
        {
            _fixture_def.friction = value;
        }

        void setRestitution( float value )
        {
            _fixture_def.restitution = value;
        }

        void setSensor( bool flag )
        {
            _fixture_def.isSensor = flag;
        }

        void setUserData( void* userData )
        {
            _body_def.userData = userData;
        }

        void setFilterGroup( int16 index )
        {
            _fixture_def.filter.groupIndex = index;
        }

		void setFilterMask( uint16 mask )
		{
			_fixture_def.filter.maskBits = mask;
		}

		void setFilterCategory( uint16 category )
		{
			_fixture_def.filter.categoryBits = category;
		}

        void setShapeBox( float half_width, float half_height );
        //void setShapePolygon( b2Vec2* mas, size_t count );
        void setShapeChain( b2Vec2* vertices, size_t count );
        void setShapeEdge( b2Vec2 const& a, b2Vec2 const& b );
        void setShapeLoop( b2Vec2* vertices, size_t count );

        virtual bool check() = 0;

        b2BodyDef* getBodyDef()
        {
            return &_body_def;
        }

        b2FixtureDef* getFixtureDef()
        {
            return &_fixture_def;
        }

    protected:
        std::unique_ptr<b2Shape> _shape; 
        b2BodyDef _body_def;
        b2FixtureDef _fixture_def;
    };
    
    inline OneShapeBaseDef::~OneShapeBaseDef() {}

    namespace static_body
    {

        class OneShapeDef : public OneShapeBaseDef
        {
        public:
            OneShapeDef()
            {
                _body_def.type = b2_staticBody;
            }

            void setDensity( float value )
            {
                assert( false && "Static body don't have mass!");
            }

            virtual bool check() override;
        };

    }//end namespace static_body

    namespace dynamic_body
    {

        class OneShapeDef : public OneShapeBaseDef
        {
        public:
            OneShapeDef()
            {
                _body_def.type = b2_dynamicBody;
            }

            virtual bool check() override;
        };

    }//end namespace dynamic_body

}//end namespace definitions

namespace defs = definitions;

namespace definitions
{
    namespace dyn = dynamic_body;
    namespace st = static_body;
}

#endif
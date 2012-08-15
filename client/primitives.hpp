#ifndef _AREKS_PRIMITIVES_HPP_
#define _AREKS_PRIMITIVES_HPP_

# include "defs.hpp"
# include <Box2D/Box2D.h>

# include "master.hpp"

namespace primitives
{
    float toPixel(float world);
    float toWorld(float pixel);
    
    class Vec2
    {
    public:
        float x;
        float y;

        Vec2()
            : x(0)
            , y(0)
        {}
        
        Vec2( cc::CCSize const& s )
            : x( toWorld( s.width ) )
            , y( toWorld( s.height) )
        {}
        
        Vec2( cc::CCPoint const& s )
            : x( toWorld( s.x ) )
            , y( toWorld( s.y) )
        {}
        
        Vec2( b2Vec2 const& v )
            : x( v.x )
            , y( v.y )
        {}

        Vec2( float x, float y )
            : x( x )
            , y( y )
        {}
        
        cc::CCSize toCCSize() const
        {
            return cc::CCSize(toPixel(x), toPixel(y));
        }

        cc::CCPoint toCCPoint() const
        {
            return cc::CCPoint(toPixel(x), toPixel(y));
        }
        
        b2Vec2 tob2Vec2() const
        {
            return b2Vec2(x, y);
        }
        
        Vec2 operator-() const
        {
            Vec2 v(-x, -y);
            return v;
        }
        
        void operator+=(const Vec2& v)
        {
            x += v.x;
            y += v.y;
        }
        
        void operator-=(const Vec2& v)
        {
            x -= v.x;
            y -= v.y;
        }
        
        void operator*=(float a)
        {
            x *= a;
            y *= a;
        }
        
};

}//end namespace primitives

namespace pr = primitives;

#endif
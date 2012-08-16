#ifndef _AREKS_PRIMITIVES_HPP_
#define _AREKS_PRIMITIVES_HPP_

# include "defs.hpp"
# include <Box2D/Box2D.h>

# include "master.hpp"

namespace primitives
{
    float worldToPixel(float world);
    float pixelToWorld(float pixel);
    
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
            : x( pixelToWorld( s.width ) )
            , y( pixelToWorld( s.height) )
        {}
        
        Vec2( cc::CCPoint const& s )
            : x( pixelToWorld( s.x ) )
            , y( pixelToWorld( s.y) )
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
            return cc::CCSize(worldToPixel(x), worldToPixel(y));
        }

        cc::CCPoint toCCPoint() const
        {
            return cc::CCPoint(worldToPixel(x), worldToPixel(y));
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
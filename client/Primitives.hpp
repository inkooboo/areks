#ifndef _AREKS_PRIMITIVES_HPP_
#define _AREKS_PRIMITIVES_HPP_

# include "defs.hpp"
# include <Box2D/Box2D.h>

#include "master.hpp"
#include "View.hpp"

namespace primitives
{
    inline float ConvertToMeter( float p );
    inline float ConvertToPixel( float m );

    class Pixel
    {
    public:
        explicit Pixel( float p ) :_p(p) {}
        float get() const { return _p; }
        void set( float p ) { _p=p; }
        float& value() { return _p;}

        float toMeter() { return ConvertToMeter(_p); }

    private:
        float _p;
    };

    class Meter
    {
    public:
        explicit Meter( float m ) :_m(m) {}
        float get() const { return _m; }
        void set( float m ) { _m=m; }
        float& value() { return _m;}

        float toPixel() { return ConvertToPixel(_m); }

    private:
        float _m;
    };

    inline float ConvertToMeter( float p )
    {
        return master_t::subsystem<View>().toWorld( p );            
    };

    inline float ConvertToPixel( float m )
    {
        return master_t::subsystem<View>().toPixel( m );            
    };    

    class Vec2
    {
    public:
        Vec2( cc::CCSize const& s )
            : _x( ConvertToMeter( s.width ) )
            , _y( ConvertToPixel( s.height) )
        {}
        Vec2( b2Vec2 const& v )
            : _x( v.x )
            , _y( v.y )
        {}

        Vec2( float x, float y )
            : _x( x )
            , _y( y )
        {}

        void setX( float x ) { _x = x; }
        void setY( float y ) { _y = y; }

        float getMeterX() const { return _x; }
        float getMeterY() const { return _y; }
        float getPixelX() const { return ConvertToPixel(_x); }
        float getPixelY() const { return ConvertToPixel(_y); }

        float& x() { return _x; }
        float& y() { return _y; }

    private:
        float _x;
        float _y;
    };    

}//end namespace primitives

namespace pr = primitives;

#endif
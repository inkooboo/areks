#ifndef _AREKS_PRIMITIVES_HPP_
#define _AREKS_PRIMITIVES_HPP_

# include "defs.hpp"
# include <Box2D/Box2D.h>

#include "master.hpp"
#include "View.hpp"

namespace primitives
{

    class Pixel
    {
    public:
        explicit Pixel( float p ) :_p(p) {}
        float Get() const { return _p; }
        void Set( float p ) { _p=p; }
        float& Value() { return _p;}
    private:
        float _p;
    };

    class Meter
    {
    public:
        explicit Meter( float m ) :_m(m) {}
        float Get() const { return _m; }
        void Set( float m ) { _m=m; }
        float& Value() { return _m;}
    private:
        float _m;
    };

    template <typename Ret>
    class ConvertTo;

    template <>
    class ConvertTo<Meter>
    {
    public:
        static Meter Result( Pixel p )
        {
            return Meter( master_t::subsystem<View>().toWorld( p.Get() ) );
        }
        static Meter Result( Meter m )
        {
            return m;
        }
    };

    template <>
    class ConvertTo<Pixel>
    {
    public:
        static Pixel Result( Pixel p )
        {
            return p;            
        }
        static Pixel Result( Meter m )
        {
            return Pixel( master_t::subsystem<View>().toPixel( m.Get() ) );            
        }
    };    

    template <typename Base>
    class BaseAntonym;

    template <>
    class BaseAntonym<Meter>
    {
    public:
        typedef Pixel Result;
    };
    template <>
    class BaseAntonym<Pixel>
    {
    public:
        typedef Meter Result;
    };


    template <typename Base>
    class Vec2
    {
    private:
        typedef typename BaseAntonym<Base>::Result Antonym;

    public:
        Vec2( cc::CCSize const& s )
            : _x( ConvertTo<Base>::Result( Pixel(s.width) ) )
            , _y( ConvertTo<Base>::Result( Pixel(s.height) ) )
        {}
        Vec2( b2Vec2 const& v )
            : _x( ConvertTo<Base>::Result( Meter(v.x) ) )
            , _y( ConvertTo<Base>::Result( Meter(v.y) ) )
        {}

        Vec2( Base x, Base y )
            : _x( x )
            , _y( y )
        {}

        Vec2( Antonym x, Antonym y )
            : _x( ConvertTo::Result<Base>(x) )
            , _y( ConvertTo::Result<Base>(y) )
        {}
        
        template <typename T>
        Vec2( Vec2<T> const& pOther )
            : _x( ConvertTo<Base>::Result( pOther.GetX() ) )
            , _y( ConvertTo<Base>::Result( pOther.GetY() ) )
        {}

        template <typename T>
        Vec2<Base>& operator=( Vec2<T> const& pOther )
        {
            _x = ConvertTo<Base>::Result( pOther.GetX() );
            _y = ConvertTo<Base>::Result( pOther.GetY() );
            return *this;
        }

        template <typename T>
        void SetX( T x );

        void SetX( Base x ) { _x = x; }
        void SetY( Base y ) { _y = y; }
        void SetX( Antonym x ) { _x = ConvertTo<Base>::Result(x); }
        void SetY( Antonym y ) { _y =  ConvertTo<Base>::Result(y); }

        Pixel GetPixelX() const { return ConvertTo<Pixel>::Result(_x); }
        Pixel GetPixelY() const { return ConvertTo<Pixel>::Result(_y); }
        Pixel GetMeterX() const { return ConvertTo<Meter>::Result(_x); }
        Pixel GetMeterY() const { return ConvertTo<Meter>::Result(_y); }

        Base& X() { return _x; }
        Base& Y() { return _y; }

        Base GetX() { return _x; }
        Base GetY() { return _y; }

    private:
        Base _x;
        Base _y;
    };

    template <typename T>
    inline Vec2<T> CreateVec2( T, T )
    {
        return Vec2<T>(T,T);
    }

    template <typename T, typename Base>
    inline Vec2<Base> CreateVec2( T );

    inline Vec2<Pixel> CreateVec2( cc::CCSize const& s )
    {
        return Vec2<Pixel>(s);
    }

    inline Vec2<Meter> CreateVec2( b2Vec2 const& v )
    {
        return Vec2<Meter>(v);
    }

}//end namespace primitives

#endif
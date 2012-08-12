#ifndef _AREKS_PRIMITIVES_HPP_
#define _AREKS_PRIMITIVES_HPP_

# include "defs.hpp"
# include <Box2D/Box2D.h>

class Vec2
{
public:
    Vec2( cc::CCSize const& s );
    Vec2( b2Vec2 const& v );
    Vec2( float x, float y );

    void SetX( float x );
    void SetY( float y );

    float GetX() const;
    float GetY() const;

    float GetPixelX() const;
    float GetPixelY() const;

    float& X();
    float& Y();

private:
    float _x;
    float _y;
};

#endif
//
//  primitives.cpp
//  areks
//
//  Created by inkooboo on 8/15/12.
//
//

#include "primitives.hpp"
#include "view.hpp"

#include <math.h>

namespace primitives
{

    float worldToPixel(float world)
    {
        return master_t::subsystem<View>().worldToPixel( world );
    }

    float pixelToWorld(float pixel)
    {
        return master_t::subsystem<View>().pixelToWorld( pixel );
    }

    Vec2& Vec2::absolutize()
    {
        x = fabs(x);
        y = fabs(y);
        return *this;
    }

    Vec2& Vec2::normalize()
    {
		float d = this->length();
        x /= d;
        y /= d;
        return *this;
    }

	float Vec2::length() const
	{
		return sqrt( x*x + y*y );
	}

    float distance( Vec2 const& a, Vec2 const& b )
    {
        return sqrt( pow( a.x-b.x, 2 ) + pow( a.y-b.y, 2 ) );
    }

    float angle( Vec2 const& a, Vec2 const& b )
    {
        float cos_v = (a.x*b.x + a.y*b.y) / sqrt(( a.x*a.x + a.y*a.y )*( b.x*b.x + b.y*b.y ));
        return acos( cos_v );

    }

    float angleAxisX( Vec2 const& v)
    {
        return atan2( v.y, v.x );
    }

}
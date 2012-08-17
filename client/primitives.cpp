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

}

float distance( pr::Vec2 const& a, pr::Vec2 const& b )
{
    return sqrt( pow( a.x-b.x, 2 ) + pow( a.y-b.y, 2 ) );
}
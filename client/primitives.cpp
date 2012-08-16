//
//  primitives.cpp
//  areks
//
//  Created by inkooboo on 8/15/12.
//
//

#include "primitives.hpp"
#include "view.hpp"

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

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

    float toPixel(float world)
    {
        return master_t::subsystem<View>().toPixel( world );
    }

    float toWorld(float pixel)
    {
        return master_t::subsystem<View>().toWorld( pixel );
    }

}

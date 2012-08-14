#ifndef _AREKS_OBJECT_PLATFORM_HPP_
#define _AREKS_OBJECT_PLATFORM_HPP_

#include "defs.hpp"
#include "ObjectInterfaces.hpp"

#include "Primitives.hpp"

namespace objects
{

    class Paltform : public StaticObject
    {
    public:
        static Platform* create(primitives::Vec2<Meter> const& coordinates, primitives::Vec2<Meter> const& size);
        
        virtual void draw() override;
        
    private:
        Platform();
    };
    
}//end namespace objects

#endif
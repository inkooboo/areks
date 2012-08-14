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
        template <typename T>
        static Platform* create(primitives::Vec2<T> const& coordinates, primitives::Vec2<T> const& size);
        
        virtual void Draw();
        
    private:
        Platform();
    };
    
}//end namespace objects

#endif
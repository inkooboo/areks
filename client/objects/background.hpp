//
//  backoground.hpp
//  areks
//
//  Created by inkooboo on 8/15/12.
//
//

#ifndef areks_backoground_hpp
#define areks_backoground_hpp

# include "base_object.hpp"
# include "primitives.hpp"

# include <string>

namespace objects
{
    class Background : public BaseObject
    {
    public:
        static Background* create(const std::string &file_name);
        
        virtual void draw() override;
        
    private:
        explicit Background(const std::string &file_name);
        ~Background();

        b2Body *_body;]
        cc::CCSprite *_sprite;
        pr::Vec2 _position;
    };
}

#endif

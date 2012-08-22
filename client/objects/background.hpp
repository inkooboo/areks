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
        static Background* create(const std::string &file_name_base, const std::string &file_name_lvl_1);
        
        virtual void draw() override;

        virtual b2Body* getBody() override;

        virtual void collide( BaseObject* other ) override;
        
    private:
        Background(const std::string &file_name_base, const std::string &file_name_lvl_1);
        ~Background();

        b2Body *_body;
        cc::CCSprite *_sprite_base;
        cc::CCSprite *_sprite_lvl_1;
    };
}

#endif

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
# include "body_definitions.hpp"

# include <json/value.h>
# include <string>

namespace objects
{
    class Background : public BaseObject
    {
    public:
        Background(const Json::Value &description);
        ~Background();
        
        virtual void draw() override;

        virtual b2Body* getBody() override;

        virtual void collide( BaseObject* other, b2Contact *contact ) override;
        
    private:
        BodyOwner _body;
        cc::CCSprite *_sprite_base;
        cc::CCSprite *_sprite_lvl_1;
    };
}

#endif

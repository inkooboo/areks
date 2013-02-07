#ifndef _AREKS_OBJECT_PLATFORM_HPP_
# define _AREKS_OBJECT_PLATFORM_HPP_

# include "defs.hpp"

# include "primitives.hpp"
# include "base_object.hpp"
# include "body_definitions.hpp"

# include <json/value.h>

# include <vector>

namespace objects
{

    class Platform : public BaseObject
    {
    public:
        Platform(const Json::Value &description);
        ~Platform();

        virtual void draw() override;

        virtual b2Body* getBody() override;
        
    private:
        BodyOwner _body;
        cc::CCNode* _ground_sprite;
		cc::CCSpriteBatchNode* _grass_sprites;
		std::vector<pr::Vec2> _grass_points;
		std::vector<float> _grass_angles;
		pr::Vec2 _center;
    };
    
}//end namespace objects

#endif
//
//  enemy.h
//  areks
//
//  Created by inkooboo on 8/23/12.
//
//

#ifndef __areks__enemy__
#define __areks__enemy__


# include "defs.hpp"

# include "primitives.hpp"
# include "object_interfaces.hpp"
# include "body_definitions.hpp"

namespace objects
{
    
    class Enemy : public DynamicObject
    {
    public:
        static Enemy * create(const pr::Vec2 &position);
        
        virtual void draw() override;
        
        virtual void updateState(float t) override;
        
        virtual b2Body* getBody() override;
        
    private:
        Enemy( pr::Vec2 const& position );
        ~Enemy();
        
        BodyOwner _body;
    };
    
}//end namespace objects


#endif /* defined(__areks__enemy__) */

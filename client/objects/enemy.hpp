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
# include "animation.hpp"

/// test arrow effect
#include "effects/arrow.hpp"
///

namespace objects
{
    
    class Enemy : public DynamicObject
    {
        enum State
        {
              STAY
            , MOVE_LEFT
            , MOVE_RIGHT
        };
        
    public:
        static Enemy * create(const pr::Vec2 &position);
        
        virtual void draw() override;
        
        virtual void updateState(float t) override;
        
        virtual b2Body* getBody() override;
        
        virtual pr::Vec2 getPosition() const override;
                
        void brain_xD();
        
    private:
        State m_state;
        
        Enemy( pr::Vec2 const& position );
        ~Enemy();
        
        BodyOwner _body;
        Animation m_animation;
        
        /// test arrow effect
        std::weak_ptr<effects::Arrow> m_arrow;
        ///
    };
    
}//end namespace objects


#endif /* defined(__areks__enemy__) */

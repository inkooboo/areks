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
# include "base_object.hpp"
# include "body_definitions.hpp"
# include "animation.hpp"

namespace objects
{
    
    class Enemy : public BaseObject
    {
        enum State
        {
              STAY
            , MOVE_LEFT
            , MOVE_RIGHT
            , HIT_LEFT
            , HIT_RIGHT
        };
        
    public:
        Enemy(const Json::Value &description);
        ~Enemy();

        virtual void draw() override;
        
        virtual void updateState(float t) override;
        
        virtual b2Body* getBody() override;
        
        virtual pr::Vec2 getPosition() const override;
                
        void brain_xD();
        
    private:
        State m_state;
        
        BodyOwner _body;
        Animation m_animation;
};
    
}//end namespace objects


#endif /* defined(__areks__enemy__) */

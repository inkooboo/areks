#ifndef _AREKS_PLAYER_HPP_
#define _AREKS_PLAYER_HPP_

#include "defs.hpp"
#include "subsystem.hpp"

#include "primitives.hpp"

#include "action_handler.hpp"
    
namespace objects
{

    namespace player
    {
        class Head;
        class Body;
    }//end namespace player
    
}//end namespace objects
    
class Player : public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;
    
public:
    Player();
    
    void createAvatar( pr::Vec2 const& position );
    
    bool isAvatarCreated() const;
    
    void shoot( pr::Vec2 const& point );

    float getNeckMaxLength() const;

    objects::player::Body* getBody();
    objects::player::Head* getHead();

public:
	void onTouchTarget(ActionHandler::TouchPtr &touch);
    
private:
    objects::player::Body* _body;
    objects::player::Head* _head;
    static const float _neck_max_lenght;
    
};

#endif
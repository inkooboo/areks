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
		class Neck2;
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

	void unhook();

    float getNeckMaxLength() const;

	void createNeck();
	void destroyNeck();

    void reloadPlayer();

    objects::player::Body* getBody();
    objects::player::Head* getHead();
	objects::player::Neck2* getNeck();

public:
	void onTouchTarget(ActionHandler::TouchPtr &touch);

	void onTouchBodyBegin(ActionHandler::TouchPtr &touch);
	void onTouchBodyMove(ActionHandler::TouchPtr &touch);
	void onTouchBodyEnd(ActionHandler::TouchPtr &touch);
    
private:
    void controlBodyBegin();
    void controlBodyEnd();

    objects::player::Body* _body;
    objects::player::Head* _head;
	objects::player::Neck2* _neck;
    static const float _neck_max_lenght;

	//for testing
	b2Body* _temp_body;
	b2Joint* _mouse_joint;
};

#endif
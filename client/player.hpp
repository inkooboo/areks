#ifndef _AREKS_PLAYER_HPP_
#define _AREKS_PLAYER_HPP_

#include "defs.hpp"
#include "subsystem.hpp"

#include "primitives.hpp"

#include "action_target.hpp"

#include <memory>

namespace objects
{

    namespace player
    {
        class Head;
        class Body;
		class Neck2;
    }//end namespace player
    
}//end namespace objects
    
class Player : public subsystem_t, public ActionTarget
{
    virtual void start() override;
    virtual void stop() override;

	virtual void onTargetTouch(action::TouchPtr &touch) override;
	virtual void onMoveTouchBegin(action::TouchPtr &touch) override;
	virtual void onMoveTouchContinue(action::TouchPtr &touch) override;
	virtual void onMoveTouchEnd(action::TouchPtr &touch) override;
    
public:
    Player();
    
    void createAvatar( pr::Vec2 const& position );
    
    bool isAvatarCreated() const;
    
    void shoot( pr::Vec2 const& point );

	void unhook();

    float getNeckMaxLength() const;

	void createNeck();
	void destroyNeck();

    void reload();

    std::shared_ptr<objects::player::Body> getBody();
    std::shared_ptr<objects::player::Head> getHead();
	std::shared_ptr<objects::player::Neck2> getNeck();
    
private:
    std::shared_ptr<objects::player::Body> _body;
    std::shared_ptr<objects::player::Head> _head;
	std::shared_ptr<objects::player::Neck2> _neck;
    static const float _neck_max_lenght;

	//for testing
	b2Body* _temp_body;
	b2Joint* _mouse_joint;
};

#endif
#include "player.hpp"

#include "objects/player/body.hpp"
#include "objects/player/head.hpp"
#include "objects/player/neck2.hpp"
#include "objects/player/neck.hpp"

#include "master.hpp"

#include "view.hpp"
#include "loop.hpp"


const float Player::_neck_max_lenght = 10.0;

//for testing
#include "physics.hpp"

void Player::start()
{
}

void Player::stop()
{
    _body = 0;
    _head = 0;
    _neck = 0;
}

void Player::reload()
{
    stop();
    start();
}

Player::Player()
    : _body(0)
    , _head(0)
	, _neck(0)

	, _mouse_joint(0)
{
}

void Player::createAvatar( pr::Vec2 const& position )
{
    _body = objects::player::Body::create( position );
    _head = objects::player::Head::create();
}

bool Player::isAvatarCreated() const
{
    return (_body) ? true : false;
}

void Player::shoot( pr::Vec2 const& point )
{
    assert( _head && "Head don't create!" );
    if( _head->getState() == objects::player::Head::REST )
    {
        _head->fly( point );
    }
}

void Player::unhook()
{
	destroyNeck();

	assert( _head && "Player head don't create!" );
	_head->return_home();
}

objects::player::Body* Player::getBody()
{
    assert(isAvatarCreated() && "Player avatar don't created!");
    return _body;
}

objects::player::Head* Player::getHead()
{
    assert( _head && "Player head don't exist!");
    return _head;
}

objects::player::Neck2* Player::getNeck()
{
    assert( _neck && "Player neck don't exist!");
    return _neck;
}

float Player::getNeckMaxLength() const
{
    return _neck_max_lenght;
}

void Player::createNeck()
{
	assert( !_neck && "Should not create more than one neck!" );
	_neck = objects::player::Neck2::create( _body->getPosition(), _body, _head->getPosition(), _head );
}

void Player::destroyNeck()
{
	assert( _neck && "Neck2 don't exist!" );
	_neck->destroy();
	_neck = 0;
}

void Player::onTouchTarget(ActionHandler::TouchPtr &touch)
{
	if( isAvatarCreated() )
	{
		View& view = master_t::subsystem<View>();
		shoot( view.toWorldCoordinates(touch->end) );
	}
}

void Player::onTouchBodyBegin(ActionHandler::TouchPtr &touch)
{
	if( _head->getState() == objects::player::Head::HOOK )
	{
        controlBodyBegin();
	}
}

void Player::onTouchBodyMove(ActionHandler::TouchPtr &touch)
{
	if(_mouse_joint)
	{
		pr::Vec2 touch_point = master_t::subsystem<View>().toWorldCoordinates(touch->to);

		float dis = pr::distance(_body->getPosition(), touch_point);
		if( dis > 1.f && dis < 5.f )
		{
			pr::Vec2 normal = _head->getPosition() - _body->getPosition();
			//normal.normalize();
			pr::Vec2 vector = touch_point - _body->getPosition();
			//vector.normalize();

			float angle = pr::angle( normal, vector );
			if( angle < b2_pi/18 ) // 10 degrees
			{
				_neck->shorten();
			}
			else if( angle > 17*b2_pi/18 ) // 170 degrees
			{
				_neck->extend();
			}
		}

		static_cast<b2MouseJoint*>(_mouse_joint)->SetTarget( touch_point.tob2Vec2() );
	}
}

void Player::onTouchBodyEnd(ActionHandler::TouchPtr &touch)
{
	if( _mouse_joint )
	{
        controlBodyEnd();
	}
}

void Player::controlBodyBegin()
{
 //   	b2BodyDef bd;
	//bd.type = b2_staticBody;
	//_temp_body = master_t::subsystem<Physics>().worldEngine()->CreateBody( &bd );
	//for testing
	b2BodyDef bd;
	_temp_body = master_t::subsystem<Physics>().worldEngine()->CreateBody( &bd );
    b2MouseJointDef mouse_def; 

	mouse_def.bodyA = _temp_body;
	mouse_def.bodyB = _body->getBody();
	mouse_def.target = _body->getPosition().tob2Vec2();
	mouse_def.maxForce = 5.f * _body->getBody()->GetMass();
	_mouse_joint = master_t::subsystem<Physics>().worldEngine()->CreateJoint( &mouse_def );
}

void Player::controlBodyEnd()
{
	master_t::subsystem<Physics>().worldEngine()->DestroyBody( _temp_body );
	_temp_body = 0;

	//mouse joint automatic delete with _temp_body
	_mouse_joint = 0;

	unhook();
}
    
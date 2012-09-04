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
	//for testing
	b2BodyDef bd;
	_temp_body = master_t::subsystem<Physics>().worldEngine()->CreateBody( &bd );
}

void Player::stop()
{
    _body = 0;
    _head = 0;
    _neck = 0;
}

void Player::reloadPlayer()
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
	View& view = master_t::subsystem<View>();
	shoot( view.toWorldCoordinates(touch->end) );
}

void Player::onTouchBodyBegin(ActionHandler::TouchPtr &touch)
{
	if( _head->getState() == objects::player::Head::HOOK )
	{
        master_t::subsystem<Loop>().executeOnce( std::bind(&Player::controlBodyBegin, this) );
	}
}

void Player::onTouchBodyMove(ActionHandler::TouchPtr &touch)
{
	if(_mouse_joint)
	{
		static_cast<b2MouseJoint*>(_mouse_joint)->SetTarget( master_t::subsystem<View>().toWorldCoordinates(touch->to).tob2Vec2() );
		static size_t t = 0;
		if( t == 33 )
		{
			_neck->shorten();
			t = 0;
		}
		else ++t;
	}
}

void Player::onTouchBodyEnd(ActionHandler::TouchPtr &touch)
{
	if( _mouse_joint )
	{
        master_t::subsystem<Loop>().executeOnce( std::bind(&Player::controlBodyEnd, this) );
	}
}

void Player::controlBodyBegin()
{
 //   	b2BodyDef bd;
	//bd.type = b2_staticBody;
	//_temp_body = master_t::subsystem<Physics>().worldEngine()->CreateBody( &bd );

    b2MouseJointDef mouse_def; 
	mouse_def.bodyA = _temp_body;
	mouse_def.bodyB = _body->getBody();
	mouse_def.target = _body->getPosition().tob2Vec2();
	mouse_def.maxForce = 5.f * _body->getBody()->GetMass();
	_mouse_joint = master_t::subsystem<Physics>().worldEngine()->CreateJoint( &mouse_def );
}

void Player::controlBodyEnd()
{
    master_t::subsystem<Physics>().worldEngine()->DestroyJoint( _mouse_joint );
	_mouse_joint = 0;
	unhook();
}
    
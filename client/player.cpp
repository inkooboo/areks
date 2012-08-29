#include "player.hpp"

#include "objects/player/body.hpp"
#include "objects/player/head.hpp"

#include "master.hpp"

#include "view.hpp"


const float Player::_neck_max_lenght = 10.0;

void Player::start()
{
}

void Player::stop()
{
}

Player::Player()
    : _body(0)
    , _head(0)
{
}

void Player::createAvatar( pr::Vec2 const& position )
{
    _body = objects::player::Body::create( position );
}

bool Player::isAvatarCreated() const
{
    return (_body) ? true : false;
}

void Player::shoot( pr::Vec2 const& point )
{
    _head = objects::player::Head::create( _body->getPosition() );
    _head->fly( point );
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

float Player::getNeckMaxLength() const
{
    return _neck_max_lenght;
}

void Player::onTouchTarget(ActionHandler::TouchPtr &touch)
{
	View& view = master_t::subsystem<View>();
	shoot( view.toWorldCoordinates(touch->end) );
}
    
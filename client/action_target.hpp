#ifndef _AREKS_ACTION_TARGET_HPP_
#define _AREKS_ACTION_TARGET_HPP_

#include "defs.hpp"

namespace action
{

	struct Touch;
	typedef std::shared_ptr<Touch> TouchPtr;
    
	struct Touch
	{
		Touch() : type(TARGET) { }

		cc::CCPoint begin;
		cc::CCPoint from;
		cc::CCPoint to;
		cc::CCPoint end;

		enum Type
		{
			TARGET,
			MOVE
		};

		Type type;
	};

}//end namespace action

	class ActionTarget
	{
	public:
		inline virtual ~ActionTarget() = 0;

		virtual void onTargetTouch(action::TouchPtr &touch) {};

		//NOT IMPLEMENT YET
		virtual bool onLongTouch(action::TouchPtr &touch) { return false; } //false - cancel long touch, use target touch instead

		virtual void onMoveTouchBegin(action::TouchPtr &touch) {};
		virtual void onMoveTouchContinue(action::TouchPtr &touch) {};
		virtual void onMoveTouchEnd(action::TouchPtr &touch) {};

		enum MultiType
		{
			SEPARATE,
			SHARING
		};

		virtual MultiType multi_touch_type() const { return SHARING; }

		virtual void onTwoTouchBegin(action::TouchPtr &touch1, action::TouchPtr &touch2) {};
		virtual void onTwoTouchContinue(action::TouchPtr &touch1, action::TouchPtr &touch2) {};
		virtual void onTwoTouchEnd(action::TouchPtr &touch1, action::TouchPtr &touch2) {};

	};

	inline ActionTarget::~ActionTarget() {}

#endif
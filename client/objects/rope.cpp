//#include "rope.hpp"
//
//#include "master.hpp"
//#include <math.h>
//
//#include "physics.hpp"
//
//namespace objects
//{
//    namespace detail
//    {
//
//        void RopePoint::setPos(float new_x, float new_y)
//        {
//            x = old_x = new_x;
//            y = old_y = new_y;
//        }
//
//        void RopePoint::update()
//        {
//            float temp_x = x;
//	        float temp_y = y;
//	        x += x - old_x;
//	        y += y - old_y;
//	        old_x = temp_x;
//            old_y = temp_y;
//        }
//
//        void RopePoint::applyGravity(float dt)
//        {
//            y -= 10.0f*dt;
//        }
//
//        RopeStick::RopeStick(RopePoint* a, RopePoint* b)
//            : point_a( a )
//            , point_b( b )
//        {
//            hypotenuse = sqrt( pow(point_b->x - point_a->x, 2) + pow(point_b->y - point_a->y, 2) );
//        }
//
//        void RopeStick::contract()
//        {
//            float dx = point_b->x - point_a->x;
//	        float dy = point_b->y - point_a->y;
//	        float h = sqrt( pow(dx, 2) + pow(dy, 2) );
//	        float diff = hypotenuse - h;
//	        float offx = (diff * dx / h) * 0.5;
//	        float offy = (diff * dy / h) * 0.5;
//	        point_a->x-=offx;
//	        point_a->y-=offy;
//	        point_b->x+=offx;
//	        point_b->y+=offy;
//        }
//
//    }//end namespace detail
//   
//    Rope* Rope::create( pr::Vec2 const& a_point, b2Body* a_body, pr::Vec2 const& b_point, b2Body* b_body )
//    {
//        return new Rope( a_point, a_body, b_point, b_body );
//    }
//
//    Rope::Rope( pr::Vec2 const& a_point, b2Body* a_body, pr::Vec2 const& b_point, b2Body* b_body )
//        : _a_point( a_point )
//        , _a_body( a_body )
//        , _b_point( b_point )
//        , _b_body( b_body )
//    {
//        //init physics
//        b2RopeJointDef ropeDef;
//        ropeDef.bodyA=a_body; //define bodies
//        ropeDef.bodyB=b_body;
//        ropeDef.localAnchorA = b2Vec2(0,0); //define anchors
//        ropeDef.localAnchorB = b2Vec2(0,0);
//        float dist = distance( a_point, b_point );
//        ropeDef.maxLength= dist;
//        master_t::subsystem<Physics>().worldEngine()->CreateJoint(&ropeDef); //create joint
//
//        //init view
//        dist = pr::worldToPixel( dist );
//	    int segmentFactor = 12; //increase value to have less segments per rope, decrease to have more segments
//	    _num_points = dist/segmentFactor;
//        pr::Vec2 diffVector = a_point - b_point;
//	    float multiplier = dist / (numPoints-1);
//	    _anti_sag_hack = 0.1f; //HACK: scale down rope points to cheat sag. set to 0 to disable, max suggested value 0.1
//	    for(int i=0;i<_num_points;i++) {
//		    CGPoint tmpVector = ccpAdd(pointA, ccpMult(ccpNormalize(diffVector),multiplier*i*(1-antiSagHack)));
//		    VPoint *tmpPoint = [[VPoint alloc] init];
//		    [tmpPoint setPos:tmpVector.x y:tmpVector.y];
//		    [vPoints addObject:tmpPoint];
//	    }
//	    for(int i=0;i<numPoints-1;i++) {
//		    VStick *tmpStick = [[VStick alloc] initWith:[vPoints objectAtIndex:i] pointb:[vPoints objectAtIndex:i+1]];
//		    [vSticks addObject:tmpStick];
//	    }
//	    if(spriteSheet!=nil) {
//		    for(int i=0;i<numPoints-1;i++) {
//			    VPoint *point1 = [[vSticks objectAtIndex:i] getPointA];
//			    VPoint *point2 = [[vSticks objectAtIndex:i] getPointB];
//			    CGPoint stickVector = ccpSub(ccp(point1.x,point1.y),ccp(point2.x,point2.y));
//			    float stickAngle = ccpToAngle(stickVector);
//			    CCSprite *tmpSprite = [CCSprite spriteWithBatchNode:spriteSheet rect:CGRectMake(0,0,multiplier,[[[spriteSheet textureAtlas] texture] pixelsHigh])];
//			    ccTexParams params = {GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
//			    [tmpSprite.texture setTexParameters:&params];
//			    [tmpSprite setPosition:ccpMidpoint(ccp(point1.x,point1.y),ccp(point2.x,point2.y))];
//			    [tmpSprite setRotation:-1 * CC_RADIANS_TO_DEGREES(stickAngle)];
//			    [spriteSheet addChild:tmpSprite];
//			    [ropeSprites addObject:tmpSprite];
//		    }
//	    }
//    }
//
//    void Rope::draw()
//    {
//    }
//
//    void updateState( float t )
//    {
//    }
//
//    Rope::~Rope()
//    {
//    }
//
//    void Rope::reset()
//    {
//    }
//
//}//end namespace objects
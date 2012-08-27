//
//  animation.cpp
//  areks
//
//  Created by inkooboo on 8/24/12.
//
//

#include "animation.hpp"
#include "resource_utils.hpp"

#include <json/json.h>

Animation::Animation(const char *name, cc::CCNode *node)
    : m_node(node)
{
    std::string base_path = res::animation_base_path(name);
    
    std::string description_str = res::load_file_content(base_path + name + ".json");
    Json::Reader parser;
    Json::Value description;
    parser.parse(description_str, description);
    
    
    
    auto action_names = description.getMemberNames();
    for (auto it = action_names.begin(); it != action_names.end(); ++it)
    {
        const Json::Value &cur = description[*it];
        assert(cur.isObject());
        
        float interval = cur["interbal"].asFloat();
        
        const Json::Value &frames = cur["frames"];
        assert(cur.isArray());
        
        cc::CCArray* animFrames = cc::CCArray::create(frames.size());
        for (int i = 0; i < frames.size(); ++i)
        {
            std::string frame = frames[i].asString();
            
            std::string frame_path = res::picture((base_path + frame).c_str());
            
            cc::CCTexture2D *texture = cc::CCTextureCache::sharedTextureCache()->addImage(frame_path.c_str());
            
            cc::CCSpriteFrame *sprite_frame = cc::CCSpriteFrame::create(texture, cc::CCRect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
            
            animFrames->addObject(sprite_frame);
        }

//        CCAnimation *animation = CCAnimation::create(animFrames, 0.2f);
//        CCAnimate *animate = CCAnimate::create(animation);
//        CCActionInterval* seq = (CCActionInterval*)(CCSequence::create( animate,
//                                                                       CCFlipX::create(true),
//                                                                       animate->copy()->autorelease(),
//                                                                       CCFlipX::create(false),
//                                                                       NULL) );
//        
//        sprite->runAction(CCRepeatForever::create( seq ) );

    }
    
}


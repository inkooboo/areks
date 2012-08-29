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

cc::CCSprite * Animation::sprite()
{
    return m_sprite;
}


Animation::Animation(const char *name)
    : m_sprite(0)
{
    std::string base_path = res::animation_base_path(name);
    
    std::string description_str = res::load_file_content(base_path + name + ".json");
    Json::Reader parser;
    Json::Value description;
    parser.parse(description_str, description);
    
    auto action_names = description.getMemberNames();
    for (auto it = action_names.begin(); it != action_names.end(); ++it)
    {
        std::string cur_name = *it;
        const Json::Value &cur = description[cur_name];
        assert(cur.isObject());
        
        float interval = cur["interval"].asFloat();
        
        const Json::Value &frames = cur["frames"];
        assert(cur.isArray());
        
        cc::CCArray *anim_frames = cc::CCArray::create(frames.size());
        for (int i = 0; i < frames.size(); ++i)
        {
            std::string frame = frames[i].asString();
            
            std::string frame_path = res::picture((base_path + frame).c_str());
            
            cc::CCTexture2D *texture = cc::CCTextureCache::sharedTextureCache()->addImage(frame_path.c_str());
            
            cc::CCSpriteFrame *sprite_frame = cc::CCSpriteFrame::create(texture, cc::CCRect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
            
            if (!m_sprite)
            {
                m_sprite = cc::CCSprite::create(sprite_frame);
            }
            
            anim_frames->addObject(sprite_frame);
        }

        cc::CCAnimation *animation = cc::CCAnimation::create(anim_frames, interval);
        cc::CCAnimate *animate = cc::CCAnimate::create(animation);
        cc::CCActionInterval* seq = (cc::CCActionInterval *)(cc::CCSequence::create( animate,
                                                                       cc::CCFlipX::create(true),
                                                                       animate->copy()->autorelease(),
                                                                       cc::CCFlipX::create(false),
                                                                       NULL) );
        
        m_sprite->runAction(cc::CCRepeatForever::create( seq ) );
        
        break; //TEMP for testing one animation
    }
    
}


//
//  animation.cpp
//  areks
//
//  Created by inkooboo on 8/24/12.
//
//

#include "animation.hpp"
#include "resource_utils.hpp"

#include "master.hpp"
#include <json/json.h>

cc::CCSprite * Animation::sprite()
{
    return m_sprite;
}


Animation::Animation(const char *name)
    : m_sprite(0)
    , m_cur_action(0)
{
    std::string base_path = res::animation_base_path(name);
    
    std::string description_str = res::load_file_content(base_path + name + ".json");
    Json::Reader parser;
    parser.parse(description_str, m_descr);
    
    auto action_names = m_descr.getMemberNames();
    for (auto it = action_names.begin(); it != action_names.end(); ++it)
    {
        std::string cur_name = *it;
        const Json::Value &cur = m_descr[cur_name];
        assert(cur.isObject());
        
        float interval = cur["interval"].asFloat();
        
        const Json::Value &frames = cur["frames"];
        assert(frames.isArray());
        
        cc::CCArray *anim_frames = cc::CCArray::create(frames.size());
        for (unsigned int i = 0; i < frames.size(); ++i)
        {
            std::string frame = frames[i].asString();
            
            std::string frame_path = res::animation_frame((base_path + frame).c_str());
            
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
                                                                       animate->copy()->autorelease(),
                                                                       NULL) );

        seq->retain();
        m_animations[cur_name] = seq;
    }
    
}

Animation::~Animation()
{
    for (auto it = m_animations.begin(); it != m_animations.end(); ++it)
    {
        it->second->release();
    }
}

void Animation::animate(const std::string &name, LazyFunction on_animation_loop_end)
{
    auto find = m_animations.find(name);
    if (find != m_animations.end())
    {
        if (m_cur_action)
        {
            m_sprite->stopAction(m_cur_action);
        }
        m_cur_action = cc::CCRepeatForever::create( find->second );
        m_sprite->runAction(m_cur_action);
        
        float delay = m_descr[name]["interval"].asFloat() * m_descr[name]["frames"].size();
        
        master_t::subsystem<Loop>().schedule(on_animation_loop_end, delay);
    }
}

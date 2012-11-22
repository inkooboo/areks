#ifndef _AREKS_VIEW_HPP_
#define _AREKS_VIEW_HPP_

# include "defs.hpp"
# include "subsystem.hpp"
# include "primitives.hpp"

class View : public subsystem_t
{
protected:
    virtual void start() override;
    virtual void stop() override;
    
public:
    View();
    ~View();

    cc::CCScene * scene();

    void reload(cc::CCSize bg_size, pr::Vec2 world_size);
    
    float pixelScale() const;
    cc::CCPoint toScreenCoordinates(pr::Vec2 world_coord) const;
    pr::Vec2 toWorldCoordinates(cc::CCPoint screen_coord) const;
    float worldToPixel(float world_size) const;
    float pixelToScreen(float pixel_size) const;
    float screenToPixel(float screen_size) const;
    float pixelToWorld(float pixel_size) const;
    cc::CCLayer * gameLayer();
    
    void moveViewBy(float dx, float dy);
    void moveViewToPosition(const pr::Vec2 &position);
    
    virtual void manageCameraPositionAndScale(float t) {}
    
    pr::Vec2 currentCameraPosition() const;

    void addSprite(cc::CCNode *sprite, int z_order = 0);
    void removeSprite(cc::CCNode *sprite);
    void drawSpriteHelper(cc::CCNode *sprite, pr::Vec2 position, float angle);

protected:
    void createGameLayerMenu(cc::CCArray* pArrayOfItems);

    void validateScale();
    void validatePosition();
    
    cc::CCScene *m_scene;
    cc::CCLayer *m_game_layer;
    
    cc::CCSize m_size;
    
    float m_view_scale;
    float m_min_view_scale;
    float m_max_view_scale;
    float m_default_view_scale;
    float m_world_scale;
    
    pr::Vec2 m_half_screen_in_world_size;
    pr::Vec2 m_cur_positon;
};

#endif

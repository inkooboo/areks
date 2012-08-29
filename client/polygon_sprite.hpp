#ifndef _AREKS_POLYGON_SPRITE_HPP_
#define _AREKS_POLYGON_SPRITE_HPP_

#include "defs.hpp"
#include "primitives.hpp"

class PolygonSprite : public cc::CCNode, public cc::CCTextureProtocol, public cc::CCRGBAProtocol
{
    /** Opacity: conforms to CCRGBAProtocol protocol */
    CC_PROPERTY(GLubyte, m_nOpacity, Opacity)
    /** Color: conforms with CCRGBAProtocol protocol */
    CC_PROPERTY_PASS_BY_REF(cc::ccColor3B, m_sColor, Color);
public:
    virtual void draw(void);

public:
    // attributes

    /** returns whether or not the texture rectangle is rotated */
    inline bool isTextureRectRotated(void) { return m_bRectRotated; }

    /** returns the rect of the CCSprite in points */
    inline const cc::CCRect& getTextureRect(void) { return m_obRect; }

    /** conforms to CCTextureProtocol protocol */
    inline cc::ccBlendFunc getBlendFunc(void) { return m_sBlendFunc; }
    /** conforms to CCTextureProtocol protocol */
    inline void setBlendFunc(cc::ccBlendFunc blendFunc) { m_sBlendFunc = blendFunc; }

public:
	static PolygonSprite* create(cc::CCTexture2D *pTexture, std::vector<pr::Vec2> const& vertices);
	static PolygonSprite* create(cc::CCTexture2D *pTexture, std::vector<pr::Vec2> const& triangles, cc::CCRect const& rect);

public:
    PolygonSprite();
    virtual ~PolygonSprite(void);
    virtual bool init(cc::CCTexture2D *pTexture, std::vector<cc::ccVertex3F>* triangles, cc::CCRect const& rect);

    //virtual void removeChild(CCNode* pChild, bool bCleanup);
    //virtual void removeAllChildrenWithCleanup(bool bCleanup);
    //virtual void reorderChild(CCNode *pChild, int zOrder);
    //virtual void addChild(CCNode *pChild);
    //virtual void addChild(CCNode *pChild, int zOrder);
    //virtual void addChild(CCNode *pChild, int zOrder, int tag);
    //virtual void sortAllChildren();

    virtual void ignoreAnchorPointForPosition(bool value);
    void setFlipX(bool bFlipX);
    void setFlipY(bool bFlipY);
    /** whether or not the sprite is flipped horizontally. 
    It only flips the texture of the sprite, and not the texture of the sprite's children.
    Also, flipping the texture doesn't alter the anchorPoint.
    If you want to flip the anchorPoint too, and/or to flip the children too use:

    sprite->setScaleX(sprite->getScaleX() * -1);
    */
    bool isFlipX(void);
    /** whether or not the sprite is flipped vertically.
    It only flips the texture of the sprite, and not the texture of the sprite's children.
    Also, flipping the texture doesn't alter the anchorPoint.
    If you want to flip the anchorPoint too, and/or to flip the children too use:

    sprite->setScaleY(sprite->getScaleY() * -1);
    */
    bool isFlipY(void);

    void updateColor(void);
    // RGBAProtocol
    /** opacity: conforms to CCRGBAProtocol protocol */
    virtual void setOpacityModifyRGB(bool bValue);
    virtual bool isOpacityModifyRGB(void);

    // CCTextureProtocol
    virtual void setTexture(cc::CCTexture2D *texture);
    virtual cc::CCTexture2D* getTexture(void);

    /** updates the texture rect of the CCSprite in points. 
    It will call setTextureRect:rotated:untrimmedSize with rotated = NO, and utrimmedSize = rect.size.
    */
     virtual void setTextureRect(const cc::CCRect& rect);

     /** set the texture rect, rectRotated and untrimmed size of the CCSprite in points.
     It will update the texture coordinates and the vertex rectangle.
     */
     virtual void setTextureRect(const cc::CCRect& rect, bool rotated, const cc::CCSize& untrimmedSize);

    /** set the vertex rect.
     It will be called internally by setTextureRect. Useful if you want to create 2x images from SD images in Retina Display.
     Do not call it manually. Use setTextureRect instead.
     */
     virtual void setVertexRect(const cc::CCRect& rect);

    // Animation

    /** changes the display frame with animation name and index.
    The animation name will be get from the CCAnimationCache
    @since v0.99.5
    */
    //virtual void setDisplayFrameWithAnimationName(const char *animationName, int frameIndex);

protected:
    virtual void setTextureCoords(cc::CCRect rect);
    virtual void updateBlendFunc(void);

protected:
    //
    // Data used when the sprite is rendered using a CCSpriteSheet
    //
    //bool                m_bHasChildren;            // optimization to check if it contain children
    bool                m_bShouldBeHidden;        // should not be drawn because one of the ancestors is not visible
    
    cc::ccBlendFunc        m_sBlendFunc;    // Needed for the texture protocol
    cc::CCTexture2D*       m_pobTexture;// Texture used to render the sprite

    //
    // Shared data
    //

    // texture
    cc::CCRect m_obRect;
    bool   m_bRectRotated;

    // vertex coords, texture coords and color info
	std::vector<cc::ccVertex3F> m_triangles;
	std::vector<cc::ccTex2F> m_tex_coords;

    // opacity and RGB protocol
    cc::ccColor3B m_sColorUnmodified;
    bool m_bOpacityModifyRGB;

    // image is flipped
    bool m_bFlipX;
    bool m_bFlipY;
};

#endif

#include "polygon_sprite.hpp"

#include "triangulator.hpp"

PolygonSprite* PolygonSprite::create(cc::CCTexture2D *pTexture, std::vector<pr::Vec2> const& vertices)
{
	cc::CCRect rect;
	{
		pr::Vec2 lower_bound = vertices[0], upper_bound = vertices[0];
		auto it = vertices.begin();
		auto end = vertices.end();
		for( ; it != end; ++it )
		{
			lower_bound.x = std::min(it->x, lower_bound.x);
			lower_bound.y = std::min(it->y, lower_bound.y);
			upper_bound.x = std::max(it->x, upper_bound.x);
			upper_bound.y = std::max(it->y, upper_bound.y);
		}
		pr::Vec2 diff = upper_bound - lower_bound;
		float width = diff.toCCPoint().x;
		float height = diff.toCCPoint().y;
		//rect.setRect( (lower_bound.x+upper_bound.x)/2, (lower_bound.y+upper_bound.y)/2, width, height );
		rect.setRect( lower_bound.toCCPoint().x, lower_bound.toCCPoint().y, width, height );
	}

	Vector2dVector output;
    Triangulate::Process( vertices, output );

	return PolygonSprite::create( pTexture, output, rect );
}

PolygonSprite* PolygonSprite::create(cc::CCTexture2D *pTexture, std::vector<pr::Vec2> const& triangles, cc::CCRect const& rect)
{
	std::vector<cc::ccVertex3F> cc_triangles;
	
	for( size_t i=0; i<triangles.size(); ++i )
    {
		cc::CCPoint p = triangles[i].toCCPoint();
		cc::ccVertex3F v = { p.x - rect.origin.x , p.y - rect.origin.y, 0 };
        cc_triangles.push_back( v );
    }

	PolygonSprite *sprite = new PolygonSprite();

	if (sprite && sprite->init(pTexture, &cc_triangles, rect))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

// designated initializer
bool PolygonSprite::init(cc::CCTexture2D *pTexture, std::vector<cc::ccVertex3F>* triangles, cc::CCRect const& rect)
{
	m_triangles.swap( *triangles );

    // shader program
    setShaderProgram(cc::CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture));

    m_bOpacityModifyRGB = true;
    m_nOpacity = 255;
    m_sColor = m_sColorUnmodified = cc::ccWHITE;

    m_sBlendFunc.src = CC_BLEND_SRC;
    m_sBlendFunc.dst = CC_BLEND_DST;

    m_bFlipX = m_bFlipY = false;

    // default transform anchor: center
    setAnchorPoint(ccp(0.5f, 0.5f));

	//don't did childrens yet
    //m_bHasChildren = false;

    // update texture (calls updateBlendFunc)
    setTexture(pTexture);
	bool rotated = false;
    setTextureRect(rect, rotated, rect.size);

    return true;
}

PolygonSprite::PolygonSprite()
: m_pobTexture(NULL)
, m_bShouldBeHidden(false)
{
}

PolygonSprite::~PolygonSprite(void)
{
    CC_SAFE_RELEASE(m_pobTexture);
}

void PolygonSprite::setTextureRect(const cc::CCRect& rect)
{
    setTextureRect(rect, false, rect.size);
}


void PolygonSprite::setTextureRect(const cc::CCRect& rect, bool rotated, const cc::CCSize& untrimmedSize)
{
    m_bRectRotated = rotated;

    setContentSize(untrimmedSize);
    setVertexRect(rect);
    setTextureCoords(rect);
}

void PolygonSprite::setVertexRect(const cc::CCRect& rect)
{
    m_obRect = rect;
}

void PolygonSprite::setTextureCoords(cc::CCRect rect)
{
    float atlasWidth = (float)m_pobTexture->getPixelsWide();
    float atlasHeight = (float)m_pobTexture->getPixelsHigh();

	for( auto it = m_triangles.begin(), end = m_triangles.end(); it!=end; ++it )
	{
		using namespace cc;

        cc::ccTex2F tex_coord;

		tex_coord.u = it->x / atlasWidth;
		tex_coord.v = it->y / atlasHeight;

		m_tex_coords.push_back( tex_coord );
	}

//    float left, right, top, bottom;
//
//    if (m_bRectRotated)
//    {
//#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
//        left    = (2*rect.origin.x+1)/(2*atlasWidth);
//        right    = left+(rect.size.height*2-2)/(2*atlasWidth);
//        top        = (2*rect.origin.y+1)/(2*atlasHeight);
//        bottom    = top+(rect.size.width*2-2)/(2*atlasHeight);
//#else
//        left    = rect.origin.x/atlasWidth;
//        right    = (rect.origin.x+rect.size.height) / atlasWidth;
//        top        = rect.origin.y/atlasHeight;
//        bottom    = (rect.origin.y+rect.size.width) / atlasHeight;
//#endif // CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
//
//        if (m_bFlipX)
//        {
//            CC_SWAP(top, bottom, float);
//        }
//
//        if (m_bFlipY)
//        {
//            CC_SWAP(left, right, float);
//        }
//
//        m_sQuad.bl.texCoords.u = left;
//        m_sQuad.bl.texCoords.v = top;
//        m_sQuad.br.texCoords.u = left;
//        m_sQuad.br.texCoords.v = bottom;
//        m_sQuad.tl.texCoords.u = right;
//        m_sQuad.tl.texCoords.v = top;
//        m_sQuad.tr.texCoords.u = right;
//        m_sQuad.tr.texCoords.v = bottom;
//    }
//    else
//    {
//#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
//        left    = (2*rect.origin.x+1)/(2*atlasWidth);
//        right    = left + (rect.size.width*2-2)/(2*atlasWidth);
//        top        = (2*rect.origin.y+1)/(2*atlasHeight);
//        bottom    = top + (rect.size.height*2-2)/(2*atlasHeight);
//#else
//        left    = rect.origin.x/atlasWidth;
//        right    = (rect.origin.x + rect.size.width) / atlasWidth;
//        top        = rect.origin.y/atlasHeight;
//        bottom    = (rect.origin.y + rect.size.height) / atlasHeight;
//#endif // ! CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
//
//        if(m_bFlipX)
//        {
//            CC_SWAP(left,right,float);
//        }
//
//        if(m_bFlipY)
//        {
//            CC_SWAP(top,bottom,float);
//        }
//
//        m_sQuad.bl.texCoords.u = left;
//        m_sQuad.bl.texCoords.v = bottom;
//        m_sQuad.br.texCoords.u = right;
//        m_sQuad.br.texCoords.v = bottom;
//        m_sQuad.tl.texCoords.u = left;
//        m_sQuad.tl.texCoords.v = top;
//        m_sQuad.tr.texCoords.u = right;
//        m_sQuad.tr.texCoords.v = top;
//    }
}

// draw

void PolygonSprite::draw(void)
{
	using namespace cc;

	CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "PolygonSprite - draw");

	CC_NODE_DRAW_SETUP();

	ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );

	if (m_pobTexture != NULL)
	{
		ccGLBindTexture2D( m_pobTexture->getName() );
	}
	else
	{
		ccGLBindTexture2D(0);
	}
    
	//
	// Attributes
	//

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords );

	// vertex
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, 0, (void*) ( m_triangles.data() ));

	// texCoods
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, (void*)(m_tex_coords.data() ));

	// color
	//glColor4b(m_sColor.r, m_sColor.g, m_sColor.b, m_nOpacity);

    glDrawArrays( GL_TRIANGLES, 0, m_triangles.size() );

	CHECK_GL_ERROR_DEBUG();

	CC_INCREMENT_GL_DRAWS(1);

	CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "PolygonSprite - draw");



//
//    CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
//
//    CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");
//
//    CC_NODE_DRAW_SETUP();
//
//    ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );
//
//    if (m_pobTexture != NULL)
//    {
//        ccGLBindTexture2D( m_pobTexture->getName() );
//    }
//    else
//    {
//        ccGLBindTexture2D(0);
//    }
//    
//    //
//    // Attributes
//    //
//
//    ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
//
//#define kQuadSize sizeof(m_sQuad.bl)
//    long offset = (long)&m_sQuad;
//
//    // vertex
//    int diff = offsetof( ccV3F_C4B_T2F, vertices);
//    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
//
//    // texCoods
//    diff = offsetof( ccV3F_C4B_T2F, texCoords);
//    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
//
//    // color
//    diff = offsetof( ccV3F_C4B_T2F, colors);
//    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
//
//
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//
//    CHECK_GL_ERROR_DEBUG();
//
//
//#if CC_SPRITE_DEBUG_DRAW == 1
//    // draw bounding box
//    CCPoint vertices[4]={
//        ccp(m_sQuad.tl.vertices.x,m_sQuad.tl.vertices.y),
//        ccp(m_sQuad.bl.vertices.x,m_sQuad.bl.vertices.y),
//        ccp(m_sQuad.br.vertices.x,m_sQuad.br.vertices.y),
//        ccp(m_sQuad.tr.vertices.x,m_sQuad.tr.vertices.y),
//    };
//    ccDrawPoly(vertices, 4, true);
//#elif CC_SPRITE_DEBUG_DRAW == 2
//    // draw texture box
//    CCSize s = this->getTextureRect().size;
//    CCPoint offsetPix = this->getOffsetPosition();
//    CCPoint vertices[4] = {
//        ccp(offsetPix.x,offsetPix.y), ccp(offsetPix.x+s.width,offsetPix.y),
//        ccp(offsetPix.x+s.width,offsetPix.y+s.height), ccp(offsetPix.x,offsetPix.y+s.height)
//    };
//    ccDrawPoly(vertices, 4, true);
//#endif // CC_SPRITE_DEBUG_DRAW
//
//    CC_INCREMENT_GL_DRAWS(1);
//
//    CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
}






//// CCNode overrides
//
//void CCSprite::addChild(CCNode* pChild)
//{
//    CCNode::addChild(pChild);
//}
//
//void CCSprite::addChild(CCNode *pChild, int zOrder)
//{
//    CCNode::addChild(pChild, zOrder);
//}
//
//void CCSprite::addChild(CCNode *pChild, int zOrder, int tag)
//{
//    CCAssert(pChild != NULL, "Argument must be non-NULL");
//
//    if (m_pobBatchNode)
//    {
//        CCSprite* pChildSprite = dynamic_cast<CCSprite*>(pChild);
//        CCAssert( pChildSprite, "CCSprite only supports CCSprites as children when using CCSpriteBatchNode");
//        CCAssert(pChildSprite->getTexture()->getName() == m_pobTextureAtlas->getTexture()->getName(), "");
//        //put it in descendants array of batch node
//        m_pobBatchNode->appendChild(pChildSprite);
//
//        if (!m_bReorderChildDirty)
//        {
//            setReorderChildDirtyRecursively();
//        }
//    }
//    //CCNode already sets isReorderChildDirty_ so this needs to be after batchNode check
//    CCNode::addChild(pChild, zOrder, tag);
//    m_bHasChildren = true;
//}
//
//void CCSprite::reorderChild(CCNode *pChild, int zOrder)
//{
//    CCAssert(pChild != NULL, "");
//    CCAssert(m_pChildren->containsObject(pChild), "");
//
//    if (zOrder == pChild->getZOrder())
//    {
//        return;
//    }
//
//    if( m_pobBatchNode && ! m_bReorderChildDirty)
//    {
//        setReorderChildDirtyRecursively();
//        m_pobBatchNode->reorderBatch(true);
//    }
//
//    CCNode::reorderChild(pChild, zOrder);
//}
//
//void CCSprite::removeChild(CCNode *pChild, bool bCleanup)
//{
//    if (m_pobBatchNode)
//    {
//        m_pobBatchNode->removeSpriteFromAtlas((CCSprite*)(pChild));
//    }
//
//    CCNode::removeChild(pChild, bCleanup);
//    
//}
//
//void CCSprite::removeAllChildrenWithCleanup(bool bCleanup)
//{
//    if (m_pobBatchNode)
//    {
//        CCObject* pObject = NULL;
//        CCARRAY_FOREACH(m_pChildren, pObject)
//        {
//            CCSprite* pChild = dynamic_cast<CCSprite*>(pObject);
//            if (pChild)
//            {
//                m_pobBatchNode->removeSpriteFromAtlas(pChild);
//            }
//        }
//    }
//
//    CCNode::removeAllChildrenWithCleanup(bCleanup);
//    
//    m_bHasChildren = false;
//}
//
//void CCSprite::sortAllChildren()
//{
//    if (m_bReorderChildDirty)
//    {
//        int i = 0,j = 0,length = m_pChildren->data->num;
//        CCNode** x = (CCNode**)m_pChildren->data->arr;
//        CCNode *tempItem = NULL;
//
//        // insertion sort
//        for(i=1; i<length; i++)
//        {
//            tempItem = x[i];
//            j = i-1;
//
//            //continue moving element downwards while zOrder is smaller or when zOrder is the same but orderOfArrival is smaller
//            while(j>=0 && ( tempItem->getZOrder() < x[j]->getZOrder() || ( tempItem->getZOrder() == x[j]->getZOrder() && tempItem->getOrderOfArrival() < x[j]->getOrderOfArrival() ) ) )
//            {
//                x[j+1] = x[j];
//                j = j-1;
//            }
//            x[j+1] = tempItem;
//        }
//
//        if ( m_pobBatchNode)
//        {
//            arrayMakeObjectsPerformSelector(m_pChildren, sortAllChildren, CCSprite*);
//        }
//
//        m_bReorderChildDirty = false;
//    }
//}


void PolygonSprite::ignoreAnchorPointForPosition(bool value)
{
    assert(false && "ignoreAnchorPointForPosition is invalid in CCSprite");
    //CCNode::ignoreAnchorPointForPosition(value);
}

void PolygonSprite::setFlipX(bool bFlipX)
{
	assert( false && "PolygonSprite::setFlipX don't did yet!");
    if (m_bFlipX != bFlipX)
    {
        m_bFlipX = bFlipX;
        setTextureRect(m_obRect, m_bRectRotated, m_tContentSize);
    }
}

bool PolygonSprite::isFlipX(void)
{
    return m_bFlipX;
}

void PolygonSprite::setFlipY(bool bFlipY)
{
	assert( false && "PolygonSprite::setFlipY don't did yet!");
    if (m_bFlipY != bFlipY)
    {
        m_bFlipY = bFlipY;
        setTextureRect(m_obRect, m_bRectRotated, m_tContentSize);
    }
}

bool PolygonSprite::isFlipY(void)
{
    return m_bFlipY;
}

//
// RGBA protocol
//

void PolygonSprite::updateColor(void)
{
	//do nothing
}

GLubyte PolygonSprite::getOpacity(void)
{
    return m_nOpacity;
}

void PolygonSprite::setOpacity(GLubyte opacity)
{
    m_nOpacity = opacity;

    // special opacity for premultiplied textures
    if (m_bOpacityModifyRGB)
    {
        setColor(m_sColorUnmodified);
    }

    updateColor();
}

const cc::ccColor3B& PolygonSprite::getColor(void)
{
    if (m_bOpacityModifyRGB)
    {
        return m_sColorUnmodified;
    }

    return m_sColor;
}

void PolygonSprite::setColor(const cc::ccColor3B& color3)
{
    m_sColor = m_sColorUnmodified = color3;

    if (m_bOpacityModifyRGB)
    {
        m_sColor.r = color3.r * m_nOpacity/255.0f;
        m_sColor.g = color3.g * m_nOpacity/255.0f;
        m_sColor.b = color3.b * m_nOpacity/255.0f;
    }

    updateColor();
}

void PolygonSprite::setOpacityModifyRGB(bool bValue)
{
    cc::ccColor3B oldColor = m_sColor;
    m_bOpacityModifyRGB = bValue;
    m_sColor = oldColor;
}

bool PolygonSprite::isOpacityModifyRGB(void)
{
    return m_bOpacityModifyRGB;
}

// Texture protocol

void PolygonSprite::updateBlendFunc(void)
{
    // it is possible to have an untextured sprite
    if (! m_pobTexture || ! m_pobTexture->hasPremultipliedAlpha())
    {
        m_sBlendFunc.src = GL_SRC_ALPHA;
        m_sBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
        setOpacityModifyRGB(false);
    }
    else
    {
        m_sBlendFunc.src = CC_BLEND_SRC;
        m_sBlendFunc.dst = CC_BLEND_DST;
        setOpacityModifyRGB(true);
    }
}

void PolygonSprite::setTexture(cc::CCTexture2D *texture)
{
    // accept texture==nil as argument
    assert( (!texture || dynamic_cast<cc::CCTexture2D*>(texture)) && "setTexture expects a CCTexture2D. Invalid argument");

    if ( m_pobTexture != texture )
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(m_pobTexture);
        m_pobTexture = texture;
        updateBlendFunc();
    }
}

cc::CCTexture2D* PolygonSprite::getTexture(void)
{
    return m_pobTexture;
}

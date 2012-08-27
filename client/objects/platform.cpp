#include "platform.hpp"

#include "master.hpp"

#include "physics.hpp"
#include "view.hpp"

#include "resource_utils.hpp"
#include "triangulator.hpp"

//#include <algorithm>

class PolygonSprite : public cc::CCNode
{
/** Opacity: conforms to CCRGBAProtocol protocol */
CC_PROPERTY(GLubyte, _opacity, Opacity)
/** Color: conforms with CCRGBAProtocol protocol */
CC_PROPERTY_PASS_BY_REF(cc::ccColor3B, _color, Color);

public:
	PolygonSprite* create(cc::CCTexture2D* tex, std::vector<cc::CCPoint> const& vertices)
	{
		PolygonSprite *pobSprite = new PolygonSprite(vertices);
		if (pobSprite && pobSprite->init(tex))
		{
			pobSprite->autorelease();
			return pobSprite;
		}
		CC_SAFE_DELETE(pobSprite);
		return NULL;
	}

	PolygonSprite(std::vector<cc::CCPoint> const& vertices)
	{
		Vector2dVector input;
        Vector2dVector output;
		for( size_t i=0; i<vertices.size(); ++i ) input.push_back( Vector2d( vertices[i].x, vertices[i].y ) );
        Triangulate::Process( input, output );
		for( size_t i=0; i<output.size(); ++i )
        {
            cc::ccVertex3F v = { output[i].GetX(), output[i].GetY(), 0 };
            _triangles.push_back( v );
        }
	}

	bool init(cc::CCTexture2D *tex_ptr)
	{
		// shader program
		setShaderProgram(cc::CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));

		//m_bRecursiveDirty = false;
		//setDirty(false);

		//m_bOpacityModifyRGB = true;
		//m_nOpacity = 255;
		//m_sColor = m_sColorUnmodified = ccWHITE;

		_blend_func.src = CC_BLEND_SRC;
		_blend_func.dst = CC_BLEND_DST;

		//m_bFlipX = m_bFlipY = false;

		// default transform anchor: center
		//setAnchorPoint(ccp(0.5f, 0.5f));

		// zwoptex default values
		//m_obOffsetPosition = CCPointZero;

		//m_bHasChildren = false;
    
		// clean the Quad
		//memset(&m_sQuad, 0, sizeof(m_sQuad));

		// Atlas: Color
		//ccColor4B tmpColor = { 255, 255, 255, 255 };
		//m_sQuad.bl.colors = tmpColor;
		//m_sQuad.br.colors = tmpColor;
		//m_sQuad.tl.colors = tmpColor;
		//m_sQuad.tr.colors = tmpColor;

		// update texture (calls updateBlendFunc)
		setTexture(tex_ptr);
		setTextureCoords();

		// by default use "Self Render".
		// if the sprite is added to a batchnode, then it will automatically switch to "batchnode Render"
		//setBatchNode(NULL);

		return true;
	}

	void setOpacityModifyRGB(bool bValue)
	{
		cc::ccColor3B oldColor = _color;
		_opacity_modify_rgb = bValue;
		_color = oldColor;
	}

	bool isOpacityModifyRGB(void)
	{
		return _opacity_modify_rgb;
	}


	void updateBlendFunc(void)
	{
		// it is possible to have an untextured sprite
		if (! _texture || ! _texture->hasPremultipliedAlpha())
		{
			_blend_func.src = GL_SRC_ALPHA;
			_blend_func.dst = GL_ONE_MINUS_SRC_ALPHA;
			setOpacityModifyRGB(false);
		}
		else
		{
			_blend_func.src = CC_BLEND_SRC;
			_blend_func.dst = CC_BLEND_DST;
			setOpacityModifyRGB(true);
		}
	}

	void setTexture(cc::CCTexture2D *texture)
	{
		// accept texture==nil as argument
		assert( (!texture || dynamic_cast<cc::CCTexture2D*>(texture)) && "setTexture expects a CCTexture2D. Invalid argument");

		if (_texture != texture)
		{
			CC_SAFE_RETAIN(texture);
			CC_SAFE_RELEASE(_texture);
			_texture = texture;
			updateBlendFunc();
		}
	}

	void setTextureCoords()
	{
		for( size_t i=0, size=_triangles.size(); i<size; ++i )
		{
            cc::ccTex2F t;
			_tex_coords.push_back( t );
		}
	}

	virtual void draw() override
	{
		using namespace cc;

		CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "PolygonSprite - draw");

		CC_NODE_DRAW_SETUP();

		ccGLBlendFunc( _blend_func.src, _blend_func.dst );

		if (_texture != NULL)
		{
			ccGLBindTexture2D( _texture->getName() );
		}
		else
		{
			ccGLBindTexture2D(0);
		}
    
		//
		// Attributes
		//

		//ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
        ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords );

	//#define kQuadSize sizeof(m_sQuad.bl)
	//	long offset = (long)&m_sQuad;

		// vertex
		//int diff = offsetof( ccV3F_C4B_T2F, vertices);

        glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, 0, (void*) ( _triangles.data() ));

		// texCoods
		//diff = offsetof( ccV3F_C4B_T2F, texCoords);
        glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, (void*)(_tex_coords.data() ));

		// color
        glColor4f(1.f, 1.f, 1.f, 1.f);
		//diff = offsetof( ccV3F_C4B_T2F, colors);
		//glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));


        glDrawArrays( GL_TRIANGLES, 0, _triangles.size() );

		CHECK_GL_ERROR_DEBUG();

		CC_INCREMENT_GL_DRAWS(1);

		CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "PolygonSprite - draw");
	}

private:
	std::vector<cc::ccVertex3F> _triangles;
	std::vector<cc::ccTex2F> _tex_coords;
	cc::CCTexture2D* _texture;

	cc::ccBlendFunc _blend_func;
	bool _opacity_modify_rgb;
};

namespace objects
{

    Platform* Platform::create(std::vector<pr::Vec2> const& vertices)
    {
        return new Platform(vertices);
    }

    Platform::Platform(std::vector<pr::Vec2> const& vertices)
    {
		assert( (vertices.size()>2) && "Min vertices count of platform = 3!");

		Vector2dVector input;
        Vector2dVector output;
		for( size_t i=0, size = vertices.size(); i<size; ++i ) input.push_back( Vector2d( vertices[i].x, vertices[i].y ) );
		Triangulate::Process( input, output );

		pr::Vec2 lower_bound = vertices[0], upper_bound = vertices[0];
		for( size_t i=1, size = vertices.size(); i<size; ++i )
		{
			lower_bound.x = std::min(vertices[0].x, lower_bound.x);
			lower_bound.y = std::min(vertices[0].x, lower_bound.y);
			upper_bound.x = std::max(vertices[0].y, upper_bound.x);
			upper_bound.y = std::max(vertices[0].y, upper_bound.y);
		}
		pr::Vec2 center = (upper_bound - lower_bound);
		center /= 2.f;

        //init physics
		b2BodyDef body_def;
		body_def.type = b2_staticBody;
		body_def.position = b2Vec2( center.tob2Vec2() );

		b2PolygonShape shape;

		b2FixtureDef fixt_def;
		fixt_def.friction = 0.3f;
		fixt_def.restitution = 0.2f;
		fixt_def.userData = (void*)this;
		fixt_def.shape = &shape;

		_body = master_t::subsystem<Physics>().worldEngine()->CreateBody( &body_def );

		b2Vec2 v[3];
		for( size_t i=0, count = output.size()/3; i<count; ++i )
		{
			v[0] = b2Vec2( output[i*3].GetX(), output[i*3].GetY() );
			v[1] = b2Vec2( output[i*3+1].GetX(), output[i*3+1].GetY() );
			v[2] = b2Vec2( output[i*3+2].GetX(), output[i*3+2].GetY() );
			shape.Set( v, 3 );

			_body->CreateFixture( &fixt_def );
		}




		cc::CCSprite* sprite = cc::CCSprite::create( res::picture("ground").c_str() );
		cc::CCTexture2D* tex = sprite->getTexture();
		
		cc::ccTexParams tex_params = { GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT };
		tex->setTexParameters( &tex_params );

		b2Vec2 bv[3];
		for( size_t i=0, count = output.size()/3; i<count; ++i )
		{
			bv[0] = b2Vec2( output[i*3].GetX(), output[i*3].GetY() );
			bv[1] = b2Vec2( output[i*3+1].GetX(), output[i*3+1].GetY() );
			bv[2] = b2Vec2( output[i*3+2].GetX(), output[i*3+2].GetY() );
			shape.Set( bv, 3 );

			_body->CreateFixture( &fixt_def );
		}

		

        //defs::st::OneShapeDef def;
        //def.setUserData( (void*)this );
        //
        //b2Vec2* b2d_vertices = new b2Vec2[count];
        //for( size_t i=0; i<count; ++i ) b2d_vertices[i] = vertices[i].tob2Vec2();
        //def.setShapeLoop( b2d_vertices, count );
        //delete[] b2d_vertices;
        //
        //_body = master_t::subsystem<Physics>().CreateBody( def );

        ////init view
        //b2AABB aabb = _body->GetFixtureList()->GetAABB(0);
        //cc::CCSize size = pr::Vec2(10, 10).toCCSize();
        //cc::CCRenderTexture* rend_text = cc::CCRenderTexture::create( size.width, size.height );
        //cc::ccColor4F color = {255, 255, 255, 1.f};
        //cc::CCTexture2D* ground_tex = cc::CCSprite::create( res::picture("ground").c_str() )->getTexture();
        //Vector2dVector input;
        //Vector2dVector output;
        //for( size_t i=0; i<count; ++i ) input.push_back( Vector2d( vertices[i].x, vertices[i].y ) );
        //Triangulate::Process( input, output );

        //rend_text->beginWithClear( color.r, color.g, color.b, color.a );

        ////cc::ccTexParams params = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
        ////ground_tex->setTexParameters( &params );
        ////glBindTexture(GL_TEXTURE_2D, ground_tex->getName());
        //glDisable(GL_TEXTURE_2D);
        //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        //glDisableClientState(GL_COLOR_ARRAY);

        //cc::CCPoint verts[6];
        //
        //verts[0] = ccp(0, 0);
        //verts[1] = ccp(0, size.height);
        //verts[2] = ccp(size.width, 0);
        //verts[3] = ccp(0, size.height);
        //verts[4] = ccp(size.width, 0);
        //verts[5] = ccp(size.width, size.height);

 
        //glColor4f(1, 1, 1, 1);
        //glVertexPointer( 2, GL_FLOAT, 0, verts );
        ////glTexCoordPointer(2, GL_FLOAT, 0, verts );
        //glDrawArrays(GL_TRIANGLES, 0, (GLsizei)6 );

        //glEnableClientState(GL_COLOR_ARRAY);
        //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        //glEnable(GL_TEXTURE_2D);

        //rend_text->end();
        //_sprite = cc::CCSprite::create( rend_text->getSprite()->getTexture() );
        //_sprite->setScale(1);

        /*unsigned char color[] = {100, 100, 100};
        cc::CCTexture2D* texture = new cc::CCTexture2D();
        texture->autorelease();
        texture->initWithData(color, cocos2d::kCCTexture2DPixelFormat_RGB888, 1, 1, size.toCCSize() );

        _sprite = cc::CCSprite::create( texture );*/
        
        addSprite(_sprite);
        draw();
    }

    Platform::~Platform()
    {
        removeSprite(_sprite);
    }
        
    void Platform::draw()
    {
        drawSpriteHelper(_sprite, pr::Vec2(15,15), 0);
    }

    b2Body* Platform::getBody()
    {
        return _body.get();
    }

}//end namespace objects
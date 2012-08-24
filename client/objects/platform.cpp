#include "platform.hpp"

#include "master.hpp"

#include "physics.hpp"
#include "view.hpp"

#include "resource_utils.hpp"
#include "triangulator.hpp"

namespace objects
{

    Platform* Platform::create(const pr::Vec2* vertices, size_t count)
    {
        return new Platform(vertices, count);
    }

    Platform::Platform(const pr::Vec2* vertices, size_t count)
    {
        //init physics
        defs::st::OneShapeDef def;
        def.setUserData( (void*)this );
        
        b2Vec2* b2d_vertices = new b2Vec2[count];
        for( size_t i=0; i<count; ++i ) b2d_vertices[i] = vertices[i].tob2Vec2();
        def.setShapeLoop( b2d_vertices, count );
        delete[] b2d_vertices;
        
        _body = master_t::subsystem<Physics>().CreateBody( def );

        //init view
        b2AABB aabb = _body->GetFixtureList()->GetAABB(0);
        cc::CCSize size = pr::Vec2(10, 10).toCCSize();
        cc::CCRenderTexture* rend_text = cc::CCRenderTexture::create( size.width, size.height );
        cc::ccColor4F color = {255, 255, 255, 1.f};
        cc::CCTexture2D* ground_tex = cc::CCSprite::create( res::picture("ground").c_str() )->getTexture();
        Vector2dVector input;
        Vector2dVector output;
        for( size_t i=0; i<count; ++i ) input.push_back( Vector2d( vertices[i].x, vertices[i].y ) );
        Triangulate::Process( input, output );

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
#ifndef _AREKS_SPLASH_SCREEN_HPP_
#define _AREKS_SPLASH_SCREEN_HPP_

# include "defs.hpp"
# include "subsystem.hpp"
# include "primitives.hpp"

class SplashScreen : public cc::CCObject, public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;
    
public:
    SplashScreen();
    ~SplashScreen();

    cc::CCScene * scene();

private:
    cc::CCScene *m_scene;
	cc::CCLayer *m_layer;
};

#endif

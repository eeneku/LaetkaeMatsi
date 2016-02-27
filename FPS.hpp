#ifndef __FPS_HPP__
#define __FPS_HPP__

#include"SDL.h"

class FPS
{
    private :

    static unsigned int oldTime;
    static int lastTime;

    static int frames;

    public :

    static float speedFactor;
    static float currentFPS;

    FPS();
    static void update();
};

#endif

#include"..\inc\FPS.hpp"


unsigned int FPS::oldTime;
int FPS::lastTime;

int FPS::frames;

float FPS::speedFactor;
float FPS::currentFPS;

FPS::FPS()
{
    currentFPS = 0;

    oldTime = 0;
    lastTime = 0;

    speedFactor = 0;

    frames = 0;
}

void FPS::update()
{
    if(oldTime + 1000 < SDL_GetTicks())
    {
        oldTime = SDL_GetTicks();

        currentFPS = frames;

        frames = 0;
    }

    speedFactor = ((SDL_GetTicks() - lastTime) / 1000.0f);

    lastTime = SDL_GetTicks();

    frames++;
}

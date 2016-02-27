#include"..\inc\Animation.hpp"

// Konstruktori
Animation::Animation()
{
    curRowFrame = 0;
    curColFrame = 0;
    numRowFrames = 0;
    numColFrames = 0;
    frameInc = 1;
    frameHeight = 0;
    frameWidth = 0;

    frameRate = 100;
    oldTime = 0;
    runTime = 0;

    oscillate = false;
    animating = true;
}

// P‰ivitt‰‰ animaation
void Animation::update()
{
    if(animating && (oldTime + frameRate < SDL_GetTicks()))
    {
        curRowFrame += frameInc;
        oldTime = SDL_GetTicks();

        if(oscillate)
        {
            if(frameInc > 0)
            {
                if(curRowFrame >= numRowFrames - 1)
                {
                    frameInc = -frameInc;
                }
            }
            else if(curRowFrame <= 0)
            {
                frameInc = -frameInc;
            }
        }
        else if(curRowFrame > numRowFrames - 1)
        {
            curRowFrame = 0;
        }
    }
}

// Pys‰ytt‰‰
void Animation::pause()
{
    // Kun animaation laittaa pauselle, otetaan JO yhden kehyksen aikana kulunut aika ylˆs (runTime),
    // ja kun sprite otetaan paussilta, p‰ivitet‰‰n oldTime nykyaikaan ja v‰hennet‰‰n siit‰ runTime.
    // N‰in se pysyy selvill‰ ja jatkaa kehyksen loppuun asti.
    if(animating)
    {
        runTime = SDL_GetTicks() - oldTime;
        animating = false;
    }
}

// Jatkaa
void Animation::unpause()
{
    if(!animating)
    {
        oldTime = SDL_GetTicks() - runTime;
        animating = true;
    }
}

int Animation::getRowFrame()
{
    return curRowFrame * frameHeight;
}

int Animation::getColFrame()
{
    return curColFrame * frameWidth;
}

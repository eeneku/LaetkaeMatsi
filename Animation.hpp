#ifndef __ANIMATION_HPP__
#define __ANIMATION_HPP__

#include"SDL.h"

// Luokka animaatioiden käsittelyyn
class Animation
{
    public:

    // Nykyinen kehysrivi
    int curRowFrame;

    // Nykyinen kehyssarake
    int curColFrame;

    // Kehyksen lisäysmuuttuja
    int frameInc;

    // Kehysten välinen aika millisekunteina
    int frameRate;

    // Viime päivityskerta
    float oldTime;

    // Plääh
    float runTime;

    // Kehyksen koko
    int frameWidth;
    int frameHeight;

    // Rivien määrä
    int numRowFrames;

    // Sarakkeiden määrä
    int numColFrames;

    // Käykö efekti
    bool oscillate;

    // Käykö animaatio
    bool animating;

    //Konstruktori
    Animation();

    // Metodit
    void update();
    void pause();
    void unpause();
    int getRowFrame();
    int getColFrame();
};

#endif

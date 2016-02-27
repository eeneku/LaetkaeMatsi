#ifndef __SPRITE_HPP__
#define __SPRITE_HPP__

#include<vector>
#include<string>
#include"SDL.h"
#include"..\inc\Animation.hpp"
#include"..\inc\Surface.hpp"

// Sprite-luokka
class Sprite
{
    protected :

    // Animaation hallintaan
    Animation animControl;

    // Animaatiografiikka
    SDL_Surface * surfTexture;

    // Spriten paikkavektori
    Vector2D position;

    // Spriten aiemmat koordinaatit
    Vector2D prevPosition;

    // Spriten oletuskoordinaatit
    Vector2D defPosition;

    // Spriten nopeusvektori
    Vector2D velocity;

    // Spriten suuntavektori
    Vector2D direction;

    // Spriten nopeus (errjoku)
    int speed;

    // Spriten törmäysalue
    SDL_Rect colBox;

    // Onko sprite olemassa vai ei
    bool visible;

    public :

    // Metodit

    // Piirtää kuvan halutulle pinnalle
    virtual void draw(SDL_Surface * surfDest);

    // Alustaa spriten
    virtual void init(SDL_Surface * surf, int w, int h);

    // Suorittaa kaikki jutut
    virtual void update();

    // Sijoittaa kartalle
    void setPosition(float nX, float nY) { position.x = nX; position.y = nY; }
    void setPosition(Vector2D & nT) { position.x = nT.x; position.y = nT.y; }

    // Asettaa oletuskoordinaatit
    void setDefaultPosition(float nX, float nY) { defPosition.x = nX; defPosition.y = nY; }

    // Annetaan nopeus
    void setVelocity(float nX, float nY) { velocity.x = nX; velocity.y = nY; }

    // Luo törmäyslaatikon
    void setColBox(int x, int y, int w, int h) { colBox.x = x; colBox.y = y; colBox.w = w; colBox.h = h; }

    // Antaa törmäyslaatikon
    SDL_Rect & getColBox() { return colBox; }

    // Antaa sijainnin
    Vector2D & getPosition() { return position; }
    float getX() { return position.x; }
    float getY() { return position.y; }
    float getCenterX() { return position.x + animControl.frameWidth / 2; }
    float getCenterY() { return position.y + animControl.frameHeight / 2; }

    // Antaa oletussijainnin
    Vector2D & getDefaultPosition() { return defPosition; }

    // Hyvin alkeellinen törmäystarkistus!
    bool checkCollision(Sprite &spr);
    bool checkCollisionX(Sprite &spr);
    bool checkCollisionY(Sprite &spr);
    bool checkCollision(SDL_Rect &rect);
    bool checkCollisionX(SDL_Rect &rect);
    bool checkCollisionY(SDL_Rect &rect);
    bool checkCollision(int nX, int nY, int nW, int nH);
    bool checkCollisionX(int nX, int nY, int nW, int nH);
    bool checkCollisionY(int nX, int nY, int nW, int nH);

    // Tappaa spriten
    void kill() { visible = false; }

    // Henkiin taas!
    void resurrect() { visible = true; }

    // Onko sprite elossa?
    bool isAlive();

    // Konstruktori ja destruktori
    Sprite();
    virtual ~Sprite();
};

#endif

#include"..\inc\Sprite.hpp"

// Spriten konstruktori ja destruktori
Sprite::Sprite()
{
    position.x = 0;
    position.y = 0;
    prevPosition.x = 0;
    prevPosition.y = 0;
    defPosition.x = 0;
    defPosition.y = 0;
    direction.y = 0;
    direction.x = 0;
    velocity.x = 0;
    velocity.y = 0;
    visible = true;
    speed = 0;
    colBox.x = 0;
    colBox.y = 0;
    colBox.w = 0;
    colBox.h = 0;
}

Sprite::~Sprite()
{
}

// Asettaa Spriten
void Sprite::init(SDL_Surface * surf, int w, int h)
{
    surfTexture = surf;

    animControl.frameWidth = w;
    animControl.frameHeight = h;

    animControl.numRowFrames = surfTexture->h / animControl.frameHeight;
    animControl.numColFrames = surfTexture->w / animControl.frameWidth;

    colBox.x = 0;
    colBox.y = 0;
    colBox.w = w;
    colBox.h = h;
}

void Sprite::draw(SDL_Surface * surfDest)
{
    // Piirretään näytölle
    Surface::draw(surfTexture,surfDest,(int)position.x,(int)position.y,animControl.getColFrame(),animControl.getRowFrame(),animControl.frameWidth,animControl.frameHeight);
}

// Suorittaa kaikki jutut
void Sprite::update()
{
    animControl.update();
}

// Alkeellinen törmäystarkistus kahdelle spritelle
bool Sprite::checkCollision(Sprite &spr)
{
    SDL_Rect tempBox = spr.getColBox();
    Vector2D tempPos = spr.getPosition();

    if((position.x + colBox.w) < (tempPos.x + tempBox.x)) return false;
    if((position.x + colBox.x) > (tempPos.x + tempBox.w)) return false;
    if((position.y + colBox.h) < (tempPos.y + tempBox.y)) return false;
    if((position.y + colBox.y) > (tempPos.y + tempBox.h)) return false;

    return true;
}

// Alkeellinen törmäystarkistus kahdelle spritelle x-koordinaatissa
bool Sprite::checkCollisionX(Sprite &spr)
{
    SDL_Rect tempBox = spr.getColBox();
    Vector2D tempPos = spr.getPosition();

    if((position.x + colBox.w) < (tempPos.x + tempBox.x)) return false;
    if((position.x + colBox.x) > (tempPos.x + tempBox.w)) return false;
    if((prevPosition.y + colBox.h) < (tempPos.y + tempBox.y)) return false;
    if((prevPosition.y + colBox.y) > (tempPos.y + tempBox.h)) return false;

    return true;
}

// Alkeellinen törmäystarkistus kahdelle spritelle y-koordinaatissa
bool Sprite::checkCollisionY(Sprite &spr)
{
    SDL_Rect tempBox = spr.getColBox();
    Vector2D tempPos = spr.getPosition();

    if((prevPosition.x + colBox.w) < (tempPos.x + tempBox.x)) return false;
    if((prevPosition.x + colBox.x) > (tempPos.x + tempBox.w)) return false;
    if((position.y + colBox.h) < (tempPos.y + tempBox.y)) return false;
    if((position.y + colBox.y) > (tempPos.y + tempBox.h)) return false;

    return true;
}

// Alkeellinen törmäystarkistus spritelle ja rectille
bool Sprite::checkCollision(SDL_Rect &rect)
{
    if((position.x + colBox.w) < rect.x) return false;
    if((position.x + colBox.x) > (rect.x + rect.w)) return false;
    if((position.y + colBox.h) < rect.y) return false;
    if((position.y + colBox.y) > (rect.y + rect.h)) return false;

    return true;
}

// Alkeellinen törmäystarkistus spritelle ja rectille
bool Sprite::checkCollisionX(SDL_Rect &rect)
{
    if((position.x + colBox.w) < rect.x) return false;
    if((position.x + colBox.x) > (rect.x + rect.w)) return false;
    if((prevPosition.y + colBox.h) < rect.y) return false;
    if((prevPosition.y + colBox.y) > (rect.y + rect.h)) return false;

    return true;
}

// Alkeellinen törmäystarkistus spritelle ja rectille
bool Sprite::checkCollisionY(SDL_Rect &rect)
{
    if((prevPosition.x + colBox.w) < rect.x) return false;
    if((prevPosition.x + colBox.x) > (rect.x + rect.w)) return false;
    if((position.y + colBox.h) < rect.y) return false;
    if((position.y + colBox.y) > (rect.y + rect.h)) return false;

    return true;
}

// Alkeellinen törmäystarkistus spritelle ja jollekin alueelle
bool Sprite::checkCollision(int nX, int nY, int nW, int nH)
{
    if((position.x + colBox.w) < nX) return false;
    if((position.x + colBox.x) > (nX + nW)) return false;
    if((position.y + colBox.h) < nY) return false;
    if((position.y + colBox.y) > (nY + nH)) return false;

    return true;
}

// Alkeellinen törmäystarkistus spritelle ja jollekin alueelle
bool Sprite::checkCollisionX(int nX, int nY, int nW, int nH)
{
    if((position.x + colBox.w) < nX) return false;
    if((position.x + colBox.x) > (nX + nW)) return false;
    if((prevPosition.y + colBox.h) < nY) return false;
    if((prevPosition.y + colBox.y) > (nY + nH)) return false;

    return true;
}

// Alkeellinen törmäystarkistus spritelle ja jollekin alueelle
bool Sprite::checkCollisionY(int nX, int nY, int nW, int nH)
{
    if((prevPosition.x + colBox.w) < nX) return false;
    if((prevPosition.x + colBox.x) > (nX + nW)) return false;
    if((position.y + colBox.h) < nY) return false;
    if((position.y + colBox.y) > (nY + nH)) return false;

    return true;
}

// Onko elossa
bool Sprite::isAlive()
{
    if(visible) return true;
    else return false;
}

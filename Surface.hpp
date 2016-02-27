#ifndef __SURFACE_HPP__
#define __SURFACE_HPP__

#include<vector>
#include<string>
#include"SDL.h"
#include"SDL_image.h"

extern Uint32 rmask;
extern Uint32 gmask;
extern Uint32 bmask;
extern Uint32 amask;

extern SDL_Color clrBlack;
extern SDL_Color clrBlue;
extern SDL_Color clrRed;
extern SDL_Color clrYellow;
extern SDL_Color clrPink;
extern SDL_Color clrWhite;
extern SDL_Color clrGreen;
extern SDL_Color clrGrey;
extern SDL_Color clrOrange;

// Operaattoreita SDL_Colorien kopioimiseen ja vertailuun
bool operator==(SDL_Color a, SDL_Color b);
bool operator!=(SDL_Color a, SDL_Color b);

// Sis‰lt‰‰ yleiset funktiot kuvien lataukseen ja piirtoon
class Surface
{
    public :

    static int mapRGB(SDL_PixelFormat * format, SDL_Color color);

    static int fillRect(SDL_Surface * dest, SDL_Rect * rect, SDL_Color & color);

    static SDL_Surface * load(std::string file, bool alpha = true);

    static bool draw(SDL_Surface * src, SDL_Surface * dest, int x, int y);

    static bool draw(SDL_Surface * src, SDL_Surface * dest, int x, int y, int x2, int y2, int w, int h);

    static bool transparent(SDL_Surface * surf, int r, int g, int b);

    static SDL_Rect newRect(int xs,int ys,int dx,int dy );

    static SDL_Color newColor(int r,int g,int b,int a = 0);

    static SDL_Surface * newSurface(int w, int h, bool alpha = true);
};

class Vector2D
{
    public :
    float x, y;
};

#endif

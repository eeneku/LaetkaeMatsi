#ifndef __FONT_HPP__
#define __FONT_HPP__

#include<string>
#include<vector>
#include"SDL.h"
#include"SDL_ttf.h"
#include"..\inc\Surface.hpp"

// Tekstien tasaus
#define ALIGN_LEFT 0
#define ALIGN_CENTER 1
#define ALIGN_RIGHT 2
#define VALIGN_TOP 0
#define VALIGN_MIDDLE 1
#define VALIGN_BOTTOM 2

// Luokka fonttien käsittelyyn
class Font
{
    public :

    static TTF_Font * load(std::string file, int size);
    static bool drawSolid(TTF_Font * font, SDL_Surface * surfDest, int x, int y, SDL_Color clr, std::string str);
    static bool drawLinesSolid(TTF_Font * font, SDL_Surface * dest, int x, int y, SDL_Color clr, int align, int valign, std::string str);
    static bool drawLinesShaded(TTF_Font * font, SDL_Surface * dest, int x, int y, SDL_Color clr, SDL_Color bgClr, int align, int valign, std::string str);
    static bool drawLinesBlended(TTF_Font * font, SDL_Surface * dest, int x, int y, SDL_Color clr, int align, int valign, std::string str);
};

#endif

#include"..\inc\Surface.hpp"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
Uint32 rmask = 0xff000000;
Uint32 gmask = 0x00ff0000;
Uint32 bmask = 0x0000ff00;
Uint32 amask = 0x000000ff;
#else
Uint32 rmask = 0x000000ff;
Uint32 gmask = 0x0000ff00;
Uint32 bmask = 0x00ff0000;
Uint32 amask = 0xff000000;
#endif

SDL_Color clrBlack = Surface::newColor(0,0,0);
SDL_Color clrBlue = Surface::newColor(0,0,255);
SDL_Color clrRed = Surface::newColor(255,0,00);
SDL_Color clrYellow = Surface::newColor(255,255,0);
SDL_Color clrPink = Surface::newColor(255,0,255);
SDL_Color clrWhite = Surface::newColor(255,255,255);
SDL_Color clrGreen = Surface::newColor(0,255,0);
SDL_Color clrGrey = Surface::newColor(128,128,128);
SDL_Color clrOrange = Surface::newColor(255,128,0);

// Palauttaa SDL_Rectin annetuilla parametreilla
SDL_Rect Surface::newRect(int xs,int ys,int dx,int dy )
{
	SDL_Rect rect;
    rect.x = xs;
    rect.y = ys;
    rect.w = dx;
    rect.h = dy;
	return rect;
}

// Palauttaa uuden SDL_Colorin annetuilla parametreilla
SDL_Color Surface::newColor(int r,int g,int b,int a)
{
	SDL_Color clr;
    clr.r = r;
    clr.g = g;
    clr.b = b;
    clr.unused = a;
	return clr;
}

// Operaattoreita SDL_Colorien kopioimiseen ja vertailuun
bool operator==(SDL_Color a, SDL_Color b)
{
	return (a.r == b.r && a.g == b.g && a.b == b.b);
}
bool operator!=(SDL_Color a, SDL_Color b)
{
	return ((a.r != b.r || a.g != b.g || a.b != b.b));
}

// Helpompi piirtäminen
int Surface::mapRGB(SDL_PixelFormat *format,SDL_Color clr)
{
	return SDL_MapRGB(format,clr.r,clr.g,clr.b);
}

// Helpompi täyttö
int Surface::fillRect(SDL_Surface *dest,SDL_Rect *rc,SDL_Color &clr)
{
	if(!dest) return -1;
	return SDL_FillRect(dest,rc,Surface::mapRGB(dest->format,clr));
}

// Lataa kuvan
SDL_Surface * Surface::load(std::string file, bool alpha)
{
    // Lataa kuvan väliaikaiseen muuttujaan (temp), asettaa sen samaan formaattiin näytön kanssa ja palauttaa kuvan
    SDL_Surface * temp = NULL;
    SDL_Surface * temp2 = NULL;

    if(!(temp = IMG_Load(file.c_str())))
    {
        fprintf(stderr,"....ERROR: Could not load image %s\n", file.c_str());
        return NULL;
    }

    if(alpha)
    temp2 = SDL_DisplayFormatAlpha(temp);
    else
    temp2 = SDL_DisplayFormat(temp);

    SDL_FreeSurface(temp);
    temp = NULL;

    return temp2;
}

// Piirtää kuvan
bool Surface::draw(SDL_Surface * src, SDL_Surface * dest, int x, int y)
{
    if(dest == NULL || src == NULL)
    {
        fprintf(stderr,"....ERROR: Surface not found\n");
        return false;
    }

    // Koordinaatit mihin kuva piirretään
    SDL_Rect rectPos;
    rectPos.x = x;
    rectPos.y = y;

    // Ja blitataan
    SDL_BlitSurface(src,NULL,dest,&rectPos);

    return true;
}

// Piirtää kuvan
bool Surface::draw(SDL_Surface * src, SDL_Surface * dest, int x, int y, int x2, int y2, int w, int h)
{
    if(dest == NULL || src == NULL)
    {
        fprintf(stderr,"....ERROR: Surface not found\n");
        return false;
    }

    // Koordinaatit mihin kuva piirretään
    SDL_Rect rectPos;
    rectPos.x = x;
    rectPos.y = y;

    // Koordinaatit mistä kuva piirretään
    SDL_Rect rectSrc;
    rectSrc.x = x2;
    rectSrc.y = y2;
    rectSrc.h = h;
    rectSrc.w = w;

    // Ja blitataan
    SDL_BlitSurface(src,&rectSrc,dest,&rectPos);

    return true;
}

// Luo uuden pinnan
SDL_Surface * Surface::newSurface(int w, int h, bool alpha)
{
    SDL_Surface * temp;
    SDL_Surface * temp2;

    temp = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, 32, rmask, gmask, bmask, amask);

    if(alpha)
    temp2 = SDL_DisplayFormatAlpha(temp);
    else
    temp2 = SDL_DisplayFormat(temp);

    SDL_FreeSurface(temp);
    temp = NULL;

    return temp2;
}

// Tekee annetusta väristä läpinäkyvän annetussa pinnassa
bool Surface::transparent(SDL_Surface * src, int r, int g, int b)
{
    if(src == NULL)
    {
        fprintf(stderr,"....ERROR: Surface not found\n");
        return -1;
    }

    SDL_SetColorKey(src,SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(src->format, r, g, b));

    return true;
}

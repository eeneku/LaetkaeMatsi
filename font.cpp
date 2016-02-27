#include"..\inc\Font.hpp"

// Lataa fontin
TTF_Font * Font::load(std::string file, int size)
{
    TTF_Font * temp = NULL;

    if((temp = TTF_OpenFont(file.c_str(),size)) == NULL)
    {
        fprintf(stderr,"....ERROR: Could not load font %s\n",file.c_str());
        return false;
    }

    return temp;
}

// VERI SIMPLE
bool Font::drawSolid(TTF_Font * font, SDL_Surface * surfDest, int x, int y, SDL_Color clr, std::string str)
{
    if(str.length() == 0) return false;
    if(font == NULL)
    {
        fprintf(stderr,"....ERROR: Font not found\n");
        return false;
    }

    if(surfDest == NULL)
    {
        fprintf(stderr,"....ERROR: Surface not found\n");
        return false;

    }

    SDL_Rect rcDest;
    rcDest.x = x;
    rcDest.y = y;
    rcDest.w = 0;
    rcDest.h = 0;

    SDL_Surface * temp = TTF_RenderText_Solid(font,str.c_str(),clr);

    SDL_BlitSurface(temp,NULL,surfDest,&rcDest);

    SDL_FreeSurface(temp);

    return true;
}

// Kirjoittaa tekstiä nopeasti
bool Font::drawLinesSolid(TTF_Font * font, SDL_Surface * surfDest, int x, int y, SDL_Color clr, int align, int valign, std::string str)
{
    // Katsotaan jos tekstiä, kohdetta tai fonttia ei ole, ja jos ei niin palautetaan 0
    if(str.length() == 0) return false;
    if(font == NULL)
    {
        fprintf(stderr,"....ERROR: Font not found\n");
        return false;
    }

    if(surfDest == NULL)
    {
        fprintf(stderr,"....ERROR: Surface not found\n");
        return false;
    }

    // Katsotaan rivien väli ja asetetaan pituus ja korkeus
    int lineSkip = TTF_FontLineSkip(font);
    int width = 10;
    int height = 10;

    // Vector eri riveille ja tilapäinen string
    std::vector<std::string> Lines;
    std::string strsub;

    int i = 0;
    while(i != -1)
    {
        // Etsitään seuraava rivinlopetus ja kopioidaan se pätkä strsubiin
        i = str.find('\n',0);
        strsub = str.substr(0,i);

        // Jos pätkä löytyi niin...
        if(i != -1)
        {
            // Jäljelle jäänyt pätkä asetetaan
            str = str.substr(i + 1);
        }

        // Lisätään löytynyt pätkä vectoriin
        Lines.push_back(strsub);

        // Katsotaan ja asetetaan tekstin korkeus
        int w = 0;
        TTF_SizeText(font,strsub.c_str(),&w,&height);
        if(w > width) width = w;
    }

    // Katsotaan ja asetetaan tekstin korkeus
    height = (Lines.size() - 1) * lineSkip + height;

    // Blitataan teksti näytölle rivi kerrallaan
    for(unsigned int i = 0; i < Lines.size(); i++)
    {
        SDL_Rect destRc;
        if(align == ALIGN_LEFT || !(ALIGN_CENTER || ALIGN_RIGHT))
        {
            destRc.x = x;
        }
        else if(align == ALIGN_CENTER)
        {
            int w = 0;
            int h = 0;
            TTF_SizeText(font,Lines[i].c_str(),&w,&h);
            destRc.x = x - w / 2;
        }
        else if(align == ALIGN_RIGHT)
        {
            int w = 0;
            int h = 0;
            TTF_SizeText(font,Lines[i].c_str(),&w,&h);
            destRc.x = x - w;
        }
        if(valign == VALIGN_TOP || !(VALIGN_MIDDLE || VALIGN_BOTTOM))
        {
            destRc.y = y + i * lineSkip;
        }
        else if(valign == VALIGN_MIDDLE)
        {
            int w = 0;
            int h = 0;
            TTF_SizeText(font,Lines[i].c_str(),&w,&h);
            destRc.y = (y - height / 2) + i * lineSkip;
        }
        else if(valign == VALIGN_BOTTOM)
        {
            int w = 0;
            int h = 0;
            TTF_SizeText(font,Lines[i].c_str(),&w,&h);
            destRc.y = (y - height) + i * lineSkip;
        }

        destRc.h = 0;
        destRc.w = 0;

        SDL_Surface * temp = TTF_RenderText_Solid(font,Lines[i].c_str(),clr);

        SDL_BlitSurface(temp,NULL,surfDest,&destRc);

        SDL_FreeSurface(temp);
    }

    // Poistetaan rivit
    Lines.clear();

    return true;
}

// Kirjoittaa tekstiä hienosti
bool Font::drawLinesBlended(TTF_Font * font, SDL_Surface * surfDest, int x, int y, SDL_Color clr, int align, int valign, std::string str)
{
    // Katsotaan jos tekstiä, kohdetta tai fonttia ei ole, ja jos ei niin palautetaan 0
    if(str.length() == 0) return false;
    if(font == NULL)
    {
        fprintf(stderr,"....ERROR: Font not found\n");
        return false;
    }

    if(surfDest == NULL)
    {
        fprintf(stderr,"....ERROR: Surface not found\n");
        return false;
    }

    // Katsotaan rivien väli ja asetetaan pituus ja korkeus
    int lineSkip = TTF_FontLineSkip(font);
    int width = 0;
    int height = 0;

    // Vector eri riveille ja tilapäinen string
    std::vector<std::string> Lines;
    std::string strsub;

    int i = 0;
    while(i != -1)
    {
        // Etsitään seuraava rivinlopetus ja kopioidaan se pätkä strsubiin
        i = str.find('\n', 0);
        strsub = str.substr(0,i);

        // Jos pätkä löytyi niin...
        if(i != -1)
        {
            // Jäljelle jäänyt pätkä asetetaan
            str = str.substr(i + 1);
        }

        // Lisätään löytynyt pätkä vectoriin
        Lines.push_back(strsub);

        // Katsotaan ja asetetaan tekstin korkeus
        int w = 0;
        TTF_SizeText(font,strsub.c_str(), &w, &height);
        if(w > width) width = w;
    }

    // Katsotaan ja asetetaan tekstin pituus
    height = (Lines.size()-1) * lineSkip + height;

    // Väliaikainen pinta
    SDL_Surface * surfTemp;

    // Blitataan teksti näytölle rivi kerrallaan
    for(unsigned int i = 0; i < Lines.size(); i++)
    {
        SDL_Rect destRc;
        if(align == ALIGN_LEFT || !(ALIGN_CENTER || ALIGN_RIGHT))
        {
            destRc.x = x;
        }
        else if(align == ALIGN_CENTER)
        {
            int w = 0;
            int h = 0;
            TTF_SizeText(font,Lines[i].c_str(),&w,&h);
            destRc.x = x - w / 2;
        }
        else if(align == ALIGN_RIGHT)
        {
            int w = 0;
            int h = 0;
            TTF_SizeText(font,Lines[i].c_str(),&w,&h);
            destRc.x = x - w;
        }
        if(valign == VALIGN_TOP || !(VALIGN_MIDDLE || VALIGN_BOTTOM))
        {
            destRc.y = y + i * lineSkip;
        }
        else if(valign == VALIGN_MIDDLE)
        {
            int w = 0;
            int h = 0;
            TTF_SizeText(font,Lines[i].c_str(),&w,&h);
            destRc.y = (y - height / 2) + i * lineSkip;
        }
        else if(valign == VALIGN_BOTTOM)
        {
            int w = 0;
            int h = 0;
            TTF_SizeText(font,Lines[i].c_str(),&w,&h);
            destRc.y = (y - height) + i * lineSkip;
        }

        destRc.h = 0;
        destRc.w = 0;
        surfTemp= TTF_RenderText_Blended(font,Lines[i].c_str(),clr);
        SDL_BlitSurface(surfTemp,NULL,surfDest,&destRc);
        SDL_FreeSurface(surfTemp);
    }

    // Tyhjätään väliaikainen pinta
    surfTemp = NULL;

    // Poistetaan rivit
    Lines.clear();

    return true;
}

// Kirjoittaa tekstiä taustalle
bool Font::drawLinesShaded(TTF_Font * font, SDL_Surface * surfDest, int x, int y, SDL_Color clr, SDL_Color bgClr, int align, int valign, std::string str)
{
    // Katsotaan jos tekstiä, kohdetta tai fonttia ei ole, ja jos ei niin palautetaan 0
    if(str.length() == 0) return false;
    if(font == NULL)
    {
        fprintf(stderr,"....ERROR: Font not found\n");
        return false;
    }

    if(surfDest == NULL)
    {
        fprintf(stderr,"....ERROR: Surface not found\n");
        return false;
    }

    // Katsotaan rivien väli ja asetetaan pituus ja korkeus
    int lineSkip = TTF_FontLineSkip(font);
    int width = 0;
    int height = 0;

    // Vector eri riveille ja tilapäinen string
    std::vector<std::string> Lines;
    std::string strsub;

    int i = 0;
    while(i != -1)
    {
        // Etsitään seuraava rivinlopetus ja kopioidaan se pätkä strsubiin
        i = str.find('\n', 0);
        strsub = str.substr(0,i);

        // Jos pätkä löytyi niin...
        if(i != -1)
        {
            // Jäljelle jäänyt pätkä asetetaan
            str = str.substr(i + 1);
        }

        // Lisätään löytynyt pätkä vectoriin
        Lines.push_back(strsub);

        // Katsotaan ja asetetaan tekstin korkeus
        int w = 0;
        TTF_SizeText(font,strsub.c_str(), &w, &height);
        if(w > width) width = w;
    }

    // Katsotaan ja asetetaan tekstin pituus
    height = (Lines.size()-1) * lineSkip + height;

    // Väliaikainen pinta
    SDL_Surface * surfTemp;

    // Blitataan teksti näytölle rivi kerrallaan
    for(unsigned int i = 0; i < Lines.size(); i++)
    {
        SDL_Rect destRc;
        if(align == ALIGN_LEFT || !(ALIGN_CENTER || ALIGN_RIGHT))
        {
            destRc.x = x;
        }
        else if(align == ALIGN_CENTER)
        {
            int w = 0;
            int h = 0;
            TTF_SizeText(font,Lines[i].c_str(),&w,&h);
            destRc.x = x - w / 2;
        }
        else if(align == ALIGN_RIGHT)
        {
            int w = 0;
            int h = 0;
            TTF_SizeText(font,Lines[i].c_str(),&w,&h);
            destRc.x = x - w;
        }
        if(valign == VALIGN_TOP || !(VALIGN_MIDDLE || VALIGN_BOTTOM))
        {
            destRc.y = y + i * lineSkip;
        }
        else if(valign == VALIGN_MIDDLE)
        {
            int w = 0;
            int h = 0;
            TTF_SizeText(font,Lines[i].c_str(),&w,&h);
            destRc.y = (y - height / 2) + i * lineSkip;
        }
        else if(valign == VALIGN_BOTTOM)
        {
            int w = 0;
            int h = 0;
            TTF_SizeText(font,Lines[i].c_str(),&w,&h);
            destRc.y = (y - height) + i * lineSkip;
        }

        destRc.h = 0;
        destRc.w = 0;
        surfTemp = TTF_RenderText_Shaded(font,Lines[i].c_str(),clr,bgClr);
        SDL_BlitSurface(surfTemp,NULL,surfDest,&destRc);
        SDL_FreeSurface(surfTemp);
    }

    // Tyhjätään väliaikainen pinta
    surfTemp = NULL;

    // Poistetaan rivit
    Lines.clear();

    return true;
}



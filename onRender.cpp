#include"..\inc\Game.hpp"

void Game::onRender()
{
    // Vaihdellaan tiloja
    // Peli käy
    if(state == GAME_RUNNING)
    {
        // Piirretään peli
        renderGame();
    }

    // Peli on paussilla
    else if(state == GAME_PAUSED)
    {
        renderGamePaused();
    }

    // Peli on alkamassa
    else if(state == GAME_START)
    {
        // Piirretään peli
        renderGameStart();
    }

    // Erä on ohi
    else if(state == GAME_ROUND_END)
    {
        renderGameRoundEnd();
    }

    // Peli on ohi
    else if(state == GAME_OVER)
    {
        renderGameOver();
    }

    // Peli on päävalikossa
    else if(state == MENU_MAIN)
    {
        renderMenuMain();
    }

    // Peli on asetusvalikossa
    else if(state == MENU_SETTINGS)
    {
        renderMenuSettings();
    }

    // Punaisen pelaajan näppäinasetukset
    else if(state == MENU_SETTINGS_RED)
    {
        renderMenuSettingsRed();
    }

    // Sinisen pelaajan näppäinasetukset
    else if(state == MENU_SETTINGS_BLU)
    {
        renderMenuSettingsBlu();
    }

    // Luetaan namiska
    else if(state == MENU_SETTINGS_SET_KEY)
    {
        // Kirjotetaan vähän
        Font::drawSolid(fontVerdana,surfScreen,50,300,clrRed,"Anna uusi näppäin, escapesta peruuttaa");
    }

    // Blitataan
    SDL_Flip(surfScreen);
}


void Game::renderGamePaused()
{
    // Piirretään peli
    renderGame();

    // Valikkotekstit
    // Jatketaan
    if(curOption == PAUSED_OPTION_CONTINUE)
        Font::drawLinesSolid(fontVerdana,surfScreen,320,230,clrBlack,ALIGN_CENTER,VALIGN_MIDDLE,"JATKA");
    else
        Font::drawLinesSolid(fontVerdana,surfScreen,320,230,clrGrey,ALIGN_CENTER,VALIGN_MIDDLE,"JATKA");

    // Päävalikkoon
    if(curOption == PAUSED_OPTION_MENU)
        Font::drawLinesSolid(fontVerdana,surfScreen,320,250,clrBlack,ALIGN_CENTER,VALIGN_MIDDLE,"PÄÄVALIKKO");
    else
        Font::drawLinesSolid(fontVerdana,surfScreen,320,250,clrGrey,ALIGN_CENTER,VALIGN_MIDDLE,"PÄÄVALIKKO");
}

void Game::renderGameStart()
{
    // Piirretään peli
    renderGame();

    // Kirjotetaan et kohta alkaa stna
    Font::drawLinesSolid(fontVerdana,surfScreen,320,240,clrBlack,ALIGN_CENTER,VALIGN_MIDDLE,"VALMIINA");
}

void Game::renderGameRoundEnd()
{
    // Piirretään peli
    renderGame();

    // Kirjotetaan et erä ohi
    Font::drawLinesSolid(fontVerdana,surfScreen,320,200,clrBlack,ALIGN_CENTER,VALIGN_MIDDLE,"ERÄ OHI");

    // Jatketaan
    if(curOption == END_OPTION_CONTINUE)
        Font::drawLinesSolid(fontVerdana,surfScreen,320,230,clrBlack,ALIGN_CENTER,VALIGN_MIDDLE,"JATKA");
    else
        Font::drawLinesSolid(fontVerdana,surfScreen,320,230,clrGrey,ALIGN_CENTER,VALIGN_MIDDLE,"JATKA");

    // Päävalikkoon
    if(curOption == END_OPTION_MENU)
        Font::drawLinesSolid(fontVerdana,surfScreen,320,250,clrBlack,ALIGN_CENTER,VALIGN_MIDDLE,"PÄÄVALIKKO");
    else
        Font::drawLinesSolid(fontVerdana,surfScreen,320,250,clrGrey,ALIGN_CENTER,VALIGN_MIDDLE,"PÄÄVALIKKO");

}

void Game::renderGameOver()
{
    // Piirretään peli
    renderGame();

    // Kirjotetaan et peli ohi
    Font::drawLinesSolid(fontVerdana,surfScreen,320,200,clrBlack,ALIGN_CENTER,VALIGN_MIDDLE,"PELI LOPPU");

    // Katotaan kumpi voitti
    if(winner == SININEN)
    {
        Font::drawLinesSolid(fontVerdana,surfScreen,320,235,clrBlue,ALIGN_CENTER,VALIGN_MIDDLE,"SININEN PELAAJA VOITTI");
    }
    else if(winner == PUNANEN)
    {
        Font::drawLinesSolid(fontVerdana,surfScreen,320,235,clrRed,ALIGN_CENTER,VALIGN_MIDDLE,"PUNANEN PELAAJA VOITTI");
    }
    else if(winner == TASURI)
    {
        Font::drawLinesSolid(fontVerdana,surfScreen,320,235,clrGreen,ALIGN_CENTER,VALIGN_MIDDLE,"TASAPELI TULI");
    }

    // Jatketaan
    if(curOption == OVER_OPTION_NEW)
        Font::drawLinesSolid(fontVerdana,surfScreen,320,310,clrBlack,ALIGN_CENTER,VALIGN_MIDDLE,"UUSI PELI");
    else
        Font::drawLinesSolid(fontVerdana,surfScreen,320,310,clrGrey,ALIGN_CENTER,VALIGN_MIDDLE,"UUSI PELI");

    // Päävalikkoon
    if(curOption == OVER_OPTION_MENU)
        Font::drawLinesSolid(fontVerdana,surfScreen,320,330,clrBlack,ALIGN_CENTER,VALIGN_MIDDLE,"PÄÄVALIKKO");
    else
        Font::drawLinesSolid(fontVerdana,surfScreen,320,330,clrGrey,ALIGN_CENTER,VALIGN_MIDDLE,"PÄÄVALIKKO");
}

void Game::renderMenuMain()
{
    // Piirretään taustakuva
    Surface::draw(surfTaustakuva,surfScreen,0,0);

    // Kirjotetaan polku
    Font::drawSolid(fontVerdana,surfScreen,0,0,clrRed,"Päävalikko");

    // Valikkotekstit
    // Peliin
    if(curOption == MENU_OPTION_GAME)
        Font::drawSolid(fontVerdana,surfScreen,50,300,clrOrange,"PELAA");
    else
        Font::drawSolid(fontVerdana,surfScreen,50,300,clrYellow,"PELAA");

    // Asetukset
    if(curOption == MENU_OPTION_SETTINGS)
        Font::drawSolid(fontVerdana,surfScreen,50,320,clrOrange,"ASETUKSET");
    else
        Font::drawSolid(fontVerdana,surfScreen,50,320,clrYellow,"ASETUKSET");

    // Lopetus
    if(curOption == MENU_OPTION_EXIT)
        Font::drawSolid(fontVerdana,surfScreen,50,340,clrOrange,"LOPETA");
    else
        Font::drawSolid(fontVerdana,surfScreen,50,340,clrYellow,"LOPETA");

    // Kirjotetaan vähän
    if(settingsSaved) Font::drawSolid(fontVerdana,surfScreen,50,400,clrRed,"Huom! Käynnistä peli uudelleen että saat kaikki asetukset käyttöön");
}

void Game::renderMenuSettings()
{
    // Piirretään taustakuva
    Surface::draw(surfTaustakuva,surfScreen,0,0);

    // Kirjotetaan polku
    Font::drawSolid(fontVerdana,surfScreen,0,0,clrRed,"Päävalikko - asetukset");

    // Valikkotekstit
    // Näppäinasetukset
    Font::drawSolid(fontVerdana,surfScreen,50,100,clrWhite,"Pelaajien näppäimet");

    // Mennään punasen pelaajan näppäinasetuksiin
    if(curOption == SETTINGS_OPTION_RED)
        Font::drawSolid(fontVerdana,surfScreen,50,120,clrOrange,"Punainen pelaaja");
    else
        Font::drawSolid(fontVerdana,surfScreen,50,120,clrYellow,"Punainen pelaaja");

    // Mennään sinisen pelaajan näppäinasetuksiin
    if(curOption == SETTINGS_OPTION_BLU)
        Font::drawSolid(fontVerdana,surfScreen,50,140,clrOrange,"Sininen pelaaja");
    else
        Font::drawSolid(fontVerdana,surfScreen,50,140,clrYellow,"Sininen pelaaja");

    // Yleiset asetukset
    Font::drawSolid(fontVerdana,surfScreen,50,180,clrWhite,"Yleiset asetukset");

    // Aseta koko näytölle
    if(curOption == SETTINGS_OPTION_FULLSCREEN)
    {
        if(fullscreen)
            Font::drawSolid(fontVerdana,surfScreen,50,200,clrOrange,"Koko näyttö: PÄÄLLÄ");
        else
            Font::drawSolid(fontVerdana,surfScreen,50,200,clrOrange,"Koko näyttö: POIS");
    }
    else
    {
        if(fullscreen)
            Font::drawSolid(fontVerdana,surfScreen,50,200,clrYellow,"Koko näyttö: PÄÄLLÄ");
        else
            Font::drawSolid(fontVerdana,surfScreen,50,200,clrYellow,"Koko näyttö: POIS");
    }

    // Pelin asetukset
    Font::drawSolid(fontVerdana,surfScreen,50,240,clrWhite,"Pelin asetukset (maksimiarvot, 1-99)");

    // Maksimierät
    if(curOption == SETTINGS_OPTION_ROUNDS)
    {
        Font::drawSolid(fontVerdana,surfScreen,50,260,clrOrange,"Erät:");
        Font::drawSolid(fontVerdana,surfScreen,150,260,clrOrange,intToString(maxRounds));
    }
    else
    {
        Font::drawSolid(fontVerdana,surfScreen,50,260,clrYellow,"Erät:");
        Font::drawSolid(fontVerdana,surfScreen,150,260,clrYellow,intToString(maxRounds));
    }

    // Maksimiaika
    if(curOption == SETTINGS_OPTION_TIME)
    {
        Font::drawSolid(fontVerdana,surfScreen,50,280,clrOrange,"Aika:");
        Font::drawSolid(fontVerdana,surfScreen,150,280,clrOrange,intToString(maxTime));
    }
    else
    {
        Font::drawSolid(fontVerdana,surfScreen,50,280,clrYellow,"Aika:");
        Font::drawSolid(fontVerdana,surfScreen,150,280,clrYellow,intToString(maxTime));
    }

    // Maksimimaalit
    if(curOption == SETTINGS_OPTION_SCORE)
    {
        Font::drawSolid(fontVerdana,surfScreen,50,300,clrOrange,"Maalit:");
        Font::drawSolid(fontVerdana,surfScreen,150,300,clrOrange,intToString(maxScore));
    }
    else
    {
        Font::drawSolid(fontVerdana,surfScreen,50,300,clrYellow,"Maalit:");
        Font::drawSolid(fontVerdana,surfScreen,150,300,clrYellow,intToString(maxScore));
    }

    // Lataa oletusasetukset
    if(curOption == SETTINGS_OPTION_DEFAULTS)
        Font::drawSolid(fontVerdana,surfScreen,50,340,clrOrange,"Palauta oletusasetukset");
    else
        Font::drawSolid(fontVerdana,surfScreen,50,340,clrYellow,"Palauta oletusasetukset");

    // Tallenna asetukset
    if(curOption == SETTINGS_OPTION_SAVE)
        Font::drawSolid(fontVerdana,surfScreen,50,380,clrOrange,"Tallenna ja poistu");
    else
        Font::drawSolid(fontVerdana,surfScreen,50,380,clrYellow,"Tallenna ja poistu");

    // Takasin
    if(curOption == SETTINGS_OPTION_BACK)
        Font::drawSolid(fontVerdana,surfScreen,50,400,clrOrange,"Poistu");
    else
        Font::drawSolid(fontVerdana,surfScreen,50,400,clrYellow,"Poistu");
}

void Game::renderMenuSettingsRed()
{
    // Piirretään taustakuva
    Surface::draw(surfTaustakuva,surfScreen,0,0);

    // Kirjotetaan polku
    Font::drawSolid(fontVerdana,surfScreen,0,0,clrRed,"Päävalikko - Asetukset - Punaisen pelaajan näppäimet");

    // Piirretään valinnat
    // Namiska eteen
    if(curOption == KEY_OPTION_FORWARD)
    {
        Font::drawSolid(fontVerdana,surfScreen,50,120,clrOrange,"Eteen:");
        Font::drawSolid(fontVerdana,surfScreen,170,120,clrOrange,SDL_GetKeyName(plrPunanen.getKeyForward()));
    }
    else
    {
        Font::drawSolid(fontVerdana,surfScreen,50,120,clrYellow,"Eteen:");
        Font::drawSolid(fontVerdana,surfScreen,170,120,clrYellow,SDL_GetKeyName(plrPunanen.getKeyForward()));
    }

    // Namiska taa
    if(curOption == KEY_OPTION_BACKWARD)
    {
        Font::drawSolid(fontVerdana,surfScreen,50,140,clrOrange,"Taakse:");
        Font::drawSolid(fontVerdana,surfScreen,170,140,clrOrange,SDL_GetKeyName(plrPunanen.getKeyBackward()));
    }
    else
    {
        Font::drawSolid(fontVerdana,surfScreen,50,140,clrYellow,"Taakse:");
        Font::drawSolid(fontVerdana,surfScreen,170,140,clrYellow,SDL_GetKeyName(plrPunanen.getKeyBackward()));
    }

    // Namiska vasemmalle
    if(curOption == KEY_OPTION_LEFT)
    {
        Font::drawSolid(fontVerdana,surfScreen,50,160,clrOrange,"Vasen:");
        Font::drawSolid(fontVerdana,surfScreen,170,160,clrOrange,SDL_GetKeyName(plrPunanen.getKeyLeft()));
    }
    else
    {
        Font::drawSolid(fontVerdana,surfScreen,50,160,clrYellow,"Vasen:");
        Font::drawSolid(fontVerdana,surfScreen,170,160,clrYellow,SDL_GetKeyName(plrPunanen.getKeyLeft()));
    }

    // Namiska oikealle
    if(curOption == KEY_OPTION_RIGHT)
    {
        Font::drawSolid(fontVerdana,surfScreen,50,180,clrOrange,"Oikea:");
        Font::drawSolid(fontVerdana,surfScreen,170,180,clrOrange,SDL_GetKeyName(plrPunanen.getKeyRight()));
    }
    else
    {
        Font::drawSolid(fontVerdana,surfScreen,50,180,clrYellow,"Oikea:");
        Font::drawSolid(fontVerdana,surfScreen,170,180,clrYellow,SDL_GetKeyName(plrPunanen.getKeyRight()));
    }

    // Namiska ampukaa
    if(curOption == KEY_OPTION_SHOOT)
    {
        Font::drawSolid(fontVerdana,surfScreen,50,200,clrOrange,"Laukaise:");
        Font::drawSolid(fontVerdana,surfScreen,170,200,clrOrange,SDL_GetKeyName(plrPunanen.getKeyShoot()));
    }
    else
    {
        Font::drawSolid(fontVerdana,surfScreen,50,200,clrYellow,"Laukaise:");
        Font::drawSolid(fontVerdana,surfScreen,170,200,clrYellow,SDL_GetKeyName(plrPunanen.getKeyShoot()));
    }

    // Paluu asetuksiin
    if(curOption == KEY_OPTION_BACK)
        Font::drawSolid(fontVerdana,surfScreen,50,400,clrOrange,"Takaisin");
    else
        Font::drawSolid(fontVerdana,surfScreen,50,400,clrYellow,"Takaisin");
}

void Game::renderMenuSettingsBlu()
{
    // Piirretään taustakuva
    Surface::draw(surfTaustakuva,surfScreen,0,0);

    // Kirjotetaan polku
    Font::drawSolid(fontVerdana,surfScreen,0,0,clrRed,"Päävalikko - Asetukset - Punaisen pelaajan näppäimet");

    // Piirretään valinnat
    // Namiska eteen
    if(curOption == KEY_OPTION_FORWARD)
    {
        Font::drawSolid(fontVerdana,surfScreen,50,120,clrOrange,"Eteen:");
        Font::drawSolid(fontVerdana,surfScreen,170,120,clrOrange,SDL_GetKeyName(plrSininen.getKeyForward()));
    }
    else
    {
        Font::drawSolid(fontVerdana,surfScreen,50,120,clrYellow,"Eteen:");
        Font::drawSolid(fontVerdana,surfScreen,170,120,clrYellow,SDL_GetKeyName(plrSininen.getKeyForward()));
    }

    // Namiska taa
    if(curOption == KEY_OPTION_BACKWARD)
    {
        Font::drawSolid(fontVerdana,surfScreen,50,140,clrOrange,"Taakse:");
        Font::drawSolid(fontVerdana,surfScreen,170,140,clrOrange,SDL_GetKeyName(plrSininen.getKeyBackward()));
    }
    else
    {
        Font::drawSolid(fontVerdana,surfScreen,50,140,clrYellow,"Taakse:");
        Font::drawSolid(fontVerdana,surfScreen,170,140,clrYellow,SDL_GetKeyName(plrSininen.getKeyBackward()));
    }

    // Namiska vasemmalle
    if(curOption == KEY_OPTION_LEFT)
    {
        Font::drawSolid(fontVerdana,surfScreen,50,160,clrOrange,"Vasen:");
        Font::drawSolid(fontVerdana,surfScreen,170,160,clrOrange,SDL_GetKeyName(plrSininen.getKeyLeft()));
    }
    else
    {
        Font::drawSolid(fontVerdana,surfScreen,50,160,clrYellow,"Vasen:");
        Font::drawSolid(fontVerdana,surfScreen,170,160,clrYellow,SDL_GetKeyName(plrSininen.getKeyLeft()));
    }

    // Namiska oikealle
    if(curOption == KEY_OPTION_RIGHT)
    {
        Font::drawSolid(fontVerdana,surfScreen,50,180,clrOrange,"Oikea:");
        Font::drawSolid(fontVerdana,surfScreen,170,180,clrOrange,SDL_GetKeyName(plrSininen.getKeyRight()));
    }
    else
    {
        Font::drawSolid(fontVerdana,surfScreen,50,180,clrYellow,"Oikea:");
        Font::drawSolid(fontVerdana,surfScreen,170,180,clrYellow,SDL_GetKeyName(plrSininen.getKeyRight()));
    }

    // Namiska ampukaa
    if(curOption == KEY_OPTION_SHOOT)
    {
        Font::drawSolid(fontVerdana,surfScreen,50,200,clrOrange,"Laukaise:");
        Font::drawSolid(fontVerdana,surfScreen,170,200,clrOrange,SDL_GetKeyName(plrSininen.getKeyShoot()));
    }
    else
    {
        Font::drawSolid(fontVerdana,surfScreen,50,200,clrYellow,"Laukaise:");
        Font::drawSolid(fontVerdana,surfScreen,170,200,clrYellow,SDL_GetKeyName(plrSininen.getKeyShoot()));
    }

    // Paluu asetuksiin
    if(curOption == KEY_OPTION_BACK)
        Font::drawSolid(fontVerdana,surfScreen,50,400,clrOrange,"Takaisin");
    else
        Font::drawSolid(fontVerdana,surfScreen,50,400,clrYellow,"Takaisin");
}

void Game::renderGame()
{
    // Piirretään kenttä ja yläpalkki
    Surface::draw(surfPalkki,surfScreen,0,0);
    Surface::draw(surfKentta,surfScreen,0,60);

    // Piirretään muuttujat
    // Sinisen pelaajan pisteet
    Font::drawLinesSolid(fontVerdana,surfScreen,50,10,clrBlue,ALIGN_CENTER,VALIGN_TOP,"Pisteet");
    Font::drawLinesSolid(fontVerdana,surfScreen,50,30,clrWhite,ALIGN_CENTER,VALIGN_TOP,intToString(siniScore));

    // Punasen pelaajan pisteet
    Font::drawLinesSolid(fontVerdana,surfScreen,590,10,clrRed,ALIGN_CENTER,VALIGN_TOP,"Pisteet");
    Font::drawLinesSolid(fontVerdana,surfScreen,590,30,clrWhite,ALIGN_CENTER,VALIGN_TOP,intToString(punaScore));

    // Aika
    Font::drawLinesSolid(fontVerdana,surfScreen,280,10,clrGreen,ALIGN_CENTER,VALIGN_TOP,"Aika");
    std::stringstream tempTime;
    tempTime<<curMinutes<<":"<<curSeconds;
    Font::drawLinesSolid(fontVerdana,surfScreen,280,30,clrWhite,ALIGN_CENTER,VALIGN_TOP,tempTime.str());

    // Erä
    Font::drawLinesSolid(fontVerdana,surfScreen,360,10,clrGreen,ALIGN_CENTER,VALIGN_TOP,"Erä");
    std::stringstream tempRound;
    tempRound<<curRound<<"/"<<maxRounds;
    Font::drawLinesSolid(fontVerdana,surfScreen,360,30,clrWhite,ALIGN_CENTER,VALIGN_TOP,tempRound.str());

    // Piirretään kiekko
    if(puck.isAlive()) puck.draw(surfScreen);

    // Piirretään maalivahdit
    goalieSini.draw(surfScreen);
    goaliePuna.draw(surfScreen);

    // Piirretään maalit
    Surface::draw(surfSiniMaali,surfScreen,58,230);
    Surface::draw(surfPunaMaali,surfScreen,542,230);

    // Piirretään pelaajat
    plrSininen.draw(surfScreen);
    plrPunanen.draw(surfScreen);

    // Piirretään voimamittarit(jos lyödään)
    if(plrSininen.isShooting()) plrSininen.drawPowerMeter(surfScreen);
    if(plrPunanen.isShooting()) plrPunanen.drawPowerMeter(surfScreen);

    // Kirjotetaan et maali tehty jos on
    if(goalMade) Font::drawLinesSolid(fontVerdana,surfScreen,320,240,clrBlack,ALIGN_CENTER,VALIGN_MIDDLE,"MAALI!");
}

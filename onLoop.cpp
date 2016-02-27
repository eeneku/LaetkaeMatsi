#include"..\inc\Game.hpp"

void Game::onLoop()
{
    // P‰ivitet‰‰n framelaskuri
    FPS::update();

    // Vaihdellaan tiloja
    // Peli k‰y
    if(state == GAME_RUNNING)
    {
        // P‰ivitet‰‰n aika
        if(!goalMade && (SDL_GetTicks() - gameTimer) > 1000)
        {
            // Jep, sekkoja alemmas
            if(--curSeconds < 0)
            {
                // Minuutteja alemmas
                if(--curMinutes < 0)
                {
                    // AIKA LOPPU! UUSI ERƒ!
                    if(++curRound > maxRounds)
                    {
                        // ERƒT LOPPU! PELI OHI! Katotaan voittaja
                        if(siniScore > punaScore)
                            winner = SININEN;
                        else if(punaScore > siniScore)
                            winner = PUNANEN;
                        else
                            winner = TASURI;

                        // Lopetetaan peli
                        changeState(GAME_OVER);
                    }
                    else
                    {
                        // Lopetetaan er‰ ja alotetaan uus
                        changeState(GAME_ROUND_END);
                    }
                }
                else curSeconds += 60;
            }

            gameTimer = SDL_GetTicks();
        }
        else if(goalMade)
        {
            // Katotaan joko alotetaan uus er‰
            if((SDL_GetTicks() - helpTimer) > 2000)
            {
                // Joo
                goalMade = false;
                resetInstances();

                // Alotetaan
                changeState(GAME_START);
            }
        }

        // P‰ivitet‰‰n pelaajat
        plrSininen.update();
        plrSininen.checkCollisions(plrPunanen,puck,goalieSini,goaliePuna);
        plrPunanen.update();
        plrPunanen.checkCollisions(plrSininen,puck,goalieSini,goaliePuna);

        // P‰ivitet‰‰n kiekko
        if(puck.isAlive())
        {
            puck.update();

            int t = puck.checkCollisions(goalieSini,goaliePuna);

            // Tarkastetaan vaan jos maalia ei oo tehty
            if(!goalMade)
            {
                if(t == SININEN)
                {
                    // Punanen teki maalin!
                    punaScore++;
                    goalMade = true;

                    // Otetaan aika talteen
                    timePassed = SDL_GetTicks() - gameTimer;

                    // Laitetaan helppiaika
                    helpTimer = SDL_GetTicks();
                }
                else if(t == PUNANEN)
                {
                    // Sininen teki maalin!
                    siniScore++;
                    goalMade = true;

                    // Otetaan aika talteen
                    timePassed = SDL_GetTicks() - gameTimer;

                    // Laitetaan helppiaika
                    helpTimer = SDL_GetTicks();
                }
            }
        }

        // P‰ivitet‰‰n maalivahdit
        if(plrSininen.hasPuck())
        {
            goalieSini.update(plrSininen.getCenterY());
            goaliePuna.update(plrSininen.getCenterY());
        }
        else if(plrPunanen.hasPuck())
        {
            goalieSini.update(plrPunanen.getCenterY());
            goaliePuna.update(plrPunanen.getCenterY());
        }
        else
        {
            goalieSini.update(puck.getCenterY());
            goaliePuna.update(puck.getCenterY());
        }
    }

    // Peli on paussilla
    else if(state == GAME_PAUSED)
    {
    }

    // Alotus
    else if(state == GAME_START)
    {
        // Katotaan kun laskuri on menny nollille
        if((SDL_GetTicks() - helpTimer) > 2000)
        {
            gameTimer = SDL_GetTicks() - timePassed;
            state = GAME_RUNNING;
        }
    }

    // Er‰ ohi
    else if(state == GAME_ROUND_END)
    {
    }

    // Peli ohi
    else if(state == GAME_OVER)
    {
    }

    // Peli on p‰‰valikossa
    else if(state == MENU_MAIN)
    {
    }

    // Peli on asetusvalikossa
    else if(state == MENU_SETTINGS)
    {
    }
}

void Game::changeState(int nState)
{
    // Otetaan ensin vanha talteen
    prevState = state;

    // Sitten asetetaan uusi!
    state = nState;

    // Ja jos tila on joku valikoista, niin asetetaan rajat
    if(state == MENU_MAIN)
    {
        // P‰‰valikko
        curOption = MENU_OPTION_GAME;
        maxOptions = MENU_OPTIONS;
    }
    else if(state == MENU_SETTINGS)
    {
        // Asetusvalikko
        curOption = SETTINGS_OPTION_RED;
        maxOptions = SETTINGS_OPTIONS;
    }
    else if(state == GAME_PAUSED)
    {
        // Paussivalikko
        curOption = PAUSED_OPTION_CONTINUE;
        maxOptions = PAUSED_OPTIONS;
    }
    else if(state == MENU_SETTINGS_RED)
    {
        // Punasen pelaajan n‰pp‰inasetukset
        curOption = KEY_OPTION_FORWARD;
        maxOptions = KEY_OPTIONS;
    }
    else if(state == MENU_SETTINGS_BLU)
    {
        // Sinisen pelaajan n‰pp‰inasetukset
        curOption = KEY_OPTION_FORWARD;
        maxOptions = KEY_OPTIONS;
    }
    else if(state == GAME_OVER)
    {
        // Peli ohi
        curOption = OVER_OPTION_NEW;
        maxOptions = OVER_OPTIONS;
    }
    else if(state == GAME_ROUND_END)
    {
        // Er‰ ohi
        curOption = END_OPTION_CONTINUE;
        maxOptions = END_OPTIONS;
    }
    else if(state == GAME_START)
    {
        // Laitetaan laskuri
        helpTimer = SDL_GetTicks();
    }
}

void Game::resetInstances()
{
    // Resetoi oliot
    // Pelaajat
    plrSininen.resetVariables();
    plrPunanen.resetVariables();

    // Kiekko
    puck.resetVariables();

    // Molarit
    goalieSini.setPosition(goalieSini.getDefaultPosition());
    goaliePuna.setPosition(goaliePuna.getDefaultPosition());
}

void Game::resetScore()
{
    // Resetoi pisteet
    siniScore = 0;
    punaScore = 0;
}

void Game::resetTime()
{
    // Resetoi ajan
    curMinutes = maxTime;
    curSeconds = 0;
    timePassed = 0;
}

void Game::resetRounds()
{
    // Resetoi er‰t
    curRound = 1;
}

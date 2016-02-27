#include"..\inc\Game.hpp"

// ÷‰‰ tarkastetaan tapahtumia?
void Game::onEvent(SDL_Event &event)
{
    Event::onEvent(event);
}

// Kutsutaan kun sammutetaan
void Game::onExit()
{
    running = false;
}

// Tarkastetaan onko nappi alhaalla
void Game::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    // Vaihdellaan tiloja
    // Peli k‰y
    if(state == GAME_RUNNING)
    {
        if(sym == SDLK_ESCAPE || sym == SDLK_p)
        {
            // Otetaan aika talteen ett‰ saadaan jatkettua sitten siit‰
            timePassed = SDL_GetTicks() - gameTimer;

            // Esci‰ tai p:t‰ painettu, paussille
            changeState(GAME_PAUSED);
        }

        // Tarkastetaan pelaajien n‰pp‰imet
        // Punanen
        else if(sym == plrPunanen.getKeyForward())
        {
            // Menn‰‰n eteenp‰in
            plrPunanen.moveForward(true);
        }
        else if(sym == plrPunanen.getKeyBackward())
        {
            // Menn‰‰n taaksep‰in
            plrPunanen.moveBackwards(true);
        }
        else if(sym == plrPunanen.getKeyRight())
        {
            // K‰‰nnyt‰‰n oikealle
            plrPunanen.turnRight(true);
        }
        else if(sym == plrPunanen.getKeyLeft())
        {
            // K‰‰nnyt‰‰n vasemmalle
            plrPunanen.turnLeft(true);
        }
        else if(sym == plrPunanen.getKeyShoot())
        {
            // Ammutaan!
            if(plrPunanen.hasPuck()) plrPunanen.shoot(true);
            else plrPunanen.takePuck(true);
        }

        // Sininen
        else if(sym == plrSininen.getKeyForward())
        {
            // Menn‰‰n eteenp‰in
            plrSininen.moveForward(true);
        }
        else if(sym == plrSininen.getKeyBackward())
        {
            // Menn‰‰n taaksep‰in
            plrSininen.moveBackwards(true);
        }
        else if(sym == plrSininen.getKeyRight())
        {
            // K‰‰nnyt‰‰n oikealle
            plrSininen.turnRight(true);
        }
        else if(sym == plrSininen.getKeyLeft())
        {
            // K‰‰nnyt‰‰n vasemmalle
            plrSininen.turnLeft(true);
        }
        else if(sym == plrSininen.getKeyShoot())
        {
            // Ammutaan!
            if(plrSininen.hasPuck()) plrSininen.shoot(true);
            else plrSininen.takePuck(true);
        }
    }

    // Peli on paussilla
    else if(state == GAME_PAUSED)
    {
        if(sym == SDLK_UP)
        {
            // Vaihdetaan valintaa alasp‰in
            if(--curOption < 1) curOption = maxOptions;
        }
        else if(sym == SDLK_DOWN)
        {
            // Vaihdetaan valintaa alasp‰in
            if(++curOption > maxOptions) curOption = 1;
        }
        else if(sym == SDLK_RETURN)
        {
            if(curOption == PAUSED_OPTION_CONTINUE)
            {
                // Jos tila on peliin niin p‰ivitet‰‰n aika
                if(prevState == GAME_RUNNING)
                    gameTimer = SDL_GetTicks() - timePassed;

                // Jatketaan peli‰
                changeState(prevState);
            }
            else if(curOption == PAUSED_OPTION_MENU)
            {
                // P‰‰valikkoon
                changeState(MENU_MAIN);
            }

        }
        else if(sym == SDLK_ESCAPE || sym == SDLK_p)
        {
            // Jos tila on peliin niin p‰ivitet‰‰n aika
            if(prevState == GAME_RUNNING)
                gameTimer = SDL_GetTicks() - timePassed;

            // Takaisin peliin
            changeState(prevState);
        }
    }

    // Aloitetaan peli, er‰
    else if(state == GAME_START)
    {
        if(sym == SDLK_ESCAPE || sym == SDLK_p)
        {
            // Menn‰‰n paussille
            changeState(GAME_PAUSED);
        }
    }

    // Er‰ ohi
    else if(state == GAME_ROUND_END)
    {
        if(sym == SDLK_ESCAPE)
        {
            // P‰‰valikkoon
            changeState(MENU_MAIN);
        }

        else if(sym == SDLK_UP)
        {
            // Vaihdetaan valintaa alasp‰in
            if(--curOption < 1) curOption = maxOptions;
        }
        else if(sym == SDLK_DOWN)
        {
            // Vaihdetaan valintaa alasp‰in
            if(++curOption > maxOptions) curOption = 1;
        }
        else if(sym == SDLK_RETURN)
        {
            // Mik‰ valinta
            if(curOption == END_OPTION_CONTINUE)
            {
                // Menn‰‰n peliin
                resetInstances();
                resetTime();
                changeState(GAME_START);
            }
            else if(curOption == END_OPTION_MENU)
            {
                // Takasin valikkoon
                changeState(MENU_MAIN);
            }
        }
    }

    // Peli ohi
    else if(state == GAME_OVER)
    {
        if(sym == SDLK_ESCAPE)
        {
            // P‰‰valikkoon
            changeState(MENU_MAIN);
        }

        else if(sym == SDLK_UP)
        {
            // Vaihdetaan valintaa alasp‰in
            if(--curOption < 1) curOption = maxOptions;
        }
        else if(sym == SDLK_DOWN)
        {
            // Vaihdetaan valintaa alasp‰in
            if(++curOption > maxOptions) curOption = 1;
        }
        else if(sym == SDLK_RETURN)
        {
            // Mik‰ valinta
            if(curOption == OVER_OPTION_NEW)
            {
                // Menn‰‰n peliin
                resetAll();
                changeState(GAME_START);
            }
            else if(curOption == OVER_OPTION_MENU)
            {
                // Takasin valikkoon
                changeState(MENU_MAIN);
            }
        }
    }

    // Peli on p‰‰valikossa
    else if(state == MENU_MAIN)
    {
        if(sym == SDLK_ESCAPE)
        {
            // Sammutetaan peli
            onExit();
        }
        else if(sym == SDLK_UP)
        {
            // Vaihdetaan valintaa alasp‰in
            if(--curOption < 1) curOption = maxOptions;
        }
        else if(sym == SDLK_DOWN)
        {
            // Vaihdetaan valintaa alasp‰in
            if(++curOption > maxOptions) curOption = 1;
        }
        else if(sym == SDLK_RETURN)
        {
            // Mik‰ valinta
            if(curOption == MENU_OPTION_GAME)
            {
                // Menn‰‰n peliin
                resetAll();
                changeState(GAME_START);
            }
            else if(curOption == MENU_OPTION_SETTINGS)
            {
                // Menn‰‰n asetuksiin
                changeState(MENU_SETTINGS);
            }
            else if(curOption == MENU_OPTION_EXIT)
            {
                // Sammutetaan peli
                onExit();
            }
        }
    }

    // Peli on asetusvalikossa
    else if(state == MENU_SETTINGS)
    {
        if(sym == SDLK_ESCAPE)
        {
            // Palataan valikkoon
            changeState(MENU_MAIN);
        }
        else if(sym == SDLK_LEFT)
        {
            if(curOption == SETTINGS_OPTION_ROUNDS)
            {
                // V‰hennet‰‰n eri‰
                if(--maxRounds < 1) maxRounds = 1;
            }
            else if(curOption == SETTINGS_OPTION_TIME)
            {
                // V‰hennet‰‰n aikaa
                if(--maxTime < 1) maxTime = 1;
            }
            else if(curOption == SETTINGS_OPTION_SCORE)
            {
                // V‰hennet‰‰n pisteit‰
                if(--maxScore < 1) maxScore = 1;
            }
        }
        else if(sym == SDLK_RIGHT)
        {
            if(curOption == SETTINGS_OPTION_ROUNDS)
            {
                // Lis‰t‰‰n eri‰
                if(++maxRounds > 99) maxRounds = 99;
            }
            else if(curOption == SETTINGS_OPTION_TIME)
            {
                // Lis‰t‰‰n aikaa
                if(++maxTime > 99) maxTime = 99;
            }
            else if(curOption == SETTINGS_OPTION_SCORE)
            {
                // Lis‰t‰‰n pisteit‰
                if(++maxScore > 99) maxScore = 99;
            }
        }
        else if(sym == SDLK_UP)
        {
            // Vaihdetaan valintaa ylˆsp‰in
            if(--curOption < 1) curOption = maxOptions;
        }
        else if(sym == SDLK_DOWN)
        {
            // Vaihdetaan valintaa alasp‰in
            if(++curOption > maxOptions) curOption = 1;
        }
        else if(sym == SDLK_RETURN)
        {
            if(curOption == SETTINGS_OPTION_RED)
            {
                // Menn‰‰n punasen pelaajan n‰pp‰inasetuksiin
                changeState(MENU_SETTINGS_RED);
            }
            else if(curOption == SETTINGS_OPTION_BLU)
            {
                // Menn‰‰n punasen pelaajan n‰pp‰inasetuksiin
                changeState(MENU_SETTINGS_BLU);
            }
            else if(curOption == SETTINGS_OPTION_FULLSCREEN)
            {
                // Vaihdetaan fullscreenia
                if(fullscreen)
                    fullscreen = false;
                else
                    fullscreen = true;
            }
            else if(curOption == SETTINGS_OPTION_SAVE)
            {
                // Tallennetaan asetukset
                settingsSaved = saveSettings("settings.txt");
                changeState(MENU_MAIN);
            }
            else if(curOption == SETTINGS_OPTION_DEFAULTS)
            {
                // Asetetaan oletusasetukset
                defaultSettings();
            }
            else if(curOption == SETTINGS_OPTION_BACK)
            {
                // Palataan edelliseen tilaan
                changeState(MENU_MAIN);
            }
        }
    }

    // Peli on punasen pelaajan n‰pp‰inasetuksissa
    else if(state == MENU_SETTINGS_RED)
    {
        if(sym == SDLK_ESCAPE)
        {
            // Palataan edelliseen
            changeState(MENU_SETTINGS);
        }
        else if(sym == SDLK_UP)
        {
            // Vaihdetaan valintaa ylˆsp‰in
            if(--curOption < 1) curOption = maxOptions;
        }
        else if(sym == SDLK_DOWN)
        {
            // Vaihdetaan valintaa alasp‰in
            if(++curOption > maxOptions) curOption = 1;
        }
        else if(sym == SDLK_RETURN)
        {
            if(curOption == KEY_OPTION_FORWARD || curOption == KEY_OPTION_BACKWARD || curOption == KEY_OPTION_LEFT || curOption == KEY_OPTION_RIGHT || curOption == KEY_OPTION_SHOOT)
            {
                changeState(MENU_SETTINGS_SET_KEY);
            }
            else if(curOption == KEY_OPTION_BACK)
            {
                // Takasin valikkoon
                changeState(MENU_SETTINGS);
            }
        }
    }

    // Peli on sinisen pelaajan n‰pp‰inasetuksissa
    else if(state == MENU_SETTINGS_BLU)
    {
        if(sym == SDLK_ESCAPE)
        {
            // Palataan edelliseen
            changeState(MENU_SETTINGS);
        }
        else if(sym == SDLK_UP)
        {
            // Vaihdetaan valintaa ylˆsp‰in
            if(--curOption < 1) curOption = maxOptions;
        }
        else if(sym == SDLK_DOWN)
        {
            // Vaihdetaan valintaa alasp‰in
            if(++curOption > maxOptions) curOption = 1;
        }
        else if(sym == SDLK_RETURN)
        {
            if(curOption == KEY_OPTION_FORWARD || curOption == KEY_OPTION_BACKWARD || curOption == KEY_OPTION_LEFT || curOption == KEY_OPTION_RIGHT || curOption == KEY_OPTION_SHOOT)
            {
                changeState(MENU_SETTINGS_SET_KEY);
            }
            else if(curOption == KEY_OPTION_BACK)
            {
                // Takasin valikkoon
                changeState(MENU_SETTINGS);
            }
        }
    }

    // Vaihdetaan nappi
    else if(state == MENU_SETTINGS_SET_KEY)
    {
        if(sym == SDLK_ESCAPE)
        {
            // Menn‰‰n takasin tekem‰tt‰ mit‰‰n (eli kaikki muut napit paitsi escape k‰y >_>)
            changeState(prevState);
        }
        else
        {
            // Noni! Katotaan napit.
            if(prevState == MENU_SETTINGS_RED)
            {
                // Punanen oli vuoros
                switch(curOption)
                {
                    case KEY_OPTION_FORWARD :
                    {
                        plrPunanen.setKeyForward(sym);
                        break;
                    }
                    case KEY_OPTION_BACKWARD :
                    {
                        plrPunanen.setKeyBackward(sym);
                        break;
                    }
                    case KEY_OPTION_LEFT :
                    {
                        plrPunanen.setKeyLeft(sym);
                        break;
                    }
                    case KEY_OPTION_RIGHT :
                    {
                        plrPunanen.setKeyRight(sym);
                        break;
                    }
                    case KEY_OPTION_SHOOT :
                    {
                        plrPunanen.setKeyShoot(sym);
                        break;
                    }
                    default : break;
                }
            }
            else if(prevState == MENU_SETTINGS_BLU)
            {
                // Sininen oli vuoros
                switch(curOption)
                {
                    case KEY_OPTION_FORWARD :
                    {
                        plrSininen.setKeyForward(sym);
                        break;
                    }
                    case KEY_OPTION_BACKWARD :
                    {
                        plrSininen.setKeyBackward(sym);
                        break;
                    }
                    case KEY_OPTION_LEFT :
                    {
                        plrSininen.setKeyLeft(sym);
                        break;
                    }
                    case KEY_OPTION_RIGHT :
                    {
                        plrSininen.setKeyRight(sym);
                        break;
                    }
                    case KEY_OPTION_SHOOT :
                    {
                        plrSininen.setKeyShoot(sym);
                        break;
                    }
                    default : break;
                }
            }

            // Ja sit palataan edelliseen tilaan
            changeState(prevState);
        }
    }
}

void Game::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    // Vaihdellaan tiloja
    // Peli k‰y
    if(state == GAME_RUNNING)
    {
        // Tarkastetaan pelaajien n‰pp‰imet
        // Punanen
        if(sym == plrPunanen.getKeyForward())
        {
            // Menn‰‰n eteenp‰in
            plrPunanen.moveForward(false);
        }
        else if(sym == plrPunanen.getKeyBackward())
        {
            // Menn‰‰n taaksep‰in
            plrPunanen.moveBackwards(false);
        }
        else if(sym == plrPunanen.getKeyRight())
        {
            // K‰‰nnyt‰‰n oikealle
            plrPunanen.turnRight(false);
        }
        else if(sym == plrPunanen.getKeyLeft())
        {
            // K‰‰nnyt‰‰n vasemmalle
            plrPunanen.turnLeft(false);
        }
        else if(sym == plrPunanen.getKeyShoot())
        {
            // Ammutaan!
            if(plrPunanen.hasPuck()) plrPunanen.launch(puck);
            else plrPunanen.takePuck(false);
        }

        // Sininen
        else if(sym == plrSininen.getKeyForward())
        {
            // Menn‰‰n eteenp‰in
            plrSininen.moveForward(false);
        }
        else if(sym == plrSininen.getKeyBackward())
        {
            // Menn‰‰n taaksep‰in
            plrSininen.moveBackwards(false);
        }
        else if(sym == plrSininen.getKeyRight())
        {
            // K‰‰nnyt‰‰n oikealle
            plrSininen.turnRight(false);
        }
        else if(sym == plrSininen.getKeyLeft())
        {
            // K‰‰nnyt‰‰n vasemmalle
            plrSininen.turnLeft(false);
        }
        else if(sym == plrSininen.getKeyShoot())
        {
            // Ammutaan!
            if(plrSininen.hasPuck()) plrSininen.launch(puck);
            else plrSininen.takePuck(false);
        }
    }

    // Peli on paussilla
    else if(state == GAME_PAUSED)
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

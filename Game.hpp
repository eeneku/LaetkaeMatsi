#ifndef __GAME_HPP__
#define __GAME_HPP__

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<cmath>
#include<cstdio>
#include"SDL.h"
#include"SDL_mixer.h"
#include"SDL_image.h"
#include"SDL_ttf.h"
#include"..\inc\version.hpp"
#include"..\inc\Sound.hpp"
#include"..\inc\Surface.hpp"
#include"..\inc\Font.hpp"
#include"..\inc\Event.hpp"
#include"..\inc\Sprite.hpp"
#include"..\inc\FPS.hpp"
#include"..\inc\Player.hpp"
#include"..\inc\Goalie.hpp"
#include"..\inc\Puck.hpp"

// Pelin tilat
#define MENU_MAIN 10
#define MENU_SETTINGS 11
#define MENU_SETTINGS_BLU 12
#define MENU_SETTINGS_RED 13
#define MENU_SETTINGS_SET_KEY 14
#define GAME_RUNNING 20
#define GAME_PAUSED 21
#define GAME_OVER 22
#define GAME_START 23
#define GAME_ROUND_END 24

// Peliohivalikon valinnet
#define OVER_OPTIONS 2
#define OVER_OPTION_NEW 1
#define OVER_OPTION_MENU 2

// Eräohivalikon valinnat
#define END_OPTIONS 2
#define END_OPTION_CONTINUE 1
#define END_OPTION_MENU 2

// Päävalikon valinnat
#define MENU_OPTIONS 3
#define MENU_OPTION_GAME 1
#define MENU_OPTION_SETTINGS 2
#define MENU_OPTION_EXIT 3

// Asetusvalikon valinnat
#define SETTINGS_OPTIONS 9
#define SETTINGS_OPTION_RED 1
#define SETTINGS_OPTION_BLU 2
#define SETTINGS_OPTION_FULLSCREEN 3
#define SETTINGS_OPTION_ROUNDS 4
#define SETTINGS_OPTION_TIME 5
#define SETTINGS_OPTION_SCORE 6
#define SETTINGS_OPTION_DEFAULTS 7
#define SETTINGS_OPTION_SAVE 8
#define SETTINGS_OPTION_BACK 9

// Paussivalikon valinnat
#define PAUSED_OPTIONS 3
#define PAUSED_OPTION_CONTINUE 1
#define PAUSED_OPTION_MENU 2

// Pelaajan näppäinten valinnat
#define KEY_OPTIONS 6
#define KEY_OPTION_FORWARD 1
#define KEY_OPTION_BACKWARD 2
#define KEY_OPTION_LEFT 3
#define KEY_OPTION_RIGHT 4
#define KEY_OPTION_SHOOT 5
#define KEY_OPTION_BACK 6

// Näytön jutut
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

// Pelaajat
#define SININEN 1
#define PUNANEN 2

// Tasapeli tuli!
#define TASURI 10

// Peliluokka
class Game : public Event
{
    private:
    // Näyttöpinta ja muuttujat
    SDL_Surface * surfScreen;
    bool fullscreen;

    // Pelin tilamuuttuja
    int state;
    int prevState; // Aiemmpi tila

    // Pyöriikö ohjelma
    bool running;

    // Perusmuuttujat
    int maxScore;
    int maxTime;
    float gameTimer;
    float helpTimer;
    float timePassed;
    float curTime;
    int curSeconds;
    int curMinutes;
    int siniScore;
    int punaScore;
    int maxRounds;
    int curRound;
    int winner;
    int curOption;
    int maxOptions;
    bool settingsSaved;
    bool goalMade;

    // Grafiikat
    SDL_Surface * surfKentta;
    SDL_Surface * surfSininen;
    SDL_Surface * surfPunanen;
    SDL_Surface * surfSiniMolari;
    SDL_Surface * surfPunaMolari;
    SDL_Surface * surfKiekko;
    SDL_Surface * surfPalkki;
    SDL_Surface * surfTaustakuva;
    SDL_Surface * surfSiniMaali;
    SDL_Surface * surfPunaMaali;
    SDL_Surface * surfKuvake;

    // Äänet

    // Musiikit

    // Fontit
    TTF_Font * fontVerdana;

    // Oliot
    Player plrSininen;
    Player plrPunanen;
    Puck puck;
    Goalie goalieSini;
    Goalie goaliePuna;

    public:
    // Päämetodit
    Game();
    bool onInit();
    void onLoop();
    void onEvent(SDL_Event &event);
    void onCleanup();
    void onRender();
    int onExecute();

    // Muut
    bool initSettings(std::string path); // Ladataan asetukset!
    void defaultSettings(); // Asettaa oletusasetukset jos jostain kumman syystä vanhoja ei saa ladattua!
    bool saveSettings(std::string path); // Tallennetaan nykyiset asetukset tiedostoon!
    void changeState(int nState);
    void resetTime();
    void resetScore();
    void resetRounds();
    void resetInstances(); // Palauttaa oliot alkuperäisiin paikkoihinsa VVTU
    void resetAll() { resetTime(); resetScore(); resetRounds(); resetInstances(); } // resettaa kaikki jutut
    void renderGame();
    void renderGamePaused();
    void renderGameRoundEnd();
    void renderGameStart();
    void renderGameOver();
    void renderMenuMain();
    void renderMenuSettings();
    void renderMenuSettingsRed();
    void renderMenuSettingsBlu();
    std::string intToString(int n); // Palauttaa annetun int-muuttujan stringinä!

    // Tapahtumat
    void onExit();
    void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
    void onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
};

#endif

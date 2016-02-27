#include"..\inc\Game.hpp"

bool Game::onInit()
{
    // Alustetaan SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("....ERROR: Failed to initialize SDL: %s\n",SDL_GetError());
        return 0;
    } else printf("....SDL initialized succesfully \n");

    // Alustetaan SDL_TTF
    if(TTF_Init() < 0)
    {
        printf("...ERROR: Failed to initialize SDL_TTF\n");
        return 0;
    } printf("....SDL_TTF initialized succesfully \n");

    // Alustetaan SDL_Mixer
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024) < 0)
    {
        printf("....ERROR: Failed to initialize SDL_Mixer\n");
        return 0;
    } printf("....SDL_Mixer initialized succesfully \n");

    // Ladataan asetukset
    // Jos ei onnistu, niin pistetään oletusasetukset
    if(!initSettings("settings.txt"))
        defaultSettings();

    // Asetetaan näyttöpinta
    // Jos kokonäyttö niin pistetään, muuten ei
    if(fullscreen)
        surfScreen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    else
        surfScreen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_HWSURFACE | SDL_DOUBLEBUF);

    // Piilotetaan kursori
    SDL_ShowCursor(0);

    // Unicode käyttöön!
    SDL_EnableUNICODE(1);

    SDL_EnableKeyRepeat(0,SDL_DEFAULT_REPEAT_INTERVAL);

    // Alustetaan randomisaattori ajan mukaan
    srand(time(NULL));

    // Ladataan grafiikat
    surfKentta = Surface::load("gfx/kentta.png",false);
    surfSininen = Surface::load("gfx/sininen.png",false);
    surfPunanen = Surface::load("gfx/punanen.png",false);
    surfPunaMolari = Surface::load("gfx/punamolari.png",false);
    surfSiniMolari = Surface::load("gfx/sinimolari.png",false);
    surfKiekko = Surface::load("gfx/kiekko.png",false);
    surfPalkki = Surface::load("gfx/palkki.png",false);
    surfTaustakuva = Surface::load("gfx/taustakuva.png",false);
    surfSiniMaali = Surface::load("gfx/sinimaali.png",false);
    surfPunaMaali = Surface::load("gfx/punamaali.png",false);
    surfKuvake = Surface::load("gfx/lm.png",false);

    Surface::transparent(surfSininen,255,0,255);
    Surface::transparent(surfPunanen,255,0,255);
    Surface::transparent(surfKiekko,255,0,255);
    Surface::transparent(surfPunaMolari,255,0,255);
    Surface::transparent(surfSiniMolari,255,0,255);
    Surface::transparent(surfSiniMaali,255,0,255);
    Surface::transparent(surfPunaMaali,255,0,255);

    // Äänet

    // Musiikit

    // Fontit
    fontVerdana = Font::load("font/verdana.ttf",16);

    // Oliot
    // Sininen pelaaja
    plrSininen.init(surfSininen,45,45);
    plrSininen.setDefaultPosition(268,250);
    plrSininen.setDefaultAngle(0);
    plrSininen.setColBox(12,12,31,31);

    // Punanen pelaaja
    plrPunanen.init(surfPunanen,45,45);
    plrPunanen.setDefaultPosition(332,250);
    plrPunanen.setDefaultAngle(180);
    plrPunanen.setColBox(12,12,31,31);


    // Kiekko
    puck.init(surfKiekko,6,6);
    puck.setDefaultPosition(318,268);

    // Sininen molari
    goalieSini.init(surfSiniMolari,25,30);
    goalieSini.setDefaultPosition(98,255);

    // Punanen molari
    goaliePuna.init(surfPunaMolari,25,30);
    goaliePuna.setDefaultPosition(517,255);

    // Pistetään nimi ja ikoni!
    SDL_WM_SetIcon(surfKuvake, NULL);
    SDL_WM_SetCaption("Laetkaematsi", "Massss!");

    // Aloitetaan peli päävalikosta
    changeState(MENU_MAIN);

    return true;
}

// Ladataan asetukset TIEDOSTOSTA! Huijjjaa!
bool Game::initSettings(std::string path)
{
    // Tiedostomuuttuja
    std::ifstream file;

    // Väliaikaisia muuttujia
    std::string tempStr;
    int tempInt = 0;

    // Avataan tiedosto
    file.open(path.c_str());

    // Tiedostoa ei saatu auki
    if(!file.is_open())
    {
        std::cout<<"ERROR: File could not open "<<path.c_str()<<std::endl;
        return false;
    }

    // Luetaan tiedostoa
    // Hypätään pari riviä yli
    file.ignore(255,'\n');
    file.ignore(255,'\n');

    // Luetaan sinisen näppäimet
    // Eteen
    std::getline(file,tempStr);
    sscanf(tempStr.c_str(),"Forward=%d",&tempInt);
    plrSininen.setKeyForward((SDLKey)tempInt);
    // Taakse
    std::getline(file,tempStr);
    sscanf(tempStr.c_str(),"Backward=%d",&tempInt);
    plrSininen.setKeyBackward((SDLKey)tempInt);
    // Vasemmalle
    std::getline(file,tempStr);
    sscanf(tempStr.c_str(),"Left=%d",&tempInt);
    plrSininen.setKeyLeft((SDLKey)tempInt);
    // Oikealle
    std::getline(file,tempStr);
    sscanf(tempStr.c_str(),"Right=%d",&tempInt);
    plrSininen.setKeyRight((SDLKey)tempInt);
    // Ammutaan
    std::getline(file,tempStr);
    sscanf(tempStr.c_str(),"Shoot=%d",&tempInt);
    plrSininen.setKeyShoot((SDLKey)tempInt);

    // Hypätään pari riviä yli
    file.ignore(255,'\n');
    file.ignore(255,'\n');

    // Luetaan punasen näppäimet
    // Eteen
    std::getline(file,tempStr);
    sscanf(tempStr.c_str(),"Forward=%d",&tempInt);
    plrPunanen.setKeyForward((SDLKey)tempInt);
    // Taakse
    std::getline(file,tempStr);
    sscanf(tempStr.c_str(),"Backward=%d",&tempInt);
    plrPunanen.setKeyBackward((SDLKey)tempInt);
    // Vasemmalle
    std::getline(file,tempStr);
    sscanf(tempStr.c_str(),"Left=%d",&tempInt);
    plrPunanen.setKeyLeft((SDLKey)tempInt);
    // Oikealle
    std::getline(file,tempStr);
    sscanf(tempStr.c_str(),"Right=%d",&tempInt);
    plrPunanen.setKeyRight((SDLKey)tempInt);
    // Ammutaan
    std::getline(file,tempStr);
    sscanf(tempStr.c_str(),"Shoot=%d",&tempInt);
    plrPunanen.setKeyShoot((SDLKey)tempInt);

    // Hypätään pari riviä yli
    file.ignore(255,'\n');
    file.ignore(255,'\n');

    // Luetaan yleiset asetukset
    // Kokonäyttö? HMHM?
    std::getline(file,tempStr);
    sscanf(tempStr.c_str(),"Fullscreen=%d",&tempInt);

    if(tempInt == 1)
        fullscreen = true;
    else
        fullscreen = false;

    // Hypätään pari riviä yli
    file.ignore(255,'\n');
    file.ignore(255,'\n');

    // Luetaan pelin asetukset
    // Maksimierät
    std::getline(file,tempStr);
    sscanf(tempStr.c_str(),"Max_Rounds=%d",&tempInt);
    if(tempInt < 1) maxRounds = 1;
    else if(tempInt > 99) maxRounds = 99;
    else maxRounds = tempInt;
    // Maksimiaika
    std::getline(file,tempStr);
    sscanf(tempStr.c_str(),"Max_Time=%d",&tempInt);
    if(tempInt < 1) maxTime = 1;
    else if(tempInt > 99) maxTime = 99;
    else maxTime = tempInt;
    // Maksimipisteet
    std::getline(file,tempStr);
    sscanf(tempStr.c_str(),"Max_Score=%d",&tempInt);
    if(tempInt < 1) maxScore = 1;
    else if(tempInt > 99) maxScore = 99;
    else maxScore = tempInt;

    // Suljetaan tiedosto
    file.close();

    return true;
}

// Oletusasetusten laittamiseen!
void Game::defaultSettings()
{
    // Laitetaan oletusasetukset
    // Pikkunäyttö
    fullscreen = false;

    // Pelin asetukset
    maxRounds = 2;
    maxTime = 5;
    maxScore = 10;

    // Näppäimet
    // Punanen (ylös, alas, oikea, vasen, oikea ctrl)
    plrPunanen.setKeyForward(SDLK_UP);
    plrPunanen.setKeyBackward(SDLK_DOWN);
    plrPunanen.setKeyLeft(SDLK_LEFT);
    plrPunanen.setKeyRight(SDLK_RIGHT);
    plrPunanen.setKeyShoot(SDLK_RCTRL);

    // Sininen (w, s, d, a, vasen ctrl)
    plrSininen.setKeyForward(SDLK_w);
    plrSininen.setKeyBackward(SDLK_s);
    plrSininen.setKeyLeft(SDLK_a);
    plrSininen.setKeyRight(SDLK_d);
    plrSininen.setKeyShoot(SDLK_LCTRL);
}

// Tallennettaan asetukset tiedostoon!
bool Game::saveSettings(std::string path)
{
    // Avataan tiedosto
    std::ofstream file;

    // Avataan tiedosto
    file.open(path.c_str());

    // Tiedostoa ei saatu auki
    if(!file.is_open())
    {
        std::cout<<"ERROR: File could not open "<<path.c_str()<<std::endl;
        return false;
    }

    // Tallennetaan!
    file<<"// NOTE: Please do not edit this file. It might blow things up. And in case it does, reload default settings from Settings. Thanks!"<<std::endl;
    file<<"// Blue player controls."<<std::endl;
    file<<"Forward="<<(int)plrSininen.getKeyForward()<<std::endl;
    file<<"Backward="<<(int)plrSininen.getKeyBackward()<<std::endl;
    file<<"Left="<<(int)plrSininen.getKeyLeft()<<std::endl;
    file<<"Right="<<(int)plrSininen.getKeyRight()<<std::endl;
    file<<"Shoot="<<(int)plrSininen.getKeyShoot()<<std::endl;
    file<<std::endl;
    file<<"// Red player controls."<<std::endl;
    file<<"Forward="<<(int)plrPunanen.getKeyForward()<<std::endl;
    file<<"Backward="<<(int)plrPunanen.getKeyBackward()<<std::endl;
    file<<"Left="<<(int)plrPunanen.getKeyLeft()<<std::endl;
    file<<"Right="<<(int)plrPunanen.getKeyRight()<<std::endl;
    file<<"Shoot="<<(int)plrPunanen.getKeyShoot()<<std::endl;
    file<<std::endl;
    file<<"// Global settings (Fullscreen 1 = on, 0 = off)."<<std::endl;
    if(fullscreen)
        file<<"Fullscreen=1"<<std::endl;
    else
        file<<"Fullscreen=0"<<std::endl;
    file<<std::endl;
    file<<"// Game settings (time in minutes, between 1-99; rounds between 1-99; score between 1-99)"<<std::endl;
    file<<"Max_Rounds="<<maxRounds<<std::endl;
    file<<"Max_Time="<<maxTime<<std::endl;
    file<<"Max_Score="<<maxScore<<std::endl;

    // Suljetaan tiedosto
    file.close();

    return true;
}

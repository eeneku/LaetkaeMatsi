#include"..\inc\Game.hpp"

Game::Game()
{
    // Näyttöpinnat, tilat yms.
    surfScreen = NULL;
    fullscreen = false;
    running = true;
    state = 0;

    // Perusmuuttujat
    maxScore = 0;
    maxTime = 0;
    gameTimer = 0;
    helpTimer = 0;
    timePassed = 0;
    curTime = 0;
    curSeconds = 0;
    curMinutes = 0;
    maxRounds = 0;
    curRound = 0;
    winner = 0;
    siniScore = 0;
    punaScore = 0;
    curOption = 0;
    maxOptions = 0;
    settingsSaved = false;
    goalMade = false;

    // Grafiikat
    surfKentta = NULL;
    surfSininen = NULL;
    surfPunanen = NULL;
    surfKiekko = NULL;
    surfPalkki = NULL;
    surfTaustakuva = NULL;
    surfSiniMolari = NULL;
    surfPunaMolari = NULL;
    surfSiniMaali = NULL;
    surfPunaMaali = NULL;
    surfKuvake = NULL;

    // Äänet

    // Musiikit

    // Fontit
    fontVerdana = NULL;
}

int Game::onExecute()
{
    std::cout<<"Laetkaematsi v"<<AutoVersion::MAJOR<<"."<<AutoVersion::MINOR<<"."<<AutoVersion::BUILD<<"."<<AutoVersion::REVISION<<std::endl;
    printf("..Starting initializion\n");
    if(onInit() == false) return -1;
    printf("..Initializion complete\n");

    SDL_Event event;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            onEvent(event);
        }

        onLoop();
        onRender();
    }

    printf("..Starting cleanup\n");
    onCleanup();
    printf("..Cleanup complete\n");

    printf("Closing application..\n");
    return EXIT_SUCCESS;

}

std::string Game::intToString(int n)
{
    std::stringstream ss;
    ss<<n;
    return ss.str();
}

int main(int argc, char *argv[])
{
    printf("Application started\n");
    // Luodaan peliolio
    Game game;

    return game.onExecute();
}

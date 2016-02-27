#include"..\inc\Game.hpp"

void Game::onCleanup()
{
    // Poistetaan fontit
    TTF_CloseFont(fontVerdana);

    // Poistetaan pinnat
    SDL_FreeSurface(surfScreen);
    SDL_FreeSurface(surfKentta);
    SDL_FreeSurface(surfSininen);
    SDL_FreeSurface(surfPunanen);
    SDL_FreeSurface(surfKiekko);
    SDL_FreeSurface(surfPalkki);
    SDL_FreeSurface(surfTaustakuva);
    SDL_FreeSurface(surfSiniMolari);
    SDL_FreeSurface(surfPunaMolari);
    SDL_FreeSurface(surfSiniMaali);
    SDL_FreeSurface(surfPunaMaali);
    SDL_FreeSurface(surfKuvake);

    // Suljetaan SDL_Mixer
    Mix_CloseAudio();
    printf("....SDL_Mixer closed\n");

    // Suljetaan TTF
    TTF_Quit();
    printf("....SDL_TTF closed\n");

    // Suljetaan SDL
    SDL_Quit();
    printf("....SDL closed\n");
}

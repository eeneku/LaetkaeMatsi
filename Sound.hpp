#ifndef __SOUND_HPP__
#define __SOUND_HPP__

#include<vector>
#include<string>
#include"SDL.h"
#include"SDL_mixer.h"

// Luokka ‰‰nien k‰sittelyyn
class Sound
{
    public :

    static Mix_Chunk * load(std::string file);

    static void play(Mix_Chunk * sound, int repeat = 0);

    static void playTime(Mix_Chunk * sound, int time);

    static void fadeIn(Mix_Chunk * sound, int time, int repeat = 0);

    static void volume(Mix_Chunk * sound, int volume);

    static void pause(Mix_Chunk * sound);

    static void resume(Mix_Chunk * sound);

    static void stop(Mix_Chunk * sound);

    static void fadeOut(Mix_Chunk * sound, int time);
};

#endif


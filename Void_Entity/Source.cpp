#include "Sound.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>

Sound::Sound()
{
	//call init before playing sounds
}
bool Sound::Init()
{
	mCurrentVolume = 0;
	bool success = true;
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 1, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	mLazer = Mix_LoadWAV("media/sounds/lazer1.wav");
	if (mLazer == NULL)
	{
		printf("Failed to load lazer SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	mExplosion = Mix_LoadWAV("media/sounds/explode.wav");
	if (mExplosion == NULL)
	{
		printf("Failed to load explosion! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	// Set starting volume

	return success;
}
void Sound::playLazer()
{
	Mix_PlayChannel(1, mLazer, 0);
}
void Sound::playExplosion()
{
	Mix_PlayChannel(-1, mExplosion, 0);
}
void Sound::playIntroMus()
{

	music = Mix_LoadMUS("media/sounds/introMus.wav");
	Mix_FadeInMusic(music, -1, 4000);
}

void Sound::levelOneTheme()
{
	music = Mix_LoadMUS("media/sounds/level1Mus.mp3");
	Mix_FadeInMusic(music, -1, 4000);
//	Mix_PlayMusic(music, -1);
}

//new enemies
//score that increases when enemies are destroyed
//high score that saves even after closing the game (save to a file thats fine)
//after a certain period, a boss come
//fix the background.

void Sound::increaseVolume()
{
	Mix_Volume(-1,mCurrentVolume++);
}
void Sound::stopMusic()
{
	Mix_FreeMusic(music);
	music = NULL;
}
void Sound::shutdown()
{
	Mix_FreeChunk(mLazer);
	mLazer = NULL;//to be safe
	Mix_FreeChunk(mExplosion);
	mExplosion = NULL;//to be safe
	Mix_FreeChunk(med);
	med = NULL;//to be safe
	Mix_FreeChunk(low);
	low = NULL;//to be safe

	while (Mix_Init(0))
	{
		Mix_Quit();
	}//make sure mixer is unloaded from memory
}
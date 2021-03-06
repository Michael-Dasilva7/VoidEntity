#ifndef GAME_STATE_H_
#define GAME_STATE_H_
#include <SDL.h>
#include "Sound.h"
// forward declaration of Game class (can't include Game.h here!)
//***************
class Game;  //**
//***************

class GameState
{
protected:
    Game*               mGame;
	Sound*				mSound;
public:
	GameState(Game* game, Sound* sound) : mGame(game), mSound(sound){}
    
    virtual             ~GameState() {}

    virtual void        Initialize()    = 0;
    virtual void        Shutdown()      = 0;

    virtual void        Update()        = 0;
    virtual void        Draw()          = 0;


    virtual void	    OnWindowResized(int w, int h)                   {}
    virtual void		OnKeyDown(const SDL_KeyboardEvent& kbe)         {}
    virtual void		OnKeyUp(const SDL_KeyboardEvent& kbe)           {}
    virtual void		OnMouseDown(const SDL_MouseButtonEvent& mbe)    {}
    virtual void		OnMouseUp(const SDL_MouseButtonEvent& mbe)      {}
    virtual void		OnMouseMotion(const SDL_MouseMotionEvent& mme)  {}
};
#endif
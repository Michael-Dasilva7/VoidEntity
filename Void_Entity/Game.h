#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>

#include "Gameplay.h"
#include "MainMenu.h"
#include "Sound.h"
#include "GameOver.h"
class Game
{
	int					mScreenHeight;
	int					mScreenWidth;

	SDL_Window*			mWindow;
	const Uint8*		mKeys;
	SDL_Renderer*		mRenderer;
	

	bool				mShouldQuit;
	Sound*				mSound;
    Gameplay*           mGameplayState;
    MainMenu*           mMainMenuState;
	GameOver*           mGameOverState;
	GameState*          mCurrentState; //gameplay state has children that do different things...eg. menu/gameplay

public:
						Game();
	bool			    Run();
    int                 GetScreenWidth()   const    { return mScreenWidth; }
    int                 GetScreenHeight()  const    { return mScreenHeight; }
    SDL_Renderer*       GetRenderer()      const    { return mRenderer; }
    const Uint8*        GetKeys()          const    { return mKeys; }
    Gameplay*           GetGameplayState() const    { return mGameplayState; }
    MainMenu*           GetMainMenuState() const    { return mMainMenuState; }
	GameOver*           GetGameOverState() const    { return mGameOverState; }
    void                EnterMainMenu();
    void                EnterGameplay();
	void                EnterGameover();
    void                Quit()                      { mShouldQuit = true; }

private:
	bool				Initialize();
	void				Shutdown();

	void				ProcessEvents();

	void				OnQuit();

    void				OnWindowResized(int w, int h);
	void				OnKeyDown(const SDL_KeyboardEvent* kbe);
	void				OnKeyUp(const SDL_KeyboardEvent* kbe);
	void				OnMouseDown(const SDL_MouseButtonEvent* mbe);
	void				OnMouseUp(const SDL_MouseButtonEvent* mbe);
	void				OnMouseMotion(const SDL_MouseMotionEvent* mme);

	void				Update();
	void				Draw();
};

#endif

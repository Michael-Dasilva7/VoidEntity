#ifndef GAME_OVER_H_
#define GAME_OVER_H_

#include "GameState.h"
#include "Button.h"

class GameOver : public GameState
{
	SDL_Texture*        mBtnNewTex;
	SDL_Texture*        mBtnMainMenuTex;
	SDL_Texture*        mBtnExitTex;
	SDL_Texture*        mBackground;

	SDL_Texture*        mDescription1;

	Button*             mBtnNew;
	Button*             mBtnMainMenu;
	Button*             mBtnExit;
	Sound*				mCurrentSound;
public:
	GameOver(Game* game, Sound* sound);
	~GameOver();
	void                Initialize() override;
	void                Shutdown() override;

	void                Update() override;
	void                Draw() override;

	void		        OnKeyDown(const SDL_KeyboardEvent& kbe) override;
	void		        OnMouseDown(const SDL_MouseButtonEvent& mbe) override;
	void		        OnMouseMotion(const SDL_MouseMotionEvent& mbe) override;
};
#endif

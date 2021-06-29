#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include "GameState.h"
#include "Button.h"

class MainMenu : public GameState
{
    SDL_Texture*        mBtnNewTex;
    SDL_Texture*        mBtnResumeTex;
    SDL_Texture*        mBtnExitTex;
	SDL_Texture*        mBackground;
	
	SDL_Texture*        mDescription1;
	SDL_Texture*        mDescription2;

    Button*             mBtnNew;
    Button*             mBtnResume;
    Button*             mBtnExit;
	Sound*				mCurrentSound;
public:
                        MainMenu(Game* game,Sound* sound);
                        ~MainMenu();
    void                Initialize() override;
    void                Shutdown() override;

    void                Update() override;
    void                Draw() override;

    void		        OnKeyDown(const SDL_KeyboardEvent& kbe) override;
    void		        OnMouseDown(const SDL_MouseButtonEvent& mbe) override;
	void		        OnMouseMotion(const SDL_MouseMotionEvent& mbe) override;
};
#endif

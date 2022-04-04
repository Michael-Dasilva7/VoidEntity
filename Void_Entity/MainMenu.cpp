#include "MainMenu.h"
#include "Gameplay.h"
#include "Texture.h"
#include "Game.h"
#include "Sound.h"
#include <iostream>

MainMenu::MainMenu(Game* game, Sound* sound)
    : GameState(game, sound)
    , mBtnNewTex(NULL)
    , mBtnResumeTex(NULL)
    , mBtnExitTex(NULL)
    , mBtnNew(NULL)
    , mBtnResume(NULL)
    , mBtnExit(NULL)
	, mDescription1(NULL)
	, mDescription2(NULL)
	, mCurrentSound(sound)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Initialize()
{
    SDL_Renderer* renderer = mGame->GetRenderer();

	mDescription1 = LoadTexture("media/UI/x-saveTheVerse.png",renderer);
	mDescription2 = LoadTexture("media/UI/x-fromDestruction.png", renderer);
    mBtnNewTex = LoadTexture("media/UI/x-New_Game.png", renderer);
    mBtnResumeTex = LoadTexture("media/UI/button_resume.png", renderer);
    mBtnExitTex = LoadTexture("media/UI/x-Exit_Game.png", renderer);
	mBackground = LoadTexture("media/backgrounds/starysky.jpg", renderer);

	SDL_Rect* background = new SDL_Rect();
	background->w = 900;
	background->h = 600;
	background->x = 0;
	background->y = 0;
    
    mBtnNew = new Button(mBtnNewTex);
    mBtnResume = new Button(mBtnResumeTex);
    mBtnExit = new Button(mBtnExitTex);
    
    int cx = mGame->GetScreenWidth() / 2;
    int cy = mGame->GetScreenHeight() / 2;
	 
    mBtnResume->SetCenter(cx, cy - 100);
    mBtnNew->SetCenter(cx, cy);
    mBtnExit->SetCenter(cx, cy + 100);

	//load sound for the title 
	mCurrentSound->playIntroMus();

}

void MainMenu::Shutdown()
{
    delete mBtnNew;
    delete mBtnResume;
    delete mBtnExit;
//	delete mBackground;

	//SDL_DestroyTexture(mBackground);
    SDL_DestroyTexture(mBtnNewTex);
    SDL_DestroyTexture(mBtnResumeTex);
    SDL_DestroyTexture(mBtnExitTex);
}
//pure virtual in the base therefore i need to override even if it does nadda
void MainMenu::Update()
{

}

void MainMenu::Draw()
{
    SDL_Renderer* renderer = mGame->GetRenderer();

	SDL_Rect* backgroundDestRect = new SDL_Rect();
	backgroundDestRect->w = 900;
	backgroundDestRect->h = 600;
	backgroundDestRect->x = 0;
	backgroundDestRect->y = 0;
	SDL_Rect* descriptionOne_DestRect = new SDL_Rect();
	descriptionOne_DestRect->w = 544;
	descriptionOne_DestRect->h = 32;
	descriptionOne_DestRect->x = 160;
	descriptionOne_DestRect->y = 40;
	SDL_Rect* descriptionTwo_DestRect = new SDL_Rect();
	descriptionTwo_DestRect->w = 544;
	descriptionTwo_DestRect->h = 32;
	descriptionTwo_DestRect->x = 160;
	descriptionTwo_DestRect->y = 80;

    if (mGame->GetGameplayState()->IsActive()) //if main menu is current active state
	{
        mGame->GetGameplayState()->Draw();
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 33, 192);
        SDL_RenderFillRect(renderer, NULL);
		//load background texture
		if (mBackground) 
		{
			// draw textured rectangle
			//	SDL_RenderCopy(renderer, mBackground, NULL, backgroundDestRect);                               // <--- ###
		}
		else 
		{
			// draw solid rectangle
		}
        mBtnResume->Draw(renderer);
    } else {

        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, mBackground, NULL, backgroundDestRect);
		SDL_RenderCopy(renderer, mDescription1, NULL, descriptionOne_DestRect);
		SDL_RenderCopy(renderer, mDescription2, NULL, descriptionTwo_DestRect);
    }
    mBtnNew->Draw(renderer);
    mBtnExit->Draw(renderer);
}
void MainMenu::OnKeyDown(const SDL_KeyboardEvent& kbe)
{
    switch (kbe.keysym.sym) {
    case SDLK_ESCAPE:
        std::cout << "User pressed Escape" << std::endl;
        //mGame->mShouldQuit = true;  // set quit flag
        mGame->EnterGameplay();
        break;
    }
}
void MainMenu::OnMouseDown(const SDL_MouseButtonEvent& mbe)
{
    if (mbe.button == SDL_BUTTON_LEFT) {

        if (mGame->GetGameplayState()->IsActive()) {
            if (mBtnResume->Contains(mbe.x, mbe.y)) {//MouseButtonEvent properties have the x and y of where it fired
                mGame->EnterGameplay();
            }
        }

        if (mBtnNew->Contains(mbe.x, mbe.y)) {
            mGame->GetGameplayState()->LoadLevel();// reset everything
            mGame->EnterGameplay();
        }

        if (mBtnExit->Contains(mbe.x, mbe.y)) {
            mGame->Quit();
        }
    }
}

void MainMenu::OnMouseMotion(const SDL_MouseMotionEvent& mbe)
{

	if (mbe.x > mBtnNew->Left() && mbe.x < mBtnNew->Right() && mbe.y > mBtnNew->Top() && mbe.y < mBtnNew->Bottom())
	{
		/*	//find alpha
			if (SDL_GetSurfaceAlphaMod)
			//inside button new
			int SDL_SetTextureAlphaMod(SDL_Texture* texture,
			Uint8        alpha);
			}*/
	}
}

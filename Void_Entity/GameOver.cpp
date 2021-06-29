#include "GameOver.h"
#include "Gameplay.h"
#include "Texture.h"
#include "Game.h"
#include "Sound.h"
#include <iostream>

GameOver::GameOver(Game* game, Sound* sound)
	: GameState(game, sound)
	, mBtnNewTex(NULL)
	, mBtnMainMenuTex(NULL)
	, mBtnExitTex(NULL)
	, mBtnNew(NULL)
	, mBtnMainMenu(NULL)
	, mBtnExit(NULL)
	, mDescription1(NULL)
	, mCurrentSound(sound)
{
}

GameOver::~GameOver()
{
}

void GameOver::Initialize()
{
	SDL_Renderer* renderer = mGame->GetRenderer();

	mBtnNewTex = LoadTexture("media/x-New_Game.png", renderer);
	mBtnMainMenuTex = LoadTexture("media/x-Main_Menu.png", renderer);
	mBtnExitTex = LoadTexture("media/x-Exit_Game.png", renderer);
	mDescription1 = LoadTexture("media/x-Game_Over.png", renderer);
	mBackground = LoadTexture("media/starysky.jpg", renderer);

	mBtnNew = new Button(mBtnNewTex);
	mBtnMainMenu = new Button(mBtnMainMenuTex);
	mBtnExit = new Button(mBtnExitTex);

	int cx = mGame->GetScreenWidth() / 2;
	int cy = mGame->GetScreenHeight() / 2;

	mBtnMainMenu->SetCenter(cx, cy - 100);
	mBtnNew->SetCenter(cx, cy);
	mBtnExit->SetCenter(cx, cy + 100);

	//load sound for the title 
 	mCurrentSound->playTime();
}

void GameOver::Shutdown()
{
	delete mBtnNew;
	delete mBtnMainMenu;
	delete mBtnExit;
	//	delete mBackground;

	//SDL_DestroyTexture(mBackground);
	SDL_DestroyTexture(mBtnNewTex);
	SDL_DestroyTexture(mBtnMainMenuTex);
	SDL_DestroyTexture(mBtnExitTex);
}
//pure virtual in the base therefore i need to override even if it does nadda
void GameOver::Update()
{

}

void GameOver::Draw()
{
	SDL_Renderer* renderer = mGame->GetRenderer();
	
	SDL_Rect* backgroundDestRect = new SDL_Rect();
	backgroundDestRect->w = 900;
	backgroundDestRect->h = 600;
	backgroundDestRect->x = 0;
	backgroundDestRect->y = 0;
	SDL_Rect*  description = new SDL_Rect(); //rect for game over title
	description->w = 480;
	description->h = 40;
	description->x = 250;
	description->y = 50;

	SDL_RenderCopy(renderer, mBackground, NULL, backgroundDestRect);
	SDL_RenderCopy(renderer, mDescription1, NULL, description);
	mBtnNew->Draw(renderer);
	mBtnMainMenu->Draw(renderer);
	mBtnExit->Draw(renderer);
	
}
void GameOver::OnKeyDown(const SDL_KeyboardEvent& kbe)
{
	switch (kbe.keysym.sym) {
	case SDLK_ESCAPE:
		std::cout << "User pressed Escape" << std::endl;
		//mGame->mShouldQuit = true;  // set quit flag
		mGame->EnterGameplay();
		break;
	}
}
void GameOver::OnMouseDown(const SDL_MouseButtonEvent& mbe)//mbe = my button event
{
	if (mbe.button == SDL_BUTTON_LEFT) {

		if (mGame->GetGameplayState()->IsActive()) {
			if (mBtnMainMenu->Contains(mbe.x, mbe.y)) {//MouseButtonEvent properties have the x and y of where it fired
				mGame->EnterGameplay();
			}
		}

		if (mBtnNew->Contains(mbe.x, mbe.y)) {
			mGame->GetGameplayState()->LoadLevel();// reset everything
			mGame->EnterGameplay();
		}
		else if (mBtnMainMenu->Contains(mbe.x, mbe.y)) {
			mGame->GetGameplayState()->LoadLevel();// reset everything
			mGame->EnterMainMenu();
		}
		else if (mBtnExit->Contains(mbe.x, mbe.y)) {
			mGame->Quit();
		}
	}
}

void GameOver::OnMouseMotion(const SDL_MouseMotionEvent& mbe)
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

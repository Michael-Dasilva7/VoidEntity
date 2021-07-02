#include "Gameplay.h"
#include "Texture.h"
#include "Game.h"
#include "Sound.h"
#include <iostream>
#include "Animation.h"
//*Comment Index
/*
EnemyAI


*/
Gameplay::Gameplay(Game* game, Sound* sound) : GameState(game, sound)
, mPlayer(NULL)
, mMissiles()
, mPlayerTex(NULL)
, mShotTex(NULL)
, mBackgroundTex1(NULL)
, mBackgroundTex2(NULL)
, mBackgroundTex3(NULL)
, mBackgroundTex4(NULL)
, mIsActive(false)
, mBackground1Pos(0)
, mBackground2Pos(0)
, mBackground3Pos(0)
, mBackground4Pos(0)
, mScrollDelayer(0)
, mCurrentSound(sound)
, mLastTime(1) // maybe add to gamestate later because all gamestates need to know current time for stuffs
, mFlierTex(NULL)
, mFliers(NULL)
, mEnemyCount(0)
, mPlayerLives(0)
, mMissleCount(0){
}
Gameplay::~Gameplay()
{
}
void Gameplay::Initialize()
{
	SDL_Renderer* renderer = mGame->GetRenderer();
	//
	// load texture
	//
	mPlayerTex = LoadTexture("media/shuttle.png", renderer);
	mShotTex = LoadTexture("media/shot.png", renderer);
	mBackgroundTex1 = LoadTexture("media/background1.png", renderer);
	mBackgroundTex2 = LoadTexture("media/background2.png", renderer);
	mBackgroundTex3 = LoadTexture("media/background3.png", renderer);
	mBackgroundTex4 = LoadTexture("media/background4.png", renderer);
	mExplosionTex = LoadTexture("media/explosion.tga", renderer);
	//load enemy
	mFlierTex = LoadTexture("media/enemy.png", renderer);
	//load sound for gameplay
	LoadLevel();
	


}

void Gameplay::Shutdown()
{
	ClearLevel();

	// delete the textures and save the day!
	SDL_DestroyTexture(mPlayerTex);
	SDL_DestroyTexture(mBackgroundTex1);
	SDL_DestroyTexture(mBackgroundTex2);
	SDL_DestroyTexture(mBackgroundTex3);
	SDL_DestroyTexture(mBackgroundTex4);

	SDL_DestroyTexture(mExplosionTex);
	SDL_DestroyTexture(mFlierTex);
	SDL_DestroyTexture(mShotTex);   
	//add enemy an sound deconstructors
}

void Gameplay::LoadLevel()
{
	ClearLevel();
	mSound->playAxelayTheme();
	//
	// initialize the player
	//
	mPlayerLives = 3;
	mPlayer = new Player(mPlayerTex);
	mPlayer->setLives(3);
	mPlayer->SetColor(192, 0, 164, 255);                        // set fallback color
	mPlayer->SetCenter(30, mGame->GetScreenHeight() / 2);

	mHighScore = 0;//each levelmight need to carry this over. if statement with a level incrementer

}

void Gameplay::ClearLevel()
{
	delete mPlayer;
	mPlayer = NULL;

	for (auto it = mMissiles.begin(); it != mMissiles.end(); it++) {
		Missile* m = *it;
		delete m;
	}
	mMissleCount = 0;
	mEnemyCount = 0;
	mFliers.clear();
	mMissiles.clear();
	mPlayer = NULL;
	
}

void Gameplay::Update()
{
	//bool isBoss = false;
	bool mIsDestroyed = false;
	//bool mIsPlayerDestroyed;
	//mLastTime
	mCurrentTime = (SDL_GetTicks() / 1000); // current time in seconds
	if (mLastTime % 4)
	{
		//activeEnemy = new StraightFlier();
		if (mEnemyCount < 10)
		{
			StraightFlier* activeEnemy = new StraightFlier(mFlierTex, mGame->GetScreenWidth()+ 64,10+ rand()%550);
			activeEnemy->setVelocity((rand() % 3) + 1, 0); //set
			mFliers.push_back(activeEnemy);
			mLastTime = 0;
			mEnemyCount++;
		}
		else{
		}
	}

	//iterate through enemies and check every bullet location in relation to current enemy
	for (auto it = mFliers.begin(); it != mFliers.end();)
	{

		StraightFlier* e = *it;
		
		//check every missles location
		for (auto it2 = mMissiles.begin(); it2 != mMissiles.end();)
		{
			Missile* m = *it2; // point to current missle		
			if (e->isCollision(m->Left(), m->Top()))//if current missile is inside of the enemy
			{
				delete m;
				it2 = mMissiles.erase(it2);
				mMissleCount--;
		 		mIsDestroyed = true;
				break;
			}
			//else if( e->isCollide(playerx,playery) ) player and enemy explode and dead = true which leadsto ending game loop
			else
			{
				it2++;//check next missle
			}
			//add explosion at location if collision
		}
		if (e->isCollision(mPlayer->Right(), mPlayer->Top()) || e->isCollision(mPlayer->Left(), mPlayer->Top()) || e->isCollision(mPlayer->Left(), mPlayer->Bottom()) || e->isCollision(mPlayer->Right(), mPlayer->Bottom()))
		{
			--mPlayerLives;
			mIsDestroyed = true;
			if (mPlayerLives <= 0)
			{
				mIsActive = false;
				mSound->stopMusic();
				mGame->EnterGameover();
			}
			else//player is destroyed and revived 
			{
				//is destroyed therefore we need to add a new explosion to the list
				mSound->playExplosion();
				Explosion* explode = new Explosion(mExplosionTex, mPlayer->Left(), mPlayer->Top());
				mExplosions.push_back(explode);
				std::cout << "Player Destroyed at(seconds): " << mCurrentTime << std::endl;
				mPlayer->SetCenter(30, mGame->GetScreenHeight() / 2);
			}
		}
		if ((e->Left() < 0 - e->getWidth()) /*&& !mIsDestroyed*/)
		{
			it = mFliers.erase(it);
			delete e;
			mEnemyCount--;
		}
		else if (mIsDestroyed)
		{
			//is destroyed therefore we need to add a new explosion to the list
			mSound->playExplosion();
		 	Explosion* explode = new Explosion(mExplosionTex, e->Left(), e->Top());
	    	mExplosions.push_back(explode);
			it = mFliers.erase(it);
			delete e;
     		mEnemyCount--;
			std::cout << "Enemy Destroyed at(seconds): " << mCurrentTime << std::endl;
			mIsDestroyed = false;

			mHighScore += 100;
			//Change based on which enemy is killed later.
		}
		else
		{
			//std::cout << "Update Enemy " << mCurrentTime << std::endl;
			e->Update();
			it++;
		}

	}

	for (auto it = mMissiles.begin(); it != mMissiles.end();) {
		Missile* m = *it;

		m->Update();
		//check if missles are off screen - by checking their left edge is past right side of screen
		if (m->Left() > mGame->GetScreenWidth()) 
		{
			it = mMissiles.erase(it);
			mMissleCount--;
			delete m;
		}
		else {

			it++;
		}
	}

	for (auto it = mExplosions.begin(); it != mExplosions.end();)//check explosions an update
	{
		Explosion* e = *it;

		if (e->mDurationComplete)//if explosion over delete it
		{
			it = mExplosions.erase(it);//remove from list

			delete e;//delete from list
		}
		else
		{
			float dx = ((float)SDL_GetTicks() / 1000) - mLastTime;
			e->Update(dx * .21f);//update explosion if not finished animation

			it++;
		}
		//mMissleCount--;
	}
	mIsActive = true;

	//set last time to current time to check it against next iteration of this update
	mLastTime = mCurrentTime;
	mPlayer->Update(mGame->GetKeys());
}
void Gameplay::Draw()
{
	SDL_Renderer* renderer = mGame->GetRenderer();

	// clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, mBackgroundTex1, NULL, NULL);

	dstRect.h = 720;
	dstRect.w = 1280;
	dstRect.x = 0;
	dstRect.y = 0;

	srcRect.w = 1280;
	srcRect.h = 720;
	srcRect.y = 0;
	// **************************************PARRALLAX ALERT*****************************************************//
	if (mBackground1Pos >= 12562 )
	{
		srcRect.w = 12562;
		srcRect.x = mBackground1Pos;
		dstRect.w = 12562 ;
		dstRect.x = 0;
		SDL_RenderCopy(renderer, mBackgroundTex1, &srcRect, &dstRect);

		srcRect.w = 1280 - (12562 - mBackground1Pos);
		srcRect.x = 0;
		dstRect.w = 1280 - (12562 - mBackground1Pos);
		dstRect.x = (12562 - mBackground1Pos);
		SDL_RenderCopy(renderer, mBackgroundTex1, &srcRect, &dstRect);
		//if (mBackground1Pos >= 12562)
			//mBackground1Pos = 0;
	}
	else{
		srcRect.x = mBackground1Pos;
		srcRect.w = 1280;
		srcRect.h = 720;
		srcRect.y = 0;
		//std::cout << "first" << std::endl;
		SDL_RenderCopy(renderer, mBackgroundTex1, &srcRect, NULL);

	}
	if (mBackground2Pos >= 3000 - 1280){
		srcRect.w = 3000 - mBackground2Pos;
		srcRect.x = mBackground2Pos;
		dstRect.w = 3000 - mBackground2Pos;
		dstRect.x = 0;
		SDL_RenderCopy(renderer, mBackgroundTex2, &srcRect, &dstRect);

		srcRect.w = 1280 - (3000 - mBackground2Pos);
		srcRect.x = 0;
		dstRect.w = 1280 - (3000 - mBackground2Pos);
		dstRect.x = (3000 - mBackground2Pos);
		SDL_RenderCopy(renderer, mBackgroundTex2, &srcRect, &dstRect);
		if (mBackground2Pos >= 3000)
			mBackground2Pos = 0;
	}
	else
	{
		srcRect.x = mBackground2Pos;
		srcRect.w = 1280;
		srcRect.h = 720;
		srcRect.y = 0;
		SDL_RenderCopy(renderer, mBackgroundTex2, &srcRect, NULL);
	}
	if (mBackground3Pos >= 3000 - 1280){
		srcRect.w = 3000 - mBackground3Pos;
		srcRect.x = mBackground3Pos;
		dstRect.w = 3000 - mBackground3Pos;
		dstRect.x = 0;
		SDL_RenderCopy(renderer, mBackgroundTex3, &srcRect, &dstRect);

		srcRect.w = 1280 - (3000 - mBackground3Pos);
		srcRect.x = 0;
		dstRect.w = 1280 - (3000 - mBackground3Pos);
		dstRect.x = (3000 - mBackground3Pos);
		SDL_RenderCopy(renderer, mBackgroundTex3, &srcRect, &dstRect);
		if (mBackground3Pos >= 3000)
			mBackground3Pos = 0;
	}
	else{
		srcRect.x = mBackground3Pos;
		srcRect.w = 1280;
		srcRect.h = 720;
		srcRect.y = 0;
		SDL_RenderCopy(renderer, mBackgroundTex3, &srcRect, NULL);

	}
	if (mBackground4Pos >= 3000 - 1280){
		srcRect.w = 3000 - mBackground4Pos;
		srcRect.x = mBackground4Pos;
		dstRect.w = 3000 - mBackground4Pos;
		dstRect.x = 0;
		SDL_RenderCopy(renderer, mBackgroundTex4, &srcRect, &dstRect);

		srcRect.w = 1280 - (3000 - mBackground4Pos);
		srcRect.x = 0;
		dstRect.w = 1280 - (3000 - mBackground4Pos);
		dstRect.x = (3000 - mBackground4Pos);
		SDL_RenderCopy(renderer, mBackgroundTex4, &srcRect, &dstRect);
		if (mBackground4Pos >= 3000)
			mBackground4Pos = 0;
	}
	else{
		srcRect.x = mBackground4Pos;
		srcRect.w = 1280;
		srcRect.h = 720;
		srcRect.y = 0;

		SDL_RenderCopy(renderer, mBackgroundTex4, &srcRect, NULL);
	}

	// draw missiles
	for (auto it = mMissiles.begin(); it != mMissiles.end(); it++) {
		Missile* m = *it;
		m->Draw(renderer);
	}
	for (auto it = mFliers.begin(); it != mFliers.end();)
	{
		StraightFlier* e = *it;
		e->Draw(renderer);
		it++;
	}
	for (auto it = mExplosions.begin(); it != mExplosions.end();)
	{
		Explosion* e = *it;
		e->Draw(renderer);
		it++;
	}

	mBackground1Pos += 1;
	mBackground2Pos += 2;
	mBackground3Pos += 4;
	mBackground4Pos += 6;
	// draw player
	mPlayer->Draw(renderer);
	// tell the renderer to display everything we just drew
	//	SDL_RenderPresent(renderer);
	SDL_Rect life = SDL_Rect();
	life.x = 700;
	life.y = 15;
	life.h = 34;
	life.w = 34;
	for (int i = 0; i < mPlayerLives; i++)
	{
		life.x += 36;
		//std::cout << "mPlayerLives" << mPlayerLives << std::endl;
			SDL_RenderCopy(renderer, mPlayerTex, NULL, &life);
	}

	//Display High Score!
	//mPlayerLives
	//https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
}
void Gameplay::OnKeyDown(const SDL_KeyboardEvent& kbe)
{
	switch (kbe.keysym.sym) {
	case SDLK_ESCAPE:
		std::cout << "User pressed Escape" << std::endl;
		//mGame->mShouldQuit = true;  // set quit flag
		mGame->EnterMainMenu();
		break;

	case SDLK_p:
		std::cout << mMissiles.size() << " missiles" << std::endl;
		break;
	case SDLK_SPACE:
		//if there are less than 3 regular missiles on screen
		if (mMissleCount < 3)
		{
			mMissleCount++;
			//figure out how to make a bettermissle animation
			std::cout << "Creating missile" << std::endl;
			Missile* m = new Missile(mShotTex);
			SDL_Point p = mPlayer->Center();
			m->SetCenter(p.x, p.y);
			m->SetSpeed(5, 0);
			mMissiles.push_back(m);
			mCurrentSound->playLazer();
			break;
		}
		
		
	}
}
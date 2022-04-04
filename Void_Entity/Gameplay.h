#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "GameState.h"
#include "Player.h"
#include "Missile.h"
#include "Sound.h"
#include "StraightFlier.h"
#include "Explosion.h"
#include <list>

class Gameplay : public GameState
{
	Player*				       mPlayer;
	std::list<Explosion*>      mExplosions; // list of explosions
	std::list<StraightFlier*>  mFliers;
    std::list<Missile*>		   mMissiles;
	//convince him we know how to use the tools he gave us to use it

	Uint32              mCurrentTime;
	
	//TODO: Implement a resourceManager to dynamically create and return pointers to textures
	SDL_Texture*        mPlayerTex;
    SDL_Texture*        mShotTex;
	SDL_Texture*		mBackgroundTex1;
	SDL_Texture*		mBackgroundTex2;
	SDL_Texture*		mBackgroundTex3;
	SDL_Texture*		mBackgroundTex4;
	SDL_Texture*        mFlierTex;
	SDL_Texture*		mExplosionTex;

	SDL_Texture*		mTextAndNumbers;

	SDL_Texture*		mMissleAnimations;

	SDL_Rect			srcRect;
	SDL_Rect		    dstRect;

	int					mBackground1Pos;
	int					mBackground2Pos;
	int					mBackground3Pos;
	int					mBackground4Pos;
	int					mScrollDelayer;
	int                 mEnemyCount;
	int                 mMissleCount;

	int					mHighScore;

	int					mEnemyKillCount;
	bool				mPauseEnemyGeneration;

	int					mPlayerLives; //how many lives a player has
	Uint32				mLastTime;
    bool                mIsActive;

	bool				mIsLevelOnePhaseOne;	//before the star field and enemy generation
	bool				mIsLevelOnePhaseTwo;	//This is when enemies start to spawn and particle field comes in
	bool				mIsLevelOnePhaseThree;  //This is when the boss appears! 

	bool				mIsLevelTwoPhaseOne;
	bool				mIsLevelTwoPhaseTwo;
	bool				mIsLevelTwoPhaseThree;

	Sound*			    mCurrentSound;
public:
						Gameplay(Game* game, Sound* sound);
                        ~Gameplay();
    bool                IsActive() const        { return mIsActive; }
    void                Initialize() override;
    void                Shutdown() override;
    void                LoadLevel();
    void                ClearLevel();
    void                Update() override;
    void                Draw() override;
    void		        OnKeyDown(const SDL_KeyboardEvent& kbe) override;
	void				OnMouseDown(const SDL_MouseButtonEvent& mbe) override;

	void				FirePlayerBullet();
};
#endif
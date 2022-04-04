#ifndef ENEMY_H_
#define ENEMY_H_

#include <SDL.h>
#include <list> 
#include "Missile.h"


/*
This is the base pure virtual class that all the simple enemies in the game are derived from
SET TO ADD AnIMATION FUNCTIONALITY
*/
class Enemy
{
	int						mVelocity;
	SDL_Rect				mRect;
    SDL_Color*   			mColor;     // fallback color, in case there are problems with the texture
	SDL_Texture*            mTex;
 
	//int[][]                 mEnemySpec; //list of sprite sizes  
public:
	Enemy(){};
	Enemy(SDL_Texture* tex, int x, int y)
	{
		mTex = tex;
		mRect.x = x;
		mRect.y = y;
	};

	virtual void Move(int x, int y) = 0;
	virtual int	Left() const = 0;					    //	{ return mRect.x; }
	virtual int	Top() const = 0;					    //{ return mRect.y; }
	virtual int Right() const = 0;				        //	{ return mRect.x + mRect.w; }
	virtual int	Bottom() const = 0;					    //	{ return mRect.y + mRect.h; }
	virtual int getWidth() const { return mRect.w; };   //return mRect.w;
	virtual int getHeight() const   { return mRect.h; };//return mRect.h;
	virtual void setVelocity(int velX,int velY)=0;      //set specified speed
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw(SDL_Renderer* renderer) = 0;
	virtual bool isCollision(int x, int y) = 0;
	virtual	int scoreCount() = 0;
};
#endif
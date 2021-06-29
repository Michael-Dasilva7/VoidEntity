#include "Explosion.h"
#include "Texture.h"
#include <SDL.h>
#include <iostream>
#include "Animation.h"
#include "Math.h"
const int Explosion::msDefaultWidth = 64;
const int Explosion::msDefaultHeight = 64;
const int Explosion::msExplosionCount = 16;
int numCells = 16;
Explosion::Explosion()
{
}

Explosion::Explosion(SDL_Texture* tex, int x, int y)
{
	//
	int w = msDefaultWidth;
	int h = msDefaultHeight;
	// if the texture is not NULL, get its size
	//set width and height to the size of the texture segment
	mRect.w = w;
	mRect.h = h;
	//set location to arguments passed in
	mRect.x = x;
	mRect.y = y;
	mTex = tex;
	mDurationComplete = false;//initialize to false

	mAnimation = new Animation(tex,numCells,10.0f,false,DIR_LEFT);
}
Explosion::~Explosion()
{

}

void Explosion::Update(float dx)
{/*
	Animation::Animation(SDL_Texture* tex, int numCells, float duration, bool loopable, Direction defaultDir)
	: mTex(tex)
	, mNumCells(numCells)
	, mDuration(duration)
	, mIsLoopable(loopable)
	, mDefaultDir(defaultDir)
	, mCellWidth(0)
	, mCellHeight(0)
	, mTime(0.0f)
	{
		int texWidth = 0, texHeight = 0;
		SDL_QueryTexture(tex, NULL, NULL, &texWidth, &texHeight);

		mCellWidth = texWidth / numCells;
		mCellHeight = texHeight;
     }
*/
	
	mAnimation->AddTime(dx);
}     


void Explosion::Draw(SDL_Renderer* renderer)
{   
	
	SDL_Rect* source = new SDL_Rect();
	source->x = mRect.x;
	source->y = mRect.y;
	source->h = msDefaultHeight;
	source->w = msDefaultWidth;
	//SDL_RenderCopy(renderer, mTex, &source, &mRect);
	
	mAnimation->Draw(renderer, source, DIR_LEFT);
}
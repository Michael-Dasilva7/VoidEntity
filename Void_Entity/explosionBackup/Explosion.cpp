#include "Explosion.h"
#include "Texture.h"
#include <SDL.h>
#include <iostream>
const int Explosion::msDefaultWidth = 64;
const int Explosion::msDefaultHeight = 64;
const int Explosion::msExplosionCount = 16;
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
}
Explosion::~Explosion()
{
}

void Explosion::Update()
{
	//animation frame 1 will be 0, 2 will be 64, 3 will be 128
	mAnimationFrame = (mAnimationFrame + 2) % 60;
	if (mAnimationFrame >= 16)
	{
		mDurationComplete = true;
	}

}     


void Explosion::Draw(SDL_Renderer* renderer)
{
	SDL_Rect source;
	source.x = mAnimationFrame * 64;
	source.y = 0;
	source.h = msDefaultHeight;
	source.w = msDefaultWidth;
	SDL_RenderCopy(renderer, mTex, &source, &mRect);

}
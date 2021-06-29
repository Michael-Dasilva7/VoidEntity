#include "Animation.h"
#include <cmath>

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

Animation::~Animation()
{
	// nothing to destroy
}

void Animation::AddTime(float dt)
{
	mTime += dt;

	// see if we've reached or passed the end
	if (mTime >= mDuration) 
	{
		if (mIsLoopable) 
		{
			// wrap around
			mTime = std::fmod(mTime, mDuration);
		}
		else 
		{
			// cap
			mTime = mDuration;
		}
	}
}

void Animation::Draw(SDL_Renderer* renderer, const SDL_Rect* dstRect, Direction dir)
{
	int cellIndex;
	if (mTime <= 0.0f) 
	{
		cellIndex = 0;
	}
	else if (mTime >= mDuration) 
	{
		cellIndex = mNumCells - 1;
	}
	else 
	{
		cellIndex = (int)(mTime / mDuration * mNumCells);
	}

	SDL_Rect srcRect;
	srcRect.w = mCellWidth;
	srcRect.h = mCellHeight;
	srcRect.x = cellIndex * mCellWidth;
	srcRect.y = 0;

	SDL_RendererFlip flip;
	if (dir == mDefaultDir)
	{
		flip = SDL_FLIP_NONE;
	}
	else
	{
		flip = SDL_FLIP_HORIZONTAL;
	}

	SDL_RenderCopyEx(renderer, mTex, &srcRect, dstRect, 0.0, NULL, flip);
}

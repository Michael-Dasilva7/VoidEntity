#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <SDL.h>

#include "Math.h"

class Animation
{
	SDL_Texture*                mTex;
	int                         mNumCells;
	float                       mDuration;          // in seconds
	bool                        mIsLoopable;
	Direction                   mDefaultDir;        // the direction in which the sprite is facing in the texture

	int                         mCellWidth;
	int                         mCellHeight;

	float                       mTime;              // current time position (in seconds)

public:
	Animation(SDL_Texture* tex, int numCells, float duration, bool loopable, Direction defaultDir);
	~Animation();

	void                        AddTime(float dt);

	void                        Draw(SDL_Renderer* renderer, const SDL_Rect* dstRect, Direction dir);
};

#endif

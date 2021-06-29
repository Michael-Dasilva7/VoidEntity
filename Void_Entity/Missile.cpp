#include <iostream>

#include "Missile.h"

const int Missile::msDefaultWidth = 64;
const int Missile::msDefaultHeight = 64;

const SDL_Color	Missile::msDefaultColor = { 255, 255, 255, 255 };		// white


Missile::Missile()
	: Missile(0, 0, NULL, msDefaultColor)		// C++11 delegating constructors ftw
{
}

Missile::Missile(SDL_Texture* tex)
	: Missile(0, 0, tex, msDefaultColor)
{
}

Missile::Missile(int x, int y, SDL_Texture* tex)
	: Missile(x, y, tex, msDefaultColor)
{
}

Missile::Missile(int x, int y, SDL_Texture* tex, const SDL_Color& color)
	: mRect()
	, mColor()
    , mTex(tex)
    , mSpeedX(0)
    , mSpeedY(0)
{
    int w = msDefaultWidth;
    int h = msDefaultHeight;

    // if the texture is not NULL, get its size
    if (tex) {
        if (SDL_QueryTexture(tex, NULL, NULL, &w, &h) < 0) {                                        // <--- ###
            std::cerr << "*** Failed to query player texture: " << SDL_GetError() << std::endl;
        } 
    }

	mRect.w = w;
	mRect.h = h;
	
    mRect.x = x;
	mRect.y = y;

    mColor = color;		// struct bitwise copy
}

Missile::~Missile()
{
    std::cout << "Missile destroyed" << std::endl;
}

SDL_Point Missile::Center() const
{
	SDL_Point p;
	p.x = Left() + Width() / 2;
	p.y = Top() + Height() / 2;
	return p;
}

void Missile::SetCenter(int x, int y)
{
	SetLeft(x - Width() / 2);
	SetTop(y - Height() / 2);
}

void Missile::Move(int dx, int dy)
{
	mRect.x += dx;
	mRect.y += dy;
}

void Missile::Update()
{
    mRect.x += mSpeedX;
    mRect.y += mSpeedY;
}

void Missile::Draw(SDL_Renderer* renderer) const
{
    // check if we have a valid texture
    if (mTex) {
        // draw textured rectangle
        SDL_RenderCopy(renderer, mTex, NULL, &mRect);                               // <--- ###
    } else {
        // draw solid rectangle
        SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);
        SDL_RenderFillRect(renderer, &mRect);
    }
}

void Missile::SetSpeed(int sx, int sy)
{
    mSpeedX = sx;
    mSpeedY = sy;
}

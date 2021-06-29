#include <iostream>
#include "Player.h"

const int Player::msDefaultWidth = 64;
const int Player::msDefaultHeight = 64;

const SDL_Color	Player::msDefaultColor = { 255, 255, 255, 255 };		// white

Player::Player()
	: Player(0, 0, NULL, msDefaultColor)		// C++11 delegating constructors ftw
{
}

Player::Player(SDL_Texture* tex)
	: Player(0, 0, tex, msDefaultColor)
{
}

Player::Player(int x, int y, SDL_Texture* tex)
	: Player(x, y, tex, msDefaultColor)
{
}

Player::Player(int x, int y, SDL_Texture* tex, const SDL_Color& color)
	: mRect()
	, mColor()
    , mTex(tex)
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
	mCurrentLives = 0;
		
    mColor = color;		// struct bitwise copy
}

SDL_Point Player::Center() const
{
	SDL_Point p;
	p.x = Left() + Width() / 2;
	p.y = Top() + Height() / 2;
	return p;
}

void Player::SetCenter(int x, int y)
{
	SetLeft(x - Width() / 2);
	SetTop(y - Height() / 2);
}

void Player::Move(int dx, int dy)
{
	mRect.x += dx;
	mRect.y += dy;
}

void Player::setLives(int lifeCount)
{
	mCurrentLives = lifeCount;
}

void Player::Update(const Uint8* keys)
{
    // update position based on current keyboard state
    //

   
    if (keys[SDL_SCANCODE_D] ) {
		
        mRect.x += 4;
		if (mRect.x > 900- mRect.w){ mRect.x += 4; }
	}
    if (keys[SDL_SCANCODE_A]) {
		mRect.x -= 4;
		if (mRect.x < 0){ mRect.x += 4; }
    }
    if (keys[SDL_SCANCODE_W]) {
		mRect.y -= 4;
		if (mRect.y < 0){ mRect.y += 4; }
    }
    if (keys[SDL_SCANCODE_S]) {
		mRect.y += 4;
		if (mRect.y > 600 - mRect.h){ mRect.y -= 4; }
    }
}
bool Player::isCollision(int x, int y)
{
		if ((x > mRect.x && x < Right()) && (y < Bottom() && y > Top()))
		{
			return true;
		}
		else
		{
			return false;
		}

}
void Player::Draw(SDL_Renderer* renderer) const
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

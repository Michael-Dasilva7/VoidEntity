#include "StraightFlier.h"
#include <stdio.h>
#include <iostream>
/*
basic enemy ship
*/

void StraightFlier::Move(int x, int y){ mRect.x += x, mRect.y += y; }
void StraightFlier::Initialize(){}
//takes an objects x and y to compare for collision
bool StraightFlier::isCollision(int x, int y)
{
	if ((x > mRect.x && x < Right()) && (y < Bottom() && y > Top()))
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}
void StraightFlier::setVelocity(int velX, int velY){ mVelocityX = velX; mVelocityY = velY; }    //set enemies horizontal and vertical speed
void StraightFlier::Update(){ mRect.x -= mVelocityX;  };          //minus velocity variable as Enemies move left towards player typically
void StraightFlier::Draw(SDL_Renderer* renderer) 
{
	if (mTex)
	{
		//std::cout << "drawing enemy" << std::endl;
		//draw the full texture where its SDL_Rect object's x and y members specify it to 
		SDL_RenderCopy(renderer, mTex, NULL, &mRect);
		//if (mIsExploding<--make this a member) DSL_Rendercopy - ExplosionTex
	}
	else
	{
		std::cout << "There has been a problem in the draw method" << std::endl;
	}
}
#ifndef STRAIGHFLIER_H_
#define STRAIGHFLIER_H_

#include <SDL.h>
#include <list>
#include "Player.h"
#include "Missile.h"
#include "Enemy.h"
#include "Animation.h"
/*
This enemy is going to be the most basic enemy that barely moves and barely shoots
*/

class StraightFlier : public Enemy
{
    int						mVelocityX;
    int						mVelocityY;
    SDL_Rect				mRect;
    SDL_Color* mColor;     // fallback color, in case there are problems with the texture
    SDL_Texture* mTex;
    SDL_Texture* mLazer;     //Bullet texture that is this enemy's standard weapon
public:
    StraightFlier() : Enemy() {};
    StraightFlier(SDL_Texture* tex, int x, int y) {

        mTex = tex;
        mRect.x = x;
        mRect.y = y;
        mRect.w = 64;
        mRect.h = 64;
    };

    StraightFlier(SDL_Texture* tex, SDL_Texture* missileTex, int x, int y) : Enemy(tex, x, y) {};//StraightFlier(SDL_Texture* shipTex, SDL_Texture* mLazer, int x, int y) {};
    //~StraightFlier();

    void Move(int x, int y);
    int	Left() const { return mRect.x; }
    int	Top() const { return mRect.y; }
    int Right() const { return mRect.x + mRect.w; }
    int	Bottom() const { return mRect.y + mRect.h; }

    int getWidth() const { return mRect.w; }; //return mRect.w;
    int getHeight() const { return mRect.h; };//return mRect.h;

    void setVelocity(int velX, int velY);//set specified speed
    void Initialize();

    void Update();
    void Draw(SDL_Renderer* renderer);
    bool isCollision(int x, int y);

    int scoreCount() override { return 114; };

};
#endif
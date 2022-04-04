#ifndef MISSILE_H_
#define MISSILE_H_

#include <SDL.h>
#include "Animation.h"

class Missile
{
	SDL_Rect				mRect;
    SDL_Color				mColor;     // fallback color, in case there are problems with the texture

    SDL_Texture*            mTex;                                                   // <--- ###

    int                     mSpeedX;
    int                     mSpeedY;
	
public:
							Missile();
							Missile(SDL_Texture* tex);
                            Missile(int x, int y, SDL_Texture* tex);
							Missile(int x, int y, SDL_Texture* tex, const SDL_Color& color);

                            ~Missile();

	int						Width() const		{ return mRect.w; }
	int						Height() const		{ return mRect.h; }

	int						Left() const		{ return mRect.x; }
	int						Top() const			{ return mRect.y; }
	int						Right() const		{ return mRect.x + mRect.w; }
	int						Bottom() const		{ return mRect.y + mRect.h; }

	SDL_Point				Center() const;

	void					SetLeft(int x)		{ mRect.x = x; }
	void					SetRight(int x)		{ mRect.x = x - mRect.w; }
	void					SetTop(int y)		{ mRect.y = y; }
	void					SetBottom(int y)	{ mRect.y = y - mRect.h; }

	void					SetWidth(int w)		{ mRect.w = w; }
	void					SetHeight(int h)	{ mRect.h = h; }

	void					SetCenter(int x, int y);

	void					Move(int dx, int dy);

	void					SetColor(SDL_Color color)						{ mColor = color; }
	void					SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)	{ mColor.r = r; mColor.g = g; mColor.b = b; mColor.a = a; }

	void					Update();
	void					Draw(SDL_Renderer* renderer) const;

    void                    SetSpeed(int sx, int sy);

private:
	static const int		msDefaultWidth;
	static const int		msDefaultHeight;

	static const SDL_Color	msDefaultColor;
};

#endif

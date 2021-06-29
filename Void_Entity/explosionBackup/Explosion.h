#include <SDL.h>
class Explosion
{

	SDL_Rect				mRect;
	SDL_Color				mColor;

	SDL_Texture*            mTex;
	int						mAnimationFrame;

public:
	Explosion();
	Explosion(SDL_Texture* tex, int x, int y);
	bool					mDurationComplete;
	void                    Update();
	void                    Draw(SDL_Renderer* renderer);
	int						Left() const		{ return mRect.x; }
	int						Top() const			{ return mRect.y; }
	int						Right() const		{ return mRect.x + mRect.w; }
	int						Bottom() const		{ return mRect.y + mRect.h; }

	~Explosion();

private:
	static const int		msDefaultWidth;
	static const int		msDefaultHeight;
	static const int		msExplosionCount;
};


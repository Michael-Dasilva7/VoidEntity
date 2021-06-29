#include "Game.h"

#include "Missile.h"

#include <iostream>

void Game::ProcessEvents()
{
    SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			OnQuit();
			break;
		case SDL_KEYDOWN:
			//OnKeyDown(&e.key);
			mCurrentState->OnKeyDown(e.key);
			break;
		case SDL_KEYUP:
			//OnKeyUp(&e.key);
            mCurrentState->OnKeyUp(e.key);
			break;
		case SDL_MOUSEBUTTONDOWN:
			//OnMouseDown(&e.button);
			mCurrentState->OnMouseDown(e.button);
			break;
		case SDL_MOUSEBUTTONUP:
			//OnMouseUp(&e.button);
            mCurrentState->OnMouseUp(e.button);
			break;
		case SDL_MOUSEMOTION:
			//OnMouseMotion(&e.motion);
            mCurrentState->OnMouseMotion(e.motion);
			break;
		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
				//OnWindowResized(e.window.data1, e.window.data2);
                mCurrentState->OnWindowResized(e.window.data1, e.window.data2);
			}
			break;
		default:
			break;
		}
	}
}

void Game::OnQuit()
{
	std::cout << "Application was told to quit" << std::endl;

	mShouldQuit = true;
}

void Game::OnWindowResized(int w, int h)
{
	std::cout << "Window resized to " << w << 'x' << h << std::endl;
	mScreenWidth = w;
	mScreenHeight = h;
}

void Game::OnKeyDown(const SDL_KeyboardEvent* kbe)
{
}

void Game::OnKeyUp(const SDL_KeyboardEvent* kbe)
{
}

void Game::OnMouseDown(const SDL_MouseButtonEvent* mbe)
{
}

void Game::OnMouseUp(const SDL_MouseButtonEvent* mbe)
{
}

void Game::OnMouseMotion(const SDL_MouseMotionEvent* mme)
{
}

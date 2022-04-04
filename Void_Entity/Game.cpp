#include "Game.h"
#include "Texture.h"
#include "Gameplay.h"
#include "MainMenu.h"
#include "Sound.h"
#include <SDL_image.h>
#include <iostream>

Game::Game()
    : mScreenWidth(900)//screen size
    , mScreenHeight(600)//screen size
    , mWindow(NULL)
    , mKeys(NULL)
    , mRenderer(NULL)
    , mShouldQuit(false)
    , mGameplayState(NULL)
    , mMainMenuState(NULL)
    , mCurrentState(NULL)
    , mSound(NULL)
{
}
bool Game::Run()
{
    // setup
    if (!Initialize()) {
        std::cerr << "*** Game initialization failed" << std::endl;
        return false;
    }

    // game loop
    while (!mShouldQuit) {

        ProcessEvents();
        Update();
        Draw();


    }

    // cleanup
    Shutdown();

    return true;
}
bool Game::Initialize()
{
    std::cout << "Initializing game" << std::endl;

    //
    // initialize SDL
    //
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "*** Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    // initialize SDL_image add-on
    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {                                           // <--- ###
        std::cerr << "*** Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
        return 1;
    }

    //
    // create a window
    //
    mWindow = SDL_CreateWindow("Void Entity",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        mScreenWidth, mScreenHeight,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!mWindow)
    {
        std::cerr << "*** Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    //
    // get a pointer to keyboard state managed by SDL
    //
    mKeys = SDL_GetKeyboardState(NULL);

    //
    // create a renderer that takes care of drawing stuff to the window
    //
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        std::cerr << "*** Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    //
    //initialize the sounds
    //
    mSound = new Sound();
    mSound->Init();


    //
    // create all game states
    //
    mGameplayState = new Gameplay(this, mSound);
    mGameplayState->Initialize();



    mGameOverState = new GameOver(this, mSound);
    mGameOverState->Initialize();

    mMainMenuState = new MainMenu(this, mSound);
    mMainMenuState->Initialize();
    // set initial state
    mCurrentState = mMainMenuState;

    return true;
}
void Game::Shutdown()
{
    std::cout << "Shutting down game" << std::endl;

    mGameplayState->Shutdown();
    mMainMenuState->Shutdown();

    delete mGameplayState;
    delete mMainMenuState;

    // unload the image loading library
    IMG_Quit();                                                                     // <--- ###

    // this closes the window and shuts down SDL
    SDL_Quit();
}
void Game::Update()
{
    mCurrentState->Update();
}
void Game::Draw()
{
    mCurrentState->Draw();
    // tell the renderer to display everything we just drew
    SDL_RenderPresent(mRenderer);
}
void Game::EnterMainMenu()
{
    mCurrentState = mMainMenuState;
}
void Game::EnterGameplay()
{
    mCurrentState = mGameplayState;
}
void Game::EnterGameover()
{
    mCurrentState = mGameOverState;
}
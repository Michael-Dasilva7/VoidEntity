#include "Gameplay.h"
#include "Texture.h"
#include "Game.h"
#include "Sound.h"
#include <iostream>
#include "Animation.h"
#include "ResourceManager.h"

/*
    EnemyAI
*/
Gameplay::Gameplay(Game* game, Sound* sound) : GameState(game, sound)
, mPlayer(NULL)
, mMissiles()
, mPlayerTex(NULL)
, mShotTex(NULL)
, mBackgroundTex1(NULL)
, mBackgroundTex2(NULL)
, mBackgroundTex3(NULL)
, mBackgroundTex4(NULL)
, mIsActive(false)
, mBackground1Pos(mGame->GetScreenWidth())
, mBackground2Pos(mGame->GetScreenWidth())
, mBackground3Pos(mGame->GetScreenWidth())
, mBackground4Pos(mGame->GetScreenWidth())
, mScrollDelayer(0)
, mCurrentSound(sound)
, mLastTime(1) // maybe add to gamestate later because all gamestates need to know current time for stuffs
, mFlierTex(NULL)
, mFliers(NULL)
, mEnemyCount(0)
, mPlayerLives(0)
, mMissleCount(0) {
}
Gameplay::~Gameplay()
{
}
void Gameplay::Initialize()
{
    SDL_Renderer* renderer = mGame->GetRenderer();
    //
    // load texture
    //
    mPlayerTex = LoadTexture("media/player/shuttle.png", renderer);
    mShotTex = LoadTexture("media/player/shot.png", renderer);
    mBackgroundTex1 = LoadTexture("media/backgrounds/background1.png", renderer);
    mBackgroundTex2 = LoadTexture("media/backgrounds/background2.png", renderer);
    mBackgroundTex3 = LoadTexture("media/backgrounds/background3.png", renderer);
    mBackgroundTex4 = LoadTexture("media/backgrounds/background4.png", renderer);
    mExplosionTex = LoadTexture("media/effects/explosion.tga", renderer);
    mTextAndNumbers = LoadTexture("media/text/DialogueText_16x16.png", renderer);

    ResourceManager::textImage = mTextAndNumbers;

    //y = 199 to 
    //x = 27,
    //w = 26

    //separated by 5 pixels
    mMissleAnimations = LoadTexture("media/effects/missleEffects.png", renderer);

    //load enemy
    mFlierTex = LoadTexture("media/enemies/enemy.png", renderer);

    std::cout << "screen width " << mGame->GetScreenWidth() << std::endl;
    std::cout << "screen heigjht " << mGame->GetScreenHeight() << std::endl;

    std::cout << "background Pos 1 " << mBackground1Pos << std::endl;

    //load sound for gameplay
    LoadLevel();
    mIsLevelOnePhaseOne = true;
    mIsLevelOnePhaseTwo = false;
    mIsLevelOnePhaseThree = false;

    mIsLevelTwoPhaseOne = false;
    mIsLevelTwoPhaseTwo = false;
    mIsLevelTwoPhaseThree = false;
    mEnemyKillCount = 0;
    mPauseEnemyGeneration = false;
}

void Gameplay::Shutdown()
{
    ClearLevel();

    // delete the textures and save the day!
    SDL_DestroyTexture(mPlayerTex);
    SDL_DestroyTexture(mBackgroundTex1);
    SDL_DestroyTexture(mBackgroundTex2);
    SDL_DestroyTexture(mBackgroundTex3);
    SDL_DestroyTexture(mBackgroundTex4);

    SDL_DestroyTexture(mExplosionTex);
    SDL_DestroyTexture(mTextAndNumbers);

    SDL_DestroyTexture(mFlierTex);
    SDL_DestroyTexture(mShotTex);
    //add enemy an sound deconstructors
}

void Gameplay::LoadLevel()
{
    ClearLevel();
    mSound->levelOneTheme();
    //
    // initialize the player
    //
    mPlayerLives = 3;
    mPlayer = new Player(mPlayerTex);
    mPlayer->setLives(3);
    mPlayer->SetColor(192, 0, 164, 255);                        // set fallback color
    mPlayer->SetCenter(30, mGame->GetScreenHeight() / 2);

    mHighScore = 0;//each levelmight need to carry this over. if statement with a level incrementer

    ResourceManager::PopulateCharacterRects();

}

void Gameplay::ClearLevel()
{
    delete mPlayer;
    mPlayer = NULL;

    for (auto it = mMissiles.begin(); it != mMissiles.end(); it++) {
        Missile* m = *it;
        delete m;
    }
    mMissleCount = 0;
    mEnemyCount = 0;
    mFliers.clear();
    mMissiles.clear();
    mPlayer = NULL;

}

void Gameplay::Update()
{
    //bool isBoss = false;
    bool mIsDestroyed = false;
    //bool mIsPlayerDestroyed;
    //mLastTime
    mCurrentTime = (SDL_GetTicks() / 1000); // current time in seconds


    /*
    TODO

        1. Add an enemy killed count. and reduce # of enemies that spawn. once we reach that enemy count, STOP SPAWNING MORE
        2. Once all enemies are off the screen / killed. BRING IN THE NEW BOSS WITH AI.
        3. add a flash when the boss is killed, plus more health!!
        4. once he is dead, victory music!
        5. next level.
        6. ADD HIGH SCORE THAT IS SAVED AFTER SCREEN CLOSES. take file save logic from other game
        7. Moving up and down changes the
        8. better looking shooting animation!!
        9. holding down the button will shoot rapid fire!
        10. more bullets!
        11. powerups
        12. glitch where after death can exit and go back in
        13. pause keeps background moving
        14. textures disappear on end game
        15.  INSTRUCTIONS - > Space = shoot, up, down, left, right, ESC to bring up MENU
*/


    if (mLastTime % 4)
    {
        //activeEnemy = new StraightFlier();

        if (mEnemyCount < 10 && !mPauseEnemyGeneration)
        {
            StraightFlier* activeEnemy = new StraightFlier(mFlierTex, mGame->GetScreenWidth() + 64, 10 + rand() % 550);
            activeEnemy->setVelocity((rand() % 3) + 1, 0); //set
            mFliers.push_back(activeEnemy);
            mLastTime = 0;
            mEnemyCount++;

        }
        else if (mIsLevelOnePhaseThree) {
            //ADD BOSS TO THE enemy list m

        }


    }

    //iterate through enemies and check every bullet location in relation to current enemy
    for (auto it = mFliers.begin(); it != mFliers.end();)
    {

        StraightFlier* e = *it;

        //check every missles location
        for (auto it2 = mMissiles.begin(); it2 != mMissiles.end();)
        {
            Missile* m = *it2; // point to current missle		
            if (e->isCollision(m->Left(), m->Top()))//if current missile is inside of the enemy
            {
                delete m;
                it2 = mMissiles.erase(it2);
                mMissleCount--;
                mIsDestroyed = true;
                break;
            }
            //else if( e->isCollide(playerx,playery) ) player and enemy explode and dead = true which leadsto ending game loop
            else
            {
                it2++;//check next missle
            }
            //add explosion at location if collision
        }
        if (e->isCollision(mPlayer->Right(), mPlayer->Top()) || e->isCollision(mPlayer->Left(), mPlayer->Top()) || e->isCollision(mPlayer->Left(), mPlayer->Bottom()) || e->isCollision(mPlayer->Right(), mPlayer->Bottom()))
        {
            --mPlayerLives;
            mIsDestroyed = true;
            if (mPlayerLives <= 0)
            {
                mIsActive = false;
                mSound->stopMusic();
                mGame->EnterGameover();
            }
            else//player is destroyed and revived 
            {
                //is destroyed therefore we need to add a new explosion to the list
                mSound->playExplosion();
                Explosion* explode = new Explosion(mExplosionTex, mPlayer->Left(), mPlayer->Top());
                mExplosions.push_back(explode);
                std::cout << "Player Destroyed at(seconds): " << mCurrentTime << std::endl;
                mPlayer->SetCenter(30, mGame->GetScreenHeight() / 2);
            }
        }
        if ((e->Left() < 0 - e->getWidth()) /*&& !mIsDestroyed*/)
        {
            it = mFliers.erase(it);
            delete e;
            mEnemyCount--;
        }
        else if (mIsDestroyed)
        {
            //is destroyed therefore we need to add a new explosion to the list
            mSound->playExplosion();
            Explosion* explode = new Explosion(mExplosionTex, e->Left(), e->Top());
            mExplosions.push_back(explode);

            mEnemyCount--;
            mEnemyKillCount++;

            if (mEnemyKillCount > 25) {
                mPauseEnemyGeneration = true;
                mIsLevelOnePhaseOne = false;
                mIsLevelOnePhaseTwo = true;
            }
            mHighScore += (*it)->scoreCount();

            it = mFliers.erase(it);

            delete e;

            std::cout << "Enemy Destroyed at(seconds): " << mCurrentTime << std::endl;

            mIsDestroyed = false;

        }
        else
        {
            //std::cout << "Update Enemy " << mCurrentTime << std::endl;
            e->Update();
            it++;
        }

    }

    for (auto it = mMissiles.begin(); it != mMissiles.end();) {
        Missile* m = *it;

        m->Update();
        //check if missles are off screen - by checking their left edge is past right side of screen
        if (m->Left() > mGame->GetScreenWidth())
        {
            it = mMissiles.erase(it);
            mMissleCount--;
            delete m;
        }
        else {

            it++;
        }
    }

    for (auto it = mExplosions.begin(); it != mExplosions.end();)//check explosions an update
    {
        Explosion* e = *it;

        if (e->mDurationComplete)//if explosion over delete it
        {
            it = mExplosions.erase(it);//remove from list

            delete e;//delete from list
        }
        else
        {
            float dx = ((float)SDL_GetTicks() / 1000) - mLastTime;
            e->Update(dx * .21f);//update explosion if not finished animation

            it++;
        }
        //mMissleCount--;
    }
    mIsActive = true;


    //set last time to current time to check it against next iteration of this update
    mLastTime = mCurrentTime;
    mPlayer->Update(mGame->GetKeys());

    //updateScore
    //so i have a score. then i need to
    //should i have a score object?
    //the farther back the background the slower it moved
    mBackground1Pos += 3;
    mBackground2Pos += 4;
    mBackground3Pos += 6;

}
void Gameplay::Draw()
{
    SDL_Renderer* renderer = mGame->GetRenderer();

    int screenWidth = mGame->GetScreenWidth();
    int screenHeight = mGame->GetScreenWidth();

    // clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, mBackgroundTex1, NULL, NULL);

    //6364 x 720
    //dest rect should ALWAYS been the screen width and height unless specifically needed otherwise.
    dstRect.h = screenHeight;
    dstRect.w = screenWidth;

    srcRect.w = screenWidth;
    srcRect.h = screenHeight;
    srcRect.y = 0;

    //std::cout << "mBackground1Pos " << mBackground1Pos << std::endl;
    //std::cout << "mBackground2Pos " << mBackground2Pos << std::endl;
    //std::cout << "mBackground3Pos " << mBackground3Pos << std::endl;
    //std::cout << "mBackground4Pos " << mBackground4Pos << std::endl;

    // **************************************PARRALLAX START*****************************************************//

    // There is a point in the texture we NEED to repeat at, or else the start wont equal the end and it will be a choppy repeat.
    // so we either stop at a point in the texture width at the repeat point

    //Fractal Far Back Background 1:
    if (mBackground1Pos >= 5089) {
        mBackground1Pos = 0;
    }
    srcRect.x = mBackground1Pos;
    SDL_RenderCopy(renderer, mBackgroundTex1, &srcRect, NULL);


    //After 10 seconds, we reach the particle field

    // Display Text:  START FIELD APPROACHING - GET READY for 5 seconds, then 2 seconds start field, then enemies

    //Star Background 2:
    // Textures are created so the end frames are the same as the first frame. so once we are at the very end, switch to the beginning frame for a smooth transition
    // (Current X Position of Bkround) - (texture width - screen width)
    if (mBackground2Pos >= 1800) {
        mBackground2Pos = 0;
    }
    else
    {
        srcRect.x = mBackground2Pos;
        SDL_RenderCopy(renderer, mBackgroundTex2, &srcRect, NULL);
    }

    //Star Background 3:
    if (mBackground3Pos >= 1800) {
        mBackground3Pos = 0;
    }
    else {
        srcRect.x = mBackground3Pos;
        SDL_RenderCopy(renderer, mBackgroundTex3, &srcRect, NULL);

    }
    // ************************************** PARRALLAX END *****************************************************//



    // draw missiles
    for (auto it = mMissiles.begin(); it != mMissiles.end(); it++) {
        Missile* m = *it;
        m->Draw(renderer);
    }

    for (auto it = mFliers.begin(); it != mFliers.end();)
    {
        StraightFlier* e = *it;
        e->Draw(renderer);
        it++;
    }

    for (auto it = mExplosions.begin(); it != mExplosions.end();)
    {
        Explosion* e = *it;
        e->Draw(renderer);
        it++;
    }



    // draw player
    mPlayer->Draw(renderer);
    // tell the renderer to display everything we just drew
    //	SDL_RenderPresent(renderer);
    SDL_Rect life = SDL_Rect();
    life.x = 700;
    life.y = 15;
    life.h = 34;
    life.w = 34;
    for (int i = 0; i < mPlayerLives; i++)
    {
        life.x += 36;
        //std::cout << "mPlayerLives" << mPlayerLives << std::endl;
        SDL_RenderCopy(renderer, mPlayerTex, NULL, &life);
    }

    //0
// 231341
// for each text, convert to ascii, find it, then scale the text up
// 
    //Display High Score!
    //mPlayerLives
    //https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
    //display high score

    //need a current high score, and BEST high score
    ResourceManager::displayText(5, 5, 15, 15, std::string("High Score: ") + std::to_string(mHighScore), renderer);
}
void Gameplay::OnKeyDown(const SDL_KeyboardEvent& kbe)
{
    switch (kbe.keysym.sym) {
    case SDLK_ESCAPE:
        std::cout << "User pressed Escape" << std::endl;
        //mGame->mShouldQuit = true;  // set quit flag
        mGame->EnterMainMenu();
        break;

    case SDLK_p:
        std::cout << mMissiles.size() << " missiles" << std::endl;
        break;
    case SDLK_SPACE:
        FirePlayerBullet();

    }
}

void Gameplay::OnMouseDown(const SDL_MouseButtonEvent& mbe) {

    switch (mbe.button) {

    case SDL_BUTTON_LEFT:
        FirePlayerBullet();
    }
}

void Gameplay::FirePlayerBullet() {
    //if there are less than 3 regular missiles on screen
    if (mMissleCount < 4)
    {
        mMissleCount++;
        //figure out how to make a bettermissle animation
        std::cout << "Creating missile" << std::endl;
        Missile* m = new Missile(mShotTex);
        SDL_Point p = mPlayer->Center();
        m->SetCenter(p.x, p.y);
        m->SetSpeed(5, 0);
        mMissiles.push_back(m);
        mCurrentSound->playLazer();

    }
}
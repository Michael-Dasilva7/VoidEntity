#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "Texture.h"
#include <string>
#include <memory>
#include <unordered_map>

/*
***********************************
* DOCUMENTATION *
***********************************

    The main purpose of this class is to manage resources and accessing resources, to make it easier and smoother overall

    Instead of having to create ALL textures in one huge unmanageable list (i.e. sdltext1, sdltext2,... sdltex999..)... we specify a NAME to the ACQUIRE method, and if that name does not
    exist it is added and a texture is loaded up. and a pointer to the texture is stored in a list.  if the name specified DOES exist, the pointer to the text returned.

    We also store a list of pointers to each character. in a list of 32/32 sized characters.
        TODO: we want to scale the characters in the future, so instead, use a 8x8 one, and the calling methods will need to scale! (i.e. dialogue action)

*/
class ResourceManager {

public:
    //static std::shared_ptr<SDL_Texture> Acquire(const std::string& name, SDL_Renderer* renderer)
    static SDL_Texture* Acquire(const std::string& name, SDL_Renderer* renderer)
    {
        const auto i = texturePtrs.find(name);
        if (i != texturePtrs.end())
        {
            return i->second;
        }
        else
        {
            //string dir = "./media";
            //auto pTex = std::make_shared<SDL_Texture>(LoadTexture(name.c_str, renderer));
            SDL_Texture* pTex = LoadTexture(name.c_str(), renderer);
            if (pTex != nullptr) {
                texturePtrs.insert({ name, pTex });
            }
            return pTex;
        }
    };

    //This method populates source rectangles for all the alphabet plus a variety of characters(i.e. @%{},etc.) based on
    // the specific format of textures and ascii values.  This needs to be updated so that 
    // textures should be in ascii order to make it a sort of standard. 
    static void PopulateCharacterRects()
    {
        int letterHeight = 16;
        int letterWidth = 16;
        std::string charsToInit = "ABCDEFGHIJKLMNOPQRSTUVWXYWabcdefghijklmnopqrstuvwxywz1234567890.!@#$%^&*()_+<>?:'\"{}\\ ";
        for (char& c : charsToInit) {
            SDL_Rect* rect;
            //rect = new SDL_Rect(0, 0, letterWidth, letterHeight);
            rect = new SDL_Rect();
            rect->h = letterHeight;
            rect->w = letterWidth;
            rect->x = 0;
            rect->y = 0;
            int index = (int)c;
            int mapping;

            bool isColonCharacter = (index == 58);
            bool isSpaceCharacter = (index == 32);
            bool isExclamationMark = (index == 33);
            bool isQuestionMark = (index == 63);
            bool isDoubleApostrophe = (index == 34);
            bool isApostrophe = (index == 39);
            bool isPeriod = (index == 46);
            //can also determine the nextXPosition based on above mapping

            int nextXPosIncrement = 38;
            if (isSpaceCharacter) {
                rect->y = 0;
                rect->x = letterWidth * 13;
            }
            else if (isColonCharacter) {
                rect->y = letterHeight * 3;
                rect->x = letterWidth;
            }
            else if (isApostrophe) {
                rect->y = letterHeight * 3;
                rect->x = letterWidth * 3;
            }
            else if (isExclamationMark) {
                rect->y = 0;
                rect->x = letterWidth * 10;
            }
            else if (isQuestionMark) {
                rect->y = 0;
                rect->x = letterWidth * 11;
            }
            else if (isPeriod) {
                rect->y = letterHeight * 3;
                rect->x = letterWidth * 5;
            }

            else if (index >= 48 && index <= 57) {
                //NUMBERS
                mapping = index % 48;
                rect->y = 0;
                rect->x = mapping * letterWidth;
            }
            else if (index >= 65 && index <= 90) {
                //UPPERCASE LETTERS
                mapping = index % 65;
                rect->y = letterHeight;
                rect->x = mapping * letterWidth;
            }
            else if (index >= 97 && index <= 122) {
                //LOWERCASE LETTERS
                mapping = index % 97;
                rect->y = letterHeight * 2;
                rect->x = mapping * letterWidth;
            }

            SDL_Rect* rectPtr = rect;
            if (rectPtr != nullptr) {
                characterTexturePtrs.insert({ index, rectPtr });
            }
        }
    };

    static SDL_Texture* textBox;
    static SDL_Texture* textImage;

    //THIS METHOD SHOULD RETURN A LIST OF TEXTURES AS THEY NEED TO BE
    //IT SHOULDNT BE RESPONSIBLE FOR RENDERING
    // what I can do...is create a texture made up of these other textures!!!!  then return it. or return an array of them
    // then the action can just take the textures and render them until input is recieved.
    //***************************************************************************************************************************************
    // https://stackoverflow.com/questions/20730900/creating-a-new-texture-from-several-textures-sdl-2/20736087
    // target_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, target_width, target_height);
    //***************************************************************************************************************************************
    static void displayText(int x, int y, int w, int h, std::string& dialogue, SDL_Renderer* renderer) {

        //MIGHT NEED A PRE MADE LIST OF POINTERS BASED ON THE STRING PASSED IN :)
        //NEED TO SAVE SOME PROCESSING POWER. OUCH
        int currentLetterXPos = x;

        //these should be the width of the characters in the texture were using. standard is 16x16. then we can scale up based
        //on whats passed in the w/h(these are the values we want them to be)
        int textureCharacterWidth = 16;
        int textureCharacterHeight = 16;

        for (char& c : dialogue) {
            SDL_Rect textRect;
            textRect.w = textureCharacterWidth;
            textRect.h = textureCharacterHeight;

            //this maps the x location of the letter
            //by casting the char to int, it gives the ascii value. these ascii values line up 
            //to the locations of the characters in the texture.
            //so we just need to multiple the # by the width to display them side by side
            int v1 = (int)c;

            //This is setting the starting Y position based on the ascii range
            //  EX: certain characters are on the first line, second, third... 
            // NUMBERS ARE ON INDEX LINE 3. (with index starting at 0, so technically 4th line)
            // Char 48 is 0, 49 is 1, 50 is 2......57 is 9
            //if (v1 >= 0 && v1 <= 15) {
            //    textRect.y = 0;
            //    textRect.x = v1 * 8;
            //}
            //else if (v1 >= 48 && v1 <= 57) {
            //    textRect.y = textureCharacterHeight * 4;
            //    textRect.x = (textureCharacterWidth)-v1;
            //}
            const auto i = characterTexturePtrs.find(v1);
            if (i != characterTexturePtrs.end()) {
                
                SDL_Rect destRect;
                destRect.w = w;
                destRect.h = h;
                destRect.x = currentLetterXPos += w;
                destRect.y = y;

                SDL_RenderCopy(renderer, textImage, i->second, &destRect);
            }
       
        }
        //create textures for # of characters in dialogue
        //Uint16 nextXPos = x;
        //for (char& c : dialogue) {
        //	//src rect is where in the texture you want to grab

        //	//dest rect is where on the screen you want to display it
        //	SDL_Rect textRect;
        //	textRect.w = 8;
        //	textRect.h = 10;			
        //	
        //	//if it is A, it will be 0. if it is B. it wil be 2. 
        //	//since the width of each text value is 8. we need to multiply this value by 8			
        //	//if the first value is between 0 and 15 (inclusive), the y value is 0 and the divisor is 65
        //	// if the value is between 16 and 32 exclusively. the y value is 10 and the divisor is 65
        //	//if the value is between 33 and 49 inclusive, the y value is 20 and the divisor is 65

        //	int v1 = (((int)c) % 65);

        //	if (v1 >= 0 && v1 <= 15) {
        //		textRect.y = 0;
        //		textRect.x = v1 * 8;
        //}

        //	nextXPos += 8;
        //	SDL_Rect destRect;
        //	destRect.w = 100;
        //	destRect.h = 100;
        //	destRect.x = nextXPos;
        //	destRect.y = y;

        //	//I THINK ITS DRAWING ONCE THEN THEY ARE GETTING OVERWRITTEN BY OTHERS IN DRAW LOOP
        //	//0.0, NULL, SDL_FLIP_NONE

        //	//SDL_RenderCopy will return 0 on success, or -1 on error
        //	SDL_RenderCopy(renderer, textImages, &textRect, &destRect);
            //this will only work for the first row.
            //once we get to the second row, we need to start back at 0. so if 

            //take this value. and map it to the text image
            //what if we get the remainder of dividing by 65? 
            //A is 65. 			

            //int texWidth = 0, texHeight = 0;

            //SDL_QueryTexture(currentTextToDisplay, NULL, NULL, &texWidth, &texHeight);
            //SDL_QueryTexture(currentTextToDisplay, NULL, NULL, &texWidth, &texHeight);
            //A ->65
            //B ->66
            //a ->97
            //b ->98

            //cout << "Ascii Value mod 65: " << ((int)c) % 65 << endl;
    }

    static bool initializeTextBoxTextures(SDL_Renderer* renderer) {
        textImage = Acquire("media/DialogueText.png", renderer);
        return true;
    }

    static std::unordered_map<int, SDL_Rect*>* getTexturePtrList() {
        return &characterTexturePtrs;
    }

    void cleanupTextures() {
        SDL_DestroyTexture(textImage);
    }

private:
    static std::unordered_map<std::string, SDL_Texture*> texturePtrs;
    static std::unordered_map<int, SDL_Rect*> characterTexturePtrs;
};

//TODO: add a deconstructor or a clear/delete of all existing texture objects and pointers, so we can cleanup a level or area if needed.\
//std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>  ResourceManager::texturePtrs;
std::unordered_map<std::string, SDL_Texture*>  ResourceManager::texturePtrs;
std::unordered_map<int, SDL_Rect*>  ResourceManager::characterTexturePtrs;

SDL_Texture* ResourceManager::textBox;
SDL_Texture* ResourceManager::textImage;

//void	ResourceManager::loadPlayerTextures(SDL_Renderer* renderer) {
//	//include the player constants file to get all these locations maybe? eh...probably not worth it, this is the manager after all. not sure. 
//	//leave asis for now unless i think of a reason to change it 
//	/*
//	mExplosionTex = LoadTexture("media/explosion.tga", renderer);
//	mMoveLeftTexture = LoadTexture("media/undineWalkLeft(4frame).png", renderer);
//	mMoveRightTexture = LoadTexture("media/undineWalk.png", renderer);
//	mMoveUpTexture = LoadTexture("media/undine_walk_up(4frame).png", renderer);
//	mMoveDownTexture = LoadTexture("media/undine_walk_down(4frame).png", renderer);
//	mRunLeftTexture = LoadTexture("media/undine_run_left(3frame).png", renderer);
//	*/
//}

// How about this:
//  1. Make a mandate so every entity must have a name
//  2. Pass in the entity and the name and a keyword... and we return it. instead of hardcoding these keywords
//     as method names 

/*
    SDL_Texture*  getUndineUp() {
    return mMoveUpTexture;
}*/

#endif
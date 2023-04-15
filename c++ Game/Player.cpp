#include "Player.h"
#include <SDL.h>
#include "Window.h"

//The dot that will move around on the screen
Player::Player() : mPosX{ 0 }, mPosY{ 0 }, mVelX{ 0 }, mVelY{ 0 } {}

void Player::handleEvent(SDL_Event& e)
{
    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_w: mVelY -= DOT_VEL; break;
        case SDLK_s: mVelY += DOT_VEL; break;
        case SDLK_a: mVelX -= DOT_VEL; break;
        case SDLK_d: mVelX += DOT_VEL; break;
        }
        
    }
    //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_w: mVelY += DOT_VEL; break;
        case SDLK_s: mVelY -= DOT_VEL; break;
        case SDLK_a: mVelX += DOT_VEL; break;
        case SDLK_d: mVelX -= DOT_VEL; break;
        }
    }
}

void Player::move(int screenWidth, int screenHeight)
{
    //Move the dot left or right
    mPosX += mVelX;

    //If the dot went too far to the left or right
    if ((mPosX < 0) || (mPosX + DOT_WIDTH > screenWidth))
    {
        //Move back
        mPosX -= mVelX;
    }
    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > screenHeight))
    {
        //Move back
        mPosY -= mVelY;
    }
    playerTexture->x = mPosX;
    playerTexture->y = mPosY;

}

void Player::render()
{
    //Show the dot
}

void Player::Update() {

}
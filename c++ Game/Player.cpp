#include "Player.h"
#include <SDL.h>

#include "Enemy.h"
#include "Window.h"
#include "Image.h"
#include "Shot.h"

int score;
//The dot that will move around on the screen
Player::Player(const char* imagePath,Window* window, int movementSpeed, std::vector<std::shared_ptr<GameObject>>* gameObjectsToCreate, std::vector<std::shared_ptr<GameObject>>* gameObjects, std::vector<GameObject*>* gameObjectsToDelete) :   GameObject{ imagePath, window }, shootWindow{window}, gameObjectsToCreate{gameObjectsToCreate},gameObjectsToDelete{gameObjectsToDelete},gameObjects{gameObjects}
{
    maxVelocity = movementSpeed;
    collider.h = 20;
    collider.w = 20;
}

void Player::HandleEvent(SDL_Event& e)
{
    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_w: yVelocity -= maxVelocity; break;
        case SDLK_s: yVelocity += maxVelocity; break;
        case SDLK_a: xVelocity -= maxVelocity; break;
        case SDLK_d: xVelocity += maxVelocity; break;
        }
        
    }
    //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_w: yVelocity += maxVelocity; break;
        case SDLK_s: yVelocity -= maxVelocity; break;
        case SDLK_a: xVelocity += maxVelocity; break;
        case SDLK_d: xVelocity -= maxVelocity; break;
        }
    }

    if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        shoot(gameObjectsToCreate,shootWindow,gameObjectsToDelete);
    }
    
}

void Player::move(int screenWidth, int screenHeight)
{
    //Move the dot left or right
    xPosition += xVelocity;

    //If the dot went too far to the left or right
    if ((xPosition < 0) || (xPosition + width > screenWidth))
    {
        //Move back
        xPosition -= xVelocity;
    }
    //Move the dot up or down
    yPosition += yVelocity;

    //If the dot went too far up or down
    if ((yPosition < 0) || (yPosition + height > screenHeight))
    {
        //Move back
        yPosition -= yVelocity;
    }
    image->x = xPosition;
    image->y = yPosition;
    collider.y = yPosition;
    collider.x = xPosition;
    
}

void Player::shoot(std::vector<std::shared_ptr<GameObject>>* gameObjects, Window* window, std::vector<GameObject*>* gameObjectsToDelete)
{
    if(deltaTime - startDeltaTime >= 1)
    {
        std::vector<Enemy*> enemies;
        
        gameObjects->push_back(std::make_unique<Shot>("Images/shot.png", window,xPosition,yPosition, 4,this->gameObjects,gameObjectsToDelete,deltaTime));
        enemies.clear();
        startDeltaTime = deltaTime;
    }
}

void Player::Update(uint32_t deltaTime) {
    move(SCREEN_WIDTH, SCREEN_HEIGHT);
    this->deltaTime = deltaTime;
}
Player::~Player()
{
    printf("~Player()");
}

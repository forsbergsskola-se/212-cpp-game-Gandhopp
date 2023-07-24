#include "Shot.h"

#include "Vector.h"
#include "Window.h"

void Shot::Update(uint32_t deltaTime)
{
    const int playerX = xPosition - SCREEN_WIDTH / 2;
    const int playerY = yPosition - SCREEN_HEIGHT / 2;
    vector direction{xMouse - static_cast<float>(playerX) / 300,yMouse - static_cast<float>(playerY) / 300};
    vector::normalize(direction.x,direction.y);
    image->x += direction.x * bulletSpeed;
    image->y += direction.y * bulletSpeed;
    collider.x = image->x;
    collider.y = image->y;
    for (const auto& obj : *this->gameObjects)
    {
        if(const auto& enemy = dynamic_cast<Enemy*>(obj.get()))
        {
            enemies.push_back(enemy);
        }
    }
    
    for (auto enemy : enemies)
    {
        // printf("enemy x:   %d \n",enemy->collider.x);
        // printf("enemy y:   %d \n",enemy->collider.y);
        if(CheckCollision(this->collider, enemy->collider))
        {
            gameObjectsToDelete->push_back(enemy);
            printf("Colliding!");
        }
    }
    if(deltaTime - startTime >= 10)
    {
        gameObjectsToDelete->push_back(this);
    }
    
}
Shot::Shot(const char* imagePath, Window* window, int playerXPos, int playerYPos, int bulletSpeed, std::vector<std::unique_ptr<GameObject>>* gameObjects,std::vector<GameObject*>* gameObjectsToDelete, uint32_t startTime):
    GameObject{imagePath, window}, startTime{startTime}, gameObjects{gameObjects},
    bulletSpeed{bulletSpeed}, gameObjectsToDelete{gameObjectsToDelete}
{
    collider.h = 30;
    collider.w = 30;
    
    xPosition = playerXPos;
    yPosition = playerYPos;
    //spawn at player position
    image->x = xPosition;
    image->y = yPosition;
    collider.x = xPosition;
    collider.y = yPosition;

    //get the mouse position from the player position
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    x = x - SCREEN_WIDTH / 2;
    y = y - SCREEN_HEIGHT / 2;
    xMouse = static_cast<float>(x) / 300;
    yMouse = static_cast<float>(y) / 300;
}

Shot::~Shot()
{
    printf("~Shot()");
}

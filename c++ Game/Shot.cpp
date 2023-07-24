#include "Shot.h"

#include "Vector.h"
#include "Window.h"

void Shot::Update()
{
    const int playerX = xPosition - SCREEN_WIDTH / 2;
    const int playerY = yPosition - SCREEN_HEIGHT / 2;
    vector direction{xMouse - static_cast<float>(playerX) / 300,yMouse - static_cast<float>(playerY) / 300};
    vector::normalize(direction.x,direction.y);
    image->x += direction.x * bulletSpeed;
    image->y += direction.y * bulletSpeed;
    collider.x = image->y;
    collider.y = image->x;
    
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
}
Shot::Shot(const char* imagePath, Window* window, int playerXPos, int playerYPos, int bulletSpeed, std::vector<Enemy*> enemies,std::vector<GameObject*>* gameObjectsToDelete):
    GameObject{imagePath, window}, bulletSpeed{bulletSpeed},enemies{std::move(enemies)}, gameObjectsToDelete{gameObjectsToDelete}
{
    collider.h = 20;
    collider.w = 20;
    
    xPosition = playerXPos;
    yPosition = playerYPos;
    //spawn at player position
    image->x = xPosition;
    image->y = yPosition;

    //get the mouse position from the player position
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    x = x - SCREEN_WIDTH / 2;
    y = y - SCREEN_HEIGHT / 2;
    xMouse = static_cast<float>(x) / 300;
    yMouse = static_cast<float>(y) / 300;
    printf("Shot()");
}

Shot::~Shot()
{
    printf("~Shot()");
}

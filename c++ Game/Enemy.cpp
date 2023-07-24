#include "Enemy.h"

#include "Window.h"

Enemy::Enemy(const char* imagePath, Window* window, Player* player, int movementSpeed, std::vector<GameObject*>* gameObjectsToDelete): GameObject{imagePath, window}, player{player}, gameObjectsToDelete{gameObjectsToDelete}
{
    collider.h = 20;
    collider.w = 20;

    int randomX = 1+ (rand() % 500);
    int randomY = 1+ (rand() % 400);
    image->x = randomX;
    image->y = randomY;
    collider.x = randomX;
    collider.y = randomY;
    maxVelocity = movementSpeed;
}

void Enemy::Update(uint32_t deltaTime)
{
    move();
    if(CheckCollision(this->collider, player->collider))
    {
        gameObjectsToDelete->push_back(player);
    }
}
void Enemy::move()
{
    if(image->x < player->xPosition)
    {
         image->x += maxVelocity;
        collider.x += maxVelocity;
    }
    if(image->x > player->xPosition)
    {
        image->x -= maxVelocity;
        collider.x -= maxVelocity;
    }
    if(image->y < player->yPosition)
    {
        image->y += maxVelocity;
        collider.y += maxVelocity;
    }
    if(image->y > player->yPosition)
    {
        image->y -= maxVelocity;
        collider.y -= maxVelocity;
    }
    
}
Enemy::~Enemy()
{
}

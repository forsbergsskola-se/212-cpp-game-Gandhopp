#include "Enemy.h"

#include "Window.h"

Enemy::Enemy(const char* imagePath, Window* window, Player* player, int movementSpeed): GameObject{imagePath, window}, player{player}
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
    printf("Enemy()");
}

void Enemy::Update(uint32_t deltaTime)
{
    move();
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
    printf("~Enemy()");
}
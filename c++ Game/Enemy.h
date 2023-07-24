#pragma once
#include "GameObject.h"
#include "Player.h"

class Enemy : public GameObject
{
    Player* player;
    std::vector<GameObject*>* gameObjectsToDelete;
public:
    Enemy(const char* imagePath, Window* window, Player* player, int movementSpeed, std::vector<GameObject*>* gameObjectsToDelete);
    void Update(uint32_t deltaTime) override;
    void move();
    ~Enemy() override;
    
};

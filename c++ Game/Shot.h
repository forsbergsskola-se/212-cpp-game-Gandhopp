#pragma once
#include <vector>

#include "Enemy.h"
#include "GameObject.h"

class Shot : public GameObject
{
    float xMouse = 0;
    float yMouse = 0;
public:
    int bulletSpeed;
    std::vector<Enemy*> enemies;
    std::vector<GameObject*>* gameObjectsToDelete;
    void Update() override;
    Shot(const char* imagePath, Window* window, int xPos, int yPos, int bulletSpeed, std::vector<Enemy*> enemies,std::vector<GameObject*>* gameObjectsToDelete);
    ~Shot() override;
};

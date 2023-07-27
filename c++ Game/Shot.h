#pragma once
#include <vector>

#include "Enemy.h"
#include "GameObject.h"

class Shot : public GameObject
{
    float xMouse = 0;
    float yMouse = 0;
    
    uint32_t startTime;
    std::vector<std::shared_ptr<GameObject>>* gameObjects;
public:
    int bulletSpeed;
    int fireRate{};
    std::vector<std::shared_ptr<GameObject>> enemies;
    std::vector<GameObject*>* gameObjectsToDelete;
    void Update(uint32_t deltaTime) override;
    Shot(const char* imagePath, Window* window, int xPos, int yPos, int bulletSpeed,std::vector<std::shared_ptr<GameObject>>* gameObjects,std::vector<GameObject*>* gameObjectsToDelete,uint32_t startTime);
    ~Shot() override;
};

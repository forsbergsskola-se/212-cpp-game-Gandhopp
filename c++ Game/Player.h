#pragma once
#include <SDL.h>
#include <vector>

#include "GameObject.h"

extern int score;
class Player : public GameObject
{
    uint32_t deltaTime;
    uint32_t startDeltaTime = 0;
public:
    
    const char* playerPath = "Images/armongus.png";

    Window* shootWindow;

    std::vector<std::shared_ptr<GameObject>>* gameObjectsToCreate;
    std::vector<GameObject*>* gameObjectsToDelete;
    std::vector<std::shared_ptr<GameObject>>* gameObjects;
    //Maximum axis velocity of the dot

    //Initializes the variables
    Player(const char* imagePath, Window* window, int movementSpeed,std::vector<std::shared_ptr<GameObject>>* gameObjectsToCreate, std::vector<std::shared_ptr<GameObject>>* gameObjects, std::vector<GameObject*>* gameObjectsToDelete);

    //Takes key presses and adjusts the dot's velocity
    void HandleEvent(SDL_Event& e) override;

    //Moves the dot
    void move(int width, int height);
    
    void shoot(std::vector<std::shared_ptr<GameObject>>*, Window* window,std::vector<GameObject*>* gameObjectsToDelete);
    

    void Update(uint32_t deltaTime) override;

    ~Player() override;
};


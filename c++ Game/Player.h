#pragma once
#include <SDL.h>
#include "GameObject.h"
class Player : public GameObject
{
public:
    
    const char* playerPath = "Images/armongus.png";

    //The dimensions of the dot
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    //Maximum axis velocity of the dot
    static const int DOT_VEL = 1;

    //Initializes the variables
    Player(const char* imagePath, Window* window);

    //Takes key presses and adjusts the dot's velocity
    void HandleEvent(SDL_Event& e) override;

    //Moves the dot
    void move(int width, int height);

    //Shows the dot on the screen
    

    void Update() override;

private:

    //The X and Y offsets of the dot
    int mPosX, mPosY;

    //The velocity of the dot
    int mVelX, mVelY;

};


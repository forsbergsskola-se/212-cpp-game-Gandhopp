#include "GameObject.h"
#include "IImageLoader.h"
#include "Window.h"
GameObject::GameObject(const char* imagePath, Window* window) : image{window->LoadImage(imagePath)}, xVelocity{ 0 }, yVelocity{ 0 }, xPosition{ 0 }, yPosition{ 0 } {

}
void GameObject::Render(Window* window)
{
    window->Render(image.get());
}
void GameObject::HandleEvent(SDL_Event& e)
{
    
}
bool GameObject::CheckCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;//If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}



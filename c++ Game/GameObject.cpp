#include "GameObject.h"
#include "IImageLoader.h"
#include "Window.h"
GameObject::GameObject(const char* imagePath, Window* window) : image{window->LoadImage(imagePath)} {

}
void GameObject::Render(Window* window)
{
    window->Render(image.get());
}

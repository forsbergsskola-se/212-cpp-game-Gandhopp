#pragma once
#include <memory>
#include "Image.h"
extern class IImageLoader;
extern class Window;


class GameObject
{
protected:
	std::unique_ptr<Image> image;
public:
	GameObject(const char* imagePath, Window* window);
	virtual void Update() = 0;
	virtual void HandleEvent(SDL_Event& e);
	virtual void Render(Window* window);
};


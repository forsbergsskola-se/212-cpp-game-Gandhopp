#pragma once
#include <memory>
#include "Image.h"
extern class IImageLoader;
extern class Window;


class GameObject
{
	
protected:
	std::unique_ptr<Image> image;
	//The velocity of the dot
	int xVelocity, yVelocity;
	
	//The dimensions of the dot
	static const int width = 20;
	static const int height = 20;
	
public:
	SDL_Rect collider;
	
	virtual ~GameObject() = default;

	//The X and Y offsets of the dot
	int xPosition, yPosition;
	int maxVelocity = 1;

	static bool CheckCollision( SDL_Rect a, SDL_Rect b );
	
	GameObject(const char* imagePath, Window* window);
	virtual void Update() = 0;
	virtual void HandleEvent(SDL_Event& e);
	virtual void Render(Window* window);
};


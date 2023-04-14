#pragma once
#include "Image.h"
#include <memory>

extern class IImageLoader;
class Window
{
	

	//The window we'll be rendering to
	SDL_Window* window{};

	//The surface contained by the window
	SDL_Surface* screenSurface{};

	bool success;

	IImageLoader* imageLoader;
public:
	Window(int width, int height, IImageLoader* imageLoader);
	~Window();

	
	bool WasSuccessfull(){ return success; }
	void Render(Image* image);
	std::unique_ptr<Image> LoadImage(const char* path);
};


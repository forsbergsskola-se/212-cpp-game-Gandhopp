#pragma once
#include "Image.h"
class Window
{
	//The window we'll be rendering to
	SDL_Window* window{};

	//The surface contained by the window
	SDL_Surface* screenSurface{};

	bool success;
public:
	Window(int width, int height);
	~Window();

	
	bool WasSuccessfull(){ return success; }
	void Render(Image& image);
};


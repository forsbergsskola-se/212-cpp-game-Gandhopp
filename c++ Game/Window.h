#pragma once
#include "Image.h"
#include <memory>
#include "TextRender.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;

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
	SDL_Renderer* renderer{};
	void clear();
	void present();

	Window(int width, int height, IImageLoader* imageLoader);
	~Window();

	
	bool WasSuccessfull(){ return success; }
	void Render(Image* image);
	void Render(TextRenderer& image);
	std::unique_ptr<Image> LoadImage(const char* path);
};


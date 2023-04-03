#include "Window.h"
#include <cstdio>
#include <SDL.h>

Window::Window(int width, int height) : success{}
{
	//Initialization flag

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return;
	}


	//Create window
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}


	//Get window surface
	screenSurface = SDL_GetWindowSurface(window);
	success = true;


}
Window::~Window() {

	//Destroy window
	SDL_DestroyWindow(window);
	window = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}
void Window::Render(Image& image) {
	//Apply the image
	SDL_BlitSurface(image.GetResource(), nullptr, screenSurface, nullptr);



	//Update the surface
	SDL_UpdateWindowSurface(window);
}
#include "Image.h"
#include <SDL.h>
#include <cstdio>
bool Image::loadMedia(const char* path)
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gHelloWorld = SDL_LoadBMP(path);
	if (gHelloWorld == nullptr)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "Images/Gilbert.bmp", SDL_GetError());
		success = false;
	}

	return success;
}
Image::~Image() {
	//Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;
}
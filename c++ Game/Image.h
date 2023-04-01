#pragma once
#include <SDL.h>
class Image
{
	bool loadMedia(const char* path);
	
	//The image we will load and show on the screen
	SDL_Surface* gHelloWorld{};

	bool success;
public:
	Image(const char* path)
	{
		success = loadMedia(path);
	}

	~Image();
	
	bool WasSuccesfull() {return success;}
	SDL_Surface* GetResource() { return gHelloWorld; };
};


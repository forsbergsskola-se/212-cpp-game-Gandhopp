/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Window.h"
#include "Image.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	Window window{ SCREEN_WIDTH ,SCREEN_HEIGHT };
	//Start up SDL and create window
	if (!window.WasSuccessfull())
	{
		printf("Failed to initialize!\n");
		return -1;
	}
	Image image{ "Images/Gilbert.bmp" };

	//Load media
	if (!image.WasSuccesfull())
	{
		printf("Failed to load media!\n");
		return -1;
	}
	

	//Hack to get window to stay up
	SDL_Event e; bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;
		}
		window.Render(image);
	}

	return 0;
}

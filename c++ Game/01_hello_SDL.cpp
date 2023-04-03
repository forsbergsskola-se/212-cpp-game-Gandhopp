/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Window.h"
#include "Image.h"
#include <map>
#include <memory>
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum class KeyPressSurfaces {
	Default = 0,
	Up = 1,
	Down = 2,
	Left = 3,
	Right = 4,
	Total = 5
};

const char* imageNames[]{
	"Images/press.bmp",
	"Images/up.bmp",
	"Images/down.bmp",
	"Images/left.bmp",
	"Images/right.bmp",

};

std::map<SDL_KeyCode, const char*> surfaceMap = {
	{SDL_KeyCode::SDLK_UP,"Images/up.bmp"},
	{SDL_KeyCode::SDLK_DOWN,"Images/down.bmp"},
	{SDL_KeyCode::SDLK_LEFT,"Images/left.bmp"},
	{SDL_KeyCode::SDLK_RIGHT,"Images/right.bmp"},


};

const char* fallbackSurface{ "Images/press.bmp" };

int main(int argc, char* args[])
{
	Window window{ SCREEN_WIDTH ,SCREEN_HEIGHT };
	//Start up SDL and create window
	if (!window.WasSuccessfull())
	{
		printf("Failed to initialize!\n");
		return -1;
	}
	auto image = std::make_unique<Image>( fallbackSurface );

	//Load media
	if (!image->WasSuccesfull())
	{
		printf("Failed to load media!\n");
		return -1;
	}


	//Hack to get window to stay up
	SDL_Event e; bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&e)) {
			switch (e.type)
			{
			case SDL_QUIT: {
				quit = true;
				
			}break;
			case SDL_KEYDOWN: {
				if (auto result = surfaceMap.find((SDL_KeyCode)e.key.keysym.sym); result != surfaceMap.end()) {
					auto value = *result;
					auto imageName = value.second;
					image = std::make_unique<Image>(imageName);
				}
				else {
					image = std::make_unique<Image>(fallbackSurface);
					
				}
			}break;
			}
		}
		window.Render(image.get());
	}

	return 0;
}

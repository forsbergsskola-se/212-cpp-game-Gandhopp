/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Window.h"
#include "Image.h"
#include "Player.h"
#include <map>
#include <memory>
#include "SDLImageLoader.h"

//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;

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
std::map<SDL_KeyCode, const char*> inputMap = {
	{SDL_KeyCode::SDLK_w,"Images/up.bmp"},
	{SDL_KeyCode::SDLK_s,"Images/down.bmp"},
	{SDL_KeyCode::SDLK_a,"Images/left.bmp"},
	{SDL_KeyCode::SDLK_d,"Images/right.bmp"},
	

};

const char* fallbackSurface{ "Images/press.bmp" };

int main(int argc, char* args[])
{
	IImageLoader* imageLoader = new SDLImageLoader{};
	Window window{ SCREEN_WIDTH ,SCREEN_HEIGHT, imageLoader};

	Player player;
	player.playerTexture = window.LoadImage(player.playerPath);

	auto image = window.LoadImage(fallbackSurface);

	//Start up SDL and create window
	if (!window.WasSuccessfull())
	{
		printf("Failed to initialize!\n");
		return -1;
	}

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
			player.handleEvent(e);

			switch (e.type)
			{
			case SDL_QUIT: {
				quit = true;
				
			}break;
			case SDL_KEYDOWN: {
				const char* imgPath = fallbackSurface;
				if (auto result = inputMap.find((SDL_KeyCode)e.key.keysym.sym); result != inputMap.end()) {
					auto imgPath = result->second;
					printf("Input");
				}
				image = window.LoadImage(imgPath);
				if (!image->WasSuccesfull()) {
					printf("Failed to load media!\n");
					return -1;
				}
			}break;
			}
		}
		player.move(SCREEN_WIDTH, SCREEN_HEIGHT);

		//window.Render(image.get());
		window.Render(player.playerTexture.get());
		
		SDL_Delay(50);
	}

	return 0;
}

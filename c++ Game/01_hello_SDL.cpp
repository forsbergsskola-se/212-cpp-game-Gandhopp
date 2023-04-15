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
#include "SDL_ImageImageLoader.h"
#include <vector>
#include "GameObject.h"

//Screen dimension constants


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

const unsigned int FPS = 60;
const unsigned int MS_PER_FRAME = 1000 / FPS;

int main(int argc, char* args[])
{
	IImageLoader* imageLoader = new SDL_ImageImageLoader{};
	Window window{ SCREEN_WIDTH ,SCREEN_HEIGHT, imageLoader};

	Player player;
	player.playerTexture = window.LoadImage(player.playerPath);

	auto image = window.LoadImage(fallbackSurface);

	std::vector<GameObject*> gameObjects{};

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

	unsigned int frameStartMs;

	while (quit == false) {
		frameStartMs = SDL_GetTicks();
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

		window.clear();
		//window.Render(image.get());
		window.Render(player.playerTexture.get());

		window.present();
		
		unsigned int frameTimeMs = SDL_GetTicks() - frameStartMs;
		if (frameTimeMs < MS_PER_FRAME) {
			SDL_Delay(MS_PER_FRAME - frameTimeMs);
		}

	}

	return 0;
}

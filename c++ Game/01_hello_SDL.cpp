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

	auto image = window.LoadImage(fallbackSurface);

	std::vector<GameObject*> gameObjects{};

	gameObjects.push_back(new Player{"Images/armongus.png",&window});


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
	bool quit = false;

	unsigned int frameStartMs;
	SDL_Event e;

	while (quit == false) {
		frameStartMs = SDL_GetTicks();
		
		
		while (SDL_PollEvent(&e)) {
			
			for (auto gameObject : gameObjects) {
				gameObject->Update();
			}
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
			for (auto gameobject : gameObjects) {
				gameobject->HandleEvent(e);
			}
		}
		
		for (auto gameobject : gameObjects) {
			gameobject->Update();
		}
		window.clear();
		//window.Render(image.get());

		for (auto gameobject : gameObjects) {
			gameobject->Render(&window);
		}
		window.present();
		
		unsigned int frameTimeMs = SDL_GetTicks() - frameStartMs;
		if (frameTimeMs < MS_PER_FRAME) {
			SDL_Delay(MS_PER_FRAME - frameTimeMs);
		}

	}

	return 0;
}

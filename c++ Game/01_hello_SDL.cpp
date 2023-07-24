/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <cstdio>
#include "Window.h"
#include "Player.h"
#include <map>
#include <memory>
#include "SDL_ImageImageLoader.h"
#include <vector>
#include <iostream>
#include <string>

#include "Enemy.h"
#include "GameObject.h"

//Screen dimension constants

constexpr unsigned int FPS = 60;
constexpr unsigned int MS_PER_FRAME = 1000 / FPS;

int main(int argc, char* args[])
{
	IImageLoader* imageLoader = new SDL_ImageImageLoader{};
	Window window{ SCREEN_WIDTH ,SCREEN_HEIGHT, imageLoader};

	std::vector<std::unique_ptr<GameObject>> gameObjects{};
	std::vector<std::unique_ptr<GameObject>> gameObjectsToCreate{};
	std::vector<GameObject*> gameObjectsToDelete{};
	auto player = std::make_unique<Player>("Images/armongus.png",&window, 2, &gameObjectsToCreate, &gameObjects, &gameObjectsToDelete);
	gameObjects.push_back(std::make_unique<Enemy>("Images/armongus.png", &window, player.get(), 1));
	gameObjects.push_back(std::move(player));
	
	
	//Start up SDL and create window
	if (!window.WasSuccessfull())
	{
		printf("Failed to initialize!\n");
		return -1;
	}

	
	//Hack to get window to stay up
	bool quit = false;

	SDL_Event e;

	while (quit == false) {
		const unsigned int frameStartMs = SDL_GetTicks();
		
		
		while (SDL_PollEvent(&e)) {
			switch (e.type)
			{	
			case SDL_QUIT: {
				quit = true;
				
			}break;
			default:;
			}
			for (const auto& gameObject : gameObjects) {
				gameObject->HandleEvent(e);
			}
			for (auto& gameObject : gameObjectsToCreate) {
				gameObjects.push_back(std::move(gameObject));
			}
			for (const auto& gameObject : gameObjectsToDelete) {
				gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), *gameObject),gameObjects.end());
			}
			gameObjectsToDelete.clear();
			gameObjectsToCreate.clear();
		}
		
		for (const auto& gameObject : gameObjects) {
			gameObject->Update();
		}
		window.clear();

		for (const auto& gameObject : gameObjects) {
			gameObject->Render(&window);
		}
		window.present();

		const unsigned int frameTimeMs = SDL_GetTicks() - frameStartMs;
		if (frameTimeMs < MS_PER_FRAME) {
			SDL_Delay(MS_PER_FRAME - frameTimeMs);
		}

	}

	return 0;
}

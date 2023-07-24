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

struct Clock
{
    uint32_t last_tick_time = 0;
    uint32_t delta = 0;

    void tick()
    {
        uint32_t tick_time = SDL_GetTicks();
        delta = tick_time - last_tick_time;
        last_tick_time = tick_time;
    }
};

int main(int argc, char* args[])
{
    IImageLoader* imageLoader = new SDL_ImageImageLoader{};
    Window window{SCREEN_WIDTH, SCREEN_HEIGHT, imageLoader};

    std::vector<std::unique_ptr<GameObject>> gameObjects{};
    std::vector<std::unique_ptr<GameObject>> gameObjectsToCreate{};
    std::vector<GameObject*> gameObjectsToDelete{};
    auto player = std::make_unique<Player>("Images/armongus.png", &window, 2, &gameObjectsToCreate, &gameObjects,
                                           &gameObjectsToDelete);
    Player* playerRef = player.get();
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

    uint32_t startDeltaTime = 0;

    while (quit == false)
    {
        const unsigned int frameStartMs = SDL_GetTicks();

        Clock clock;
        clock.tick();
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                {
                    quit = true;
                }
                break;
            default: ;
            }
            for (const auto& gameObject : gameObjects)
            {
                gameObject->HandleEvent(e);
            }
        }

        for (auto& gameObject : gameObjectsToCreate)
        {
            gameObjects.push_back(std::move(gameObject));
        }

        for (const auto& gameObject : gameObjectsToDelete)
        {
            gameObjects.erase(
                std::remove_if(
                    gameObjects.begin(),
                    gameObjects.end(),
                    [&](std::unique_ptr<GameObject> const& p)
                    {
                        return std::find(
                            gameObjectsToDelete.cbegin(),
                            gameObjectsToDelete.cend(),
                            p.get()
                        ) != gameObjectsToDelete.end();
                    }),
                gameObjects.end()
            );

            gameObjectsToDelete.clear();
        }
        gameObjectsToDelete.clear();
        gameObjectsToCreate.clear();

        for (const auto& gameObject : gameObjects)
        {
            gameObject->Update(clock.delta * 0.001);
        }
        window.clear();

        for (const auto& gameObject : gameObjects)
        {
            gameObject->Render(&window);
        }
        window.present();

        const unsigned int frameTimeMs = SDL_GetTicks() - frameStartMs;
        if (frameTimeMs < MS_PER_FRAME)
        {
            SDL_Delay(MS_PER_FRAME - frameTimeMs);
        }
        if(clock.delta * 0.001 - startDeltaTime >= 1)
        {
            gameObjectsToCreate.push_back(std::make_unique<Enemy>("Images/armongus.png", &window, playerRef, 1));
            startDeltaTime = clock.delta * 0.001;
        }
    }

    return 0;
}

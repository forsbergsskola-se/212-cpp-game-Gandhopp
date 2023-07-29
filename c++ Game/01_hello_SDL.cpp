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
#include "Font.h"
#include "GameObject.h"
#include "TextRender.h"

//Screen dimension constants

constexpr unsigned int FPS = 60;
constexpr unsigned int MS_PER_FRAME = 1000 / FPS;


struct Clock
{
    uint32_t last_tick_time = 0;
    uint32_t delta = 0;

    void tick()
    {
        const uint32_t tick_time = SDL_GetTicks();
        delta = tick_time - last_tick_time;
        last_tick_time = tick_time;
    }
};

int main(int argc, char* args[])
{
    IImageLoader* imageLoader = new SDL_ImageImageLoader{};
    Window window{SCREEN_WIDTH, SCREEN_HEIGHT, imageLoader};

    SDL_Renderer* gRenderer = nullptr;

    TTF_Font* gFont = nullptr;

    TextRenderer gTextTexture;

    std::vector<std::shared_ptr<GameObject>> gameObjects{};
    std::vector<std::shared_ptr<GameObject>> gameObjectsToCreate{};
    std::vector<GameObject*> gameObjectsToDelete{};
    auto player = std::make_shared<Player>("Images/amongus.png", &window, 2, &gameObjectsToCreate, &gameObjects,
                                           &gameObjectsToDelete);
    auto playerPtr = player.get();
    std::weak_ptr<Player> playerWeakPtr = player;
    gameObjects.push_back(std::move(player));

    //Start up SDL and create window
    if (!window.WasSuccessfull())
    {
        printf("Failed to initialize!\n");
        return -1;
    }

    if(TTF_Init() == -1)
    {
        printf("Failed to initialize!\n");
        return -1;
    }


    //Hack to get window to stay up
    bool quit = false;

    bool playerIsDead = false;

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
            if (playerIsDead && e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_f)
                {
                    for (const auto& gameObject : gameObjects)
                    {
                        gameObjectsToDelete.push_back(gameObject.get());
                    }

                    auto playerRespawn = std::make_shared<Player>("Images/amongus.png", &window, 2,
                                                                  &gameObjectsToCreate,
                                                                  &gameObjects,
                                                                  &gameObjectsToDelete);
                    playerPtr = playerRespawn.get();
                    playerWeakPtr = playerRespawn;
                    gameObjects.push_back(std::move(playerRespawn));
                    playerIsDead = false;
                    score = 0;
                }
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
                    [&](std::shared_ptr<GameObject> const& p)
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


        const unsigned int frameTimeMs = SDL_GetTicks() - frameStartMs;
        if (frameTimeMs < MS_PER_FRAME)
        {
            SDL_Delay(MS_PER_FRAME - frameTimeMs);
        }
        if (clock.delta * 0.001 - startDeltaTime >= 1 && !playerIsDead)
        {
            gameObjectsToCreate.push_back(
                std::make_shared<Enemy>("Images/imposter.png", &window, playerPtr, 1, &gameObjectsToDelete));
            startDeltaTime = clock.delta * 0.001;
        }
        if (playerWeakPtr.expired())
        {
            //player died
            playerIsDead = true;
            Font font{"Fonts/standard_font.ttf", 28};
            auto text = font.createText("text and stuff", window.renderer);
            
            gTextTexture.gFont = TTF_OpenFont("Fonts/standard_font.ttf",28);
            gTextTexture.loadFromRenderedText("Press F to restart", SDL_Color{255, 0, 0});
            gTextTexture.rect.x = (SCREEN_WIDTH - gTextTexture.rect.w )/ 2;
            gTextTexture.rect.y = (SCREEN_HEIGHT - gTextTexture.rect.h) /2;
            window.Render(gTextTexture);

        }
        Font font{"Fonts/standard_font.ttf", 28};
        auto text = font.createText("text and stuff", window.renderer);
            
        gTextTexture.gFont = TTF_OpenFont("Fonts/score_font.ttf",28);
        std::string scoreString = "Score " + std::to_string(score);
        gTextTexture.loadFromRenderedText(scoreString, SDL_Color{255, 0, 0});
        gTextTexture.rect.x = SCREEN_WIDTH - gTextTexture.rect.w;
        gTextTexture.rect.y = 0;
        window.Render(gTextTexture);
        window.present();

    }

    return 0;
}

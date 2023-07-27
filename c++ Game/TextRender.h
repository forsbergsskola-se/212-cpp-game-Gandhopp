#pragma once
#include <SDL_surface.h>
#include <string>
#include <SDL_ttf.h>
class TextRenderer
{
    SDL_Surface* textSurface = NULL;
public:
    TTF_Font* gFont = NULL;
    SDL_Rect rect{ 0, 0, 640, 480 };
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
    SDL_Surface* getResource()
    {
        return textSurface;
    }
};
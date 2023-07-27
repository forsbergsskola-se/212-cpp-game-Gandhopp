#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>

extern class Image;

class Font
{
    //The image we will load and show on the screen
    TTF_Font* font{};
    bool success;
public:
public:
    Font(const char* path, const int size);
    ~Font();
    SDL_Rect rect { 0, 0, 640, 480 };
    bool wasSuccessful() { return success; }
    TTF_Font* getResource() { return font; }
    Font& operator =(Font& other) = delete;
    Font& operator =(Font&& other) = delete;
    std::unique_ptr<Image> createText(const char* text, SDL_Renderer* renderer);
};
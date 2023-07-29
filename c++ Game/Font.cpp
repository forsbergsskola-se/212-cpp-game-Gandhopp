#include "Font.h"
#include "Window.h"
#include <cstdio>
#include <SDL.h>
#include <SDL_ttf.h>
#include "TextRender.h"
#include "Image.h"
Font::Font(const char* path, const int size) : success{}
{
    font = TTF_OpenFont( "Fonts/standard_font.ttf", 28 );
    if( font == nullptr )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        success = true;
    }
}

Font::~Font()
{
    TTF_CloseFont(font);
    font = nullptr;
}

std::unique_ptr<Image> Font::createText(const char* text, SDL_Renderer* renderer)
{
    const SDL_Color textColor = {255, 0, 0};
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor );
    if( textSurface == nullptr )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n",TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        return std::make_unique<Image>(textSurface);
    }
    return nullptr;
}
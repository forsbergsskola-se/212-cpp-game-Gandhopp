#include "Font.h"
#include "Window.h"
#include <cstdio>
#include <SDL.h>
#include <SDL_ttf.h>
#include "TextRender.h"
#include "Image.h"

Font::Font(const char* path, const int size) : success{}
{
    font = TTF_OpenFont( "16_true_type_fonts/lazy.ttf", 28 );
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

std::unique_ptr<Image> createText(const char* text, SDL_Renderer* renderer, TTF_Font* font)
{
    SDL_Color textColor = {0, 0, 0};
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor );
    if( textSurface == nullptr )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    // else
    // {
    //     //Create texture from surface pixels
    //     auto mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
    //     if( mTexture == nullptr )
    //     {
    //         printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
    //     }
    //     else
    //     {
    //         //Get image dimensions
    //         auto width = textSurface->w;
    //         auto height = textSurface->h;
    //        // auto image = std::make_unique<Image>(mTexture);
    //     }
    // }
    return nullptr;
}
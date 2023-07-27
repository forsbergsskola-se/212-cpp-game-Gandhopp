#include "TextRender.h"

#include <SDL_surface.h>

bool TextRenderer::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    SDL_FreeSurface(textSurface);

    //Render text surface
    textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if (textSurface == NULL)
    {
        return false;
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    rect.w = textSurface->w;
    rect.h = textSurface->h;

    //Return success
    return true;
}

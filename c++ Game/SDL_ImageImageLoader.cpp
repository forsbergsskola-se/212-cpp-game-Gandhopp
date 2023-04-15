#include "SDL_ImageImageLoader.h"
#include <SDL_image.h>
#include "Image.h"
std::unique_ptr<Image> SDL_ImageImageLoader::LoadImage(const char* path, const SDL_PixelFormat* pixelFormat) {
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, pixelFormat, 0);
        if (optimizedSurface == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return std::make_unique<Image>(optimizedSurface);

}
SDL_ImageImageLoader::SDL_ImageImageLoader() {
    //Initialize PNG loading 
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }
}
#include "SDLImageLoader.h"
#include "Image.h"
std::unique_ptr<Image> SDLImageLoader::LoadImage(const char* path, const SDL_PixelFormat* pixelFormat)
{

	//Load splash ima
	auto tmpSurface = SDL_LoadBMP(path);
	if (!tmpSurface)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
		return std::make_unique<Image>(nullptr);;
	}
	auto imageSurface = SDL_ConvertSurface(tmpSurface, pixelFormat, 0);
	SDL_FreeSurface(tmpSurface);
	if (!imageSurface)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
		return std::make_unique<Image>(nullptr);;
	}

    return std::make_unique<Image>(imageSurface);
}

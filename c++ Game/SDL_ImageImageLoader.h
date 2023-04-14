#pragma once
#include "IImageLoader.h"
class SDL_ImageImageLoader : public IImageLoader
{
	std::unique_ptr<Image> LoadImage(const char* path, const SDL_PixelFormat* pixelFormat) override;
public:
	SDL_ImageImageLoader();
};


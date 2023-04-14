#pragma once
#include "IImageLoader.h"
class SDLImageLoader : public IImageLoader
{
public:
	std::unique_ptr<Image> LoadImage(const char* path, const SDL_PixelFormat* pixelFormat) override;

};


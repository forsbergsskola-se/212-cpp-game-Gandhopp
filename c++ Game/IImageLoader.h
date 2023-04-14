#pragma once

#include <memory>

extern class Image;
extern struct SDL_PixelFormat;

class IImageLoader
{
public:
	virtual std::unique_ptr<Image> LoadImage(const char* path, const SDL_PixelFormat* pixelFormat) = 0;
};


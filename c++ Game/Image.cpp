#include "Image.h"
#include <SDL.h>
#include <cstdio>
#include <SDL_image.h>
Image::Image(SDL_Surface* surface) : success{surface != nullptr}, x{},y{},w{20},h{20},imageSurface{surface}
{

	
	success = true;

}
Image::~Image() {
	//Deallocate surface
	SDL_FreeSurface(imageSurface);
	imageSurface = NULL;
}
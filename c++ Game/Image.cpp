#include "Image.h"

#include <cstdio>
#include <SDL.h>
Image::Image(SDL_Surface* surface) : success{surface != nullptr}, x{},y{},w{20},h{20},imageSurface{surface}
{
	printf("image");
	
	success = true;

}
Image::~Image() {
	//Deallocate surface
	printf("~image");
	SDL_FreeSurface(imageSurface);
	imageSurface = NULL;
}
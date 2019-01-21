#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Artefact {
	public:
		Artefact(int x, int y, char * img);
		SDL_Surface* get_surface();
		SDL_Rect* get_position();
	private:
		SDL_Surface *s;
		SDL_Rect position;
};

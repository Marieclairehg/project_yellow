#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Artefact.hh"

Artefact::Artefact(int x, int y, char *img) : s(IMG_Load(img)){
	position.x = x;
	position.y = y;
	if (!s) {
		std::cout << SDL_GetError() << std::endl;
	}
}

SDL_Surface* Artefact::get_surface() {
	return s;
}

void Artefact::set_surface(SDL_Surface *a) {
	s = a;
}

SDL_Rect* Artefact::get_position() {
	return &position;
}

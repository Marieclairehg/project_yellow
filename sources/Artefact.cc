#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Artefact.hh"

Artefact::Artefact(int x, int y, char *img) : s(IMG_Load(img)){
	position.x = x;
	position.y = y;
}

SDL_Surface* Artefact::get_surface() {
	return s;
}

SDL_Rect* Artefact::get_position() {
	return &position;
}

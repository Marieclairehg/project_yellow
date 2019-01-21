#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Artefact.hh"

class Malus : public Artefact {
	public:
		Malus(int x, int y, char * img);
	private:
};

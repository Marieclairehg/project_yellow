#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Voiture.hh"

class Artefact {
	public:
		Artefact(int x, int y, char * img);
		virtual ~Artefact() {};
		SDL_Surface* get_surface();
		void set_surface(SDL_Surface *a);
		SDL_Rect* get_position();
		virtual void interact(Voiture &v) = 0;
	private:
	protected:
		SDL_Surface *s;
		SDL_Rect position;
};

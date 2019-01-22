#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Malus.hh"
#include "Voiture.hh"

class Cailloux : public Malus {
	public:
		Cailloux(int x, int y);
		virtual ~Cailloux() {};
		void interact(Voiture &v);
	private:
};

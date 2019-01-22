#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Malus.hh"
#include "Voiture.hh"

class Trou : public Malus {
	public:
		Trou(int x, int y);
		virtual ~Trou() {};
		void interact(Voiture &v);
	private:
};

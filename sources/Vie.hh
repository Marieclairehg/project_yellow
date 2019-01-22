#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Bonus.hh"
#include "Voiture.hh"

class Vie : public Bonus {
	public:
		Vie(int x, int y);
		virtual ~Vie() {};
		bool isEnabled();
		void disable();
		void interact(Voiture &v);
	private:
		bool enabled;
};

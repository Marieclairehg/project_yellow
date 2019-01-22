#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Bonus.hh"

class Piece : public Bonus {
	public:
		Piece(int x, int y);
		virtual ~Piece() {};
		bool isEnabled();
		void disable();
		void interact(Voiture &v);
	protected:
		bool enabled;
};

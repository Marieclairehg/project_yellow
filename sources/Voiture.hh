#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Voiture {
	public:
		Voiture();
		SDL_Surface* get_surface();
		SDL_Rect* get_position();
		int get_vies();
		int get_pieces();
		void set_vies(int v);
		void set_pieces(int p);
	private:
		int vie;
		int nbPieces;
		SDL_Surface *v;
		SDL_Rect posVoiture, posVies;
};

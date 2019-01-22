#pragma once
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
		void stop();
		bool isStopped();
		void enableSaut();
		void disableSaut();
		void gestionSaut();
		void gestionPiste(SDL_Surface *piste);
	private:
		int vie;
		int nbPieces;
		int saut;
		SDL_Surface *v;
		SDL_Rect posVoiture, posVies;
		bool sautEnable;
		bool stopped;
		int tableSaut[63];
};

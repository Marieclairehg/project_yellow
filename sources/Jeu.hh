#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include "Artefact.hh"
#include "Voiture.hh"
#include "Vie.hh"
#include "Cailloux.hh"
#include "Trou.hh"
#include "Piece.hh"

class Jeu {
public:
	Jeu();
	~Jeu();

private:
	void initSDL();
	void initPositions();
	void loadImages();
	void boucleEvt();
	void affichage();
	void affichageVies();
	void affichagePieces(int nb, int indice);
	Voiture voiture;
	SDL_Rect posBG, posVies[3], posPieces[5];
	bool continuer;
	int nbVies;
	SDL_Surface *screenSurface;
	SDL_Surface *background;
	SDL_Surface *piste;
	SDL_Surface *endOfGame;
	SDL_Surface *vies[3];
	SDL_Surface *pieces[3];
	SDL_Event event;
	SDL_Window* window;
	std::list<Artefact*> artefacts;
};

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Voiture.hh"
#include "Vie.hh"
#include "Cailloux.hh"
#include "Trou.hh"

int main(int argc, char **argv) {
	bool continuer = 1;
	bool stop = 0;
	int nbVies = -1;
	SDL_Event event;
	// Notre fenêtre
	SDL_Window* window(0);
	int tableSaut[63] = {3,3,3,3,3,3,3,3,3,3,3,3,
											 2,2,2,2,2,2,2,2,2,
										   1,1,1,1,1,1,1,1,1,
										   0,0,0,
										   -1,-1,-1,-1,-1,-1,-1,-1,-1,
										   -2,-2,-2,-2,-2,-2,-2,-2,-2,
										 	 -3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3};

	SDL_Surface* screenSurface = NULL;
	SDL_Surface *background = NULL;
	SDL_Surface *piste = NULL;
	SDL_Surface *endOfGame = NULL;
	SDL_Surface *vies[3];
	SDL_Surface *pieces[4];
	pieces[0] = IMG_Load("images/piece.png");
	pieces[1] = IMG_Load("images/1.png");
	pieces[2] = NULL;
	pieces[3] = NULL;
	vies[0] = IMG_Load("images/coeur.png");
	vies[1] = NULL;
	vies[2] = NULL;
	Vie v1(500, 120);
	Cailloux c1(800, 165);
	Trou t1(500, 219);


	SDL_Rect posBG, posVies[3], posPieces[5];
	posBG.x = 0;
	posBG.y = 0;
	posVies[0].x = 0;
	posVies[0].y = 0;
	posVies[1].x = 64;
	posVies[1].y = 0;
	posVies[2].x = 128;
	posVies[2].y = 0;
	posPieces[0].x = 192;
	posPieces[0].y = 0;
	posPieces[1].x = 256;
	posPieces[1].y = 10;
	posPieces[2].x = 192;
	posPieces[2].y = 10;
	posPieces[3].x = 320;
	posPieces[3].y = 10;
	posPieces[4].x = 384;
	posPieces[4].y = 10;
	Voiture voiture;
	background = IMG_Load("images/ciel.png");
	piste = IMG_Load("images/piste_small.png");

	// Initialisation de la SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}

	// Création de la fenêtre
	window = SDL_CreateWindow("Jeu Yellow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1227, 300, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}
	//Get window surface
	screenSurface = SDL_GetWindowSurface( window );
	int saut = 0;
	bool sautEnable = 0;
	while (continuer) {
		SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						continuer = 0;
						break;
					case SDLK_UP:
				                if (!stop)
													voiture.get_position()->y-=2;
						break;
					case SDLK_DOWN:
				                if (!stop)
				                	voiture.get_position()->y+=2;
						break;
					case SDLK_RIGHT:
				                if (!stop)
				                	voiture.get_position()->x+=4;
						break;
					case SDLK_LEFT:
				                if (!stop)
				                	voiture.get_position()->x-=2;
						break;
					case SDLK_KP_PLUS:
				                if (!stop)
				                	voiture.set_vies(voiture.get_vies() + 1);
						break;
					case SDLK_KP_MINUS:
				                if (!stop)
				                	voiture.set_vies(voiture.get_vies() - 1);
						break;
					case SDLK_SPACE:
				                if (!stop)
													sautEnable = 1;
						break;
				}
				break;
		}

		// gestion du saut
		if (sautEnable) {
			voiture.get_position()->y-=tableSaut[saut];
			//voiture.get_position()->x+=2;
			saut++;
			if (saut == 63) {
				sautEnable = 0;
				saut = 0;
			}
		}

		// collision Cailloux --> retour au début et perte d'une vie
		if (((voiture.get_position()->x + voiture.get_position()->w) > c1.get_position()->x) &&
				(voiture.get_position()->x < (c1.get_position()->x + c1.get_position()->w)) &&
			  ((voiture.get_position()->y + voiture.get_position()->h) > c1.get_position()->y) &&
				(voiture.get_position()->y < (c1.get_position()->y + c1.get_position()->h))) {
			voiture.set_vies(voiture.get_vies() - 1);
			voiture.get_position()->x = 0;
		}



		nbVies = voiture.get_vies();
		if (nbVies > 0) {
			SDL_BlitSurface(background, NULL, screenSurface, &posBG);
			SDL_BlitSurface(piste, NULL, screenSurface, &posBG);
			SDL_BlitSurface(v1.get_surface(), NULL, screenSurface, v1.get_position());
			SDL_BlitSurface(c1.get_surface(), NULL, screenSurface, c1.get_position());
			SDL_BlitSurface(t1.get_surface(), NULL, screenSurface, t1.get_position());
			if (nbVies == 0) {
				vies[0] = NULL;
				vies[1] = NULL;
				vies[2] = NULL;
				endOfGame = IMG_Load("images/gameOver.png");
			} else if (nbVies == 1) {
				vies[0] = IMG_Load("images/coeur.png");
				vies[1] = NULL;
				vies[2] = NULL;
				endOfGame = NULL;
			} else if (nbVies == 2) {
				vies[0] = IMG_Load("images/coeur.png");
				vies[1] = IMG_Load("images/coeur.png");
				vies[2] = NULL;
				endOfGame = NULL;
			} else if (nbVies == 3) {
				vies[0] = IMG_Load("images/coeur.png");
				vies[1] = IMG_Load("images/coeur.png");
				vies[2] = IMG_Load("images/coeur.png");
				endOfGame = NULL;
			}

			// gagné
			if (voiture.get_position()->x + voiture.get_position()->w == 1227) {
				stop = 1;
				endOfGame = IMG_Load("images/winner.png");
			}
			SDL_BlitSurface(vies[0], NULL, screenSurface, &posVies[0]);
			SDL_BlitSurface(vies[1], NULL, screenSurface, &posVies[1]);
			SDL_BlitSurface(vies[2], NULL, screenSurface, &posVies[2]);
			SDL_BlitSurface(pieces[0], NULL, screenSurface, &posPieces[0]);
			SDL_BlitSurface(pieces[1], NULL, screenSurface, &posPieces[1]);
			SDL_BlitSurface(pieces[2], NULL, screenSurface, &posPieces[2]);
			SDL_BlitSurface(pieces[3], NULL, screenSurface, &posPieces[3]);
			SDL_BlitSurface(endOfGame, NULL, screenSurface, &posBG);
			SDL_BlitSurface(voiture.get_surface(), NULL, screenSurface, voiture.get_position());
		} else {
			vies[0] = NULL;
			vies[1] = NULL;
			vies[2] = NULL;
			endOfGame = IMG_Load("images/gameOver.png");
			SDL_BlitSurface(endOfGame, NULL, screenSurface, &posBG);
		}

		SDL_UpdateWindowSurface( window );
	}

	// On quitte la SDL
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

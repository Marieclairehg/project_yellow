#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Jeu.hh"

Jeu::Jeu() : continuer(1), stop(0), nbVies(-1), screenSurface(NULL),
						 background(NULL), piste(NULL), endOfGame(NULL) {
	initSDL();
	initPositions();
	loadImages();

	v1 = new Vie(500, 120);
	c1 = new Cailloux(800, 165);
	t1 = new Trou(500, 219);
	p1 = new Piece(200, 200);

	boucleEvt();
	quitSDL();
}

Jeu::~Jeu() {
	delete v1;
	delete p1;
	delete c1;
	delete t1;
}

void Jeu::initSDL() {
	// Initialisation de la SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(-1);
	}
	// Création de la fenêtre
	window = SDL_CreateWindow("Jeu Yellow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1227, 300, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(-1);
	}
	//Get window surface
	screenSurface = SDL_GetWindowSurface( window );
}

void Jeu::initPositions() {
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
}

void Jeu::loadImages() {
	background = IMG_Load("images/ciel.png");
	piste = IMG_Load("images/piste_small.png");
	pieces[0] = IMG_Load("images/piece.png");
	pieces[1] = NULL;
	pieces[2] = NULL;
	pieces[3] = NULL;
	vies[0] = IMG_Load("images/coeur.png");
	vies[1] = NULL;
	vies[2] = NULL;
}

void Jeu::quitSDL() {
	// On quitte la SDL
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Jeu::affichage() {
	nbVies = voiture.get_vies();
	if (nbVies > 0) {
		SDL_BlitSurface(background, NULL, screenSurface, &posBG);
		SDL_BlitSurface(piste, NULL, screenSurface, &posBG);
		SDL_BlitSurface(v1->get_surface(), NULL, screenSurface, v1->get_position());
		SDL_BlitSurface(c1->get_surface(), NULL, screenSurface, c1->get_position());
		SDL_BlitSurface(t1->get_surface(), NULL, screenSurface, t1->get_position());
		SDL_BlitSurface(p1->get_surface(), NULL, screenSurface, p1->get_position());
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

		if (voiture.get_pieces() == 1) {
			pieces[1] = IMG_Load("images/1.png");
		} else if (voiture.get_pieces() == 2) {
			pieces[1] = IMG_Load("images/2.png");
		}

		// gagné
		if ((voiture.get_position()->x + voiture.get_position()->w) >= 1227) {
			voiture.stop();
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

void Jeu::boucleEvt() {
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
				                if (!voiture.isStopped())
													voiture.get_position()->y-=2;
						break;
					case SDLK_DOWN:
				                if (!voiture.isStopped())
				                	voiture.get_position()->y+=2;
						break;
					case SDLK_RIGHT:
				                if (!voiture.isStopped())
				                	voiture.get_position()->x+=4;
						break;
					case SDLK_LEFT:
				                if (!voiture.isStopped())
				                	voiture.get_position()->x-=2;
						break;
					case SDLK_KP_PLUS:
				                if (!voiture.isStopped())
				                	voiture.set_vies(voiture.get_vies() + 1);
						break;
					case SDLK_KP_MINUS:
				                if (!voiture.isStopped())
				                	voiture.set_vies(voiture.get_vies() - 1);
						break;
					case SDLK_SPACE:
				                if (!voiture.isStopped())
													voiture.enableSaut();
						break;
				}
				break;
		}
		v1->interact(voiture);
		p1->interact(voiture);
		c1->interact(voiture);
		t1->interact(voiture);
		voiture.gestionSaut();
		voiture.gestionPiste(piste);
		affichage();
	}
}

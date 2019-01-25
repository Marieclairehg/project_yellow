#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Jeu.hh"

Jeu::Jeu() : continuer(1), nbVies(-1), screenSurface(NULL),
						 background(NULL), piste(NULL), endOfGame(NULL) {
	initSDL();
	initPositions();
	loadImages();

	artefacts.push_back(new Piece(120, 240));
	artefacts.push_back(new Piece(200, 220));
	artefacts.push_back(new Vie(500, 120));
	artefacts.push_back(new Piece(600, 120));
	artefacts.push_back(new Cailloux(800, 165));
	artefacts.push_back(new Trou(550, 219));
	artefacts.push_back(new Piece(400, 170));
	artefacts.push_back(new Piece(800, 100));
	artefacts.push_back(new Piece(900, 120));
	artefacts.push_back(new Piece(1100, 60));

	boucleEvt();
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Jeu::~Jeu() {
	for (std::list<Artefact*>::iterator it = artefacts.begin(); it != artefacts.end(); it++) {
		delete *it;
	}
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
	for (int i = 0 ; i < 3 ; i++) {
		posVies[i].x = i*64;
		posVies[i].y = 0;
	}
	posPieces[0].x = 192;
	posPieces[0].y = 0;
	for (int i = 1 ; i < 3 ; i++) {
		posPieces[i].x = 230 + i*40;
		posPieces[i].y = 10;
	}
}

void Jeu::loadImages() {
	background = IMG_Load("images/ciel.png");
	piste = IMG_Load("images/piste_small.png");
	pieces[0] = IMG_Load("images/piece.png");
	pieces[1] = NULL;
	pieces[2] = NULL;
	vies[0] = IMG_Load("images/coeur.png");
	vies[1] = NULL;
	vies[2] = NULL;
}

void Jeu::affichageVies() {
	switch (nbVies) {
		case 1:
			vies[0] = IMG_Load("images/coeur.png");
			vies[1] = NULL;
			vies[2] = NULL;
			endOfGame = NULL;
			break;
		case 2:
			vies[0] = IMG_Load("images/coeur.png");
			vies[1] = IMG_Load("images/coeur.png");
			vies[2] = NULL;
			endOfGame = NULL;
			break;
		case 3:
			vies[0] = IMG_Load("images/coeur.png");
			vies[1] = IMG_Load("images/coeur.png");
			vies[2] = IMG_Load("images/coeur.png");
			endOfGame = NULL;
			break;
	}
}

void Jeu::affichagePieces(int nb, int indice) {
	switch (nb) {
		case 0:
			pieces[indice] = IMG_Load("images/0.png");
			break;
		case 1:
			pieces[indice] = IMG_Load("images/1.png");
			break;
		case 2:
			pieces[indice] = IMG_Load("images/2.png");
			break;
		case 3:
			pieces[indice] = IMG_Load("images/3.png");
			break;
		case 4:
			pieces[indice] = IMG_Load("images/4.png");
			break;
		case 5:
			pieces[indice] = IMG_Load("images/5.png");
			break;
		case 6:
			pieces[indice] = IMG_Load("images/6.png");
			break;
		case 7:
			pieces[indice] = IMG_Load("images/7.png");
			break;
		case 8:
			pieces[indice] = IMG_Load("images/8.png");
			break;
		case 9:
			pieces[indice] = IMG_Load("images/9.png");
			break;
	}
}

void Jeu::affichage() {
	nbVies = voiture.get_vies();
	if (nbVies > 0) {
		SDL_BlitSurface(background, NULL, screenSurface, &posBG);
		SDL_BlitSurface(piste, NULL, screenSurface, &posBG);
		// affichage des artefacts
		for (std::list<Artefact*>::iterator it = artefacts.begin(); it != artefacts.end(); it++) {
			SDL_BlitSurface((*it)->get_surface(), NULL, screenSurface, (*it)->get_position());
		}

		affichageVies();
		affichagePieces(voiture.get_pieces() % 10, 2); // unités
		affichagePieces(voiture.get_pieces() / 10, 1); // dizaines

		// gagné
		if ((voiture.get_position()->x + voiture.get_position()->w) >= 1227) {
			voiture.stop();
			endOfGame = IMG_Load("images/winner.png");
			SDL_BlitSurface(endOfGame, NULL, screenSurface, &posBG);
		}
		// affichage des vies et des pieces
		SDL_BlitSurface(vies[0], NULL, screenSurface, &posVies[0]);
		SDL_BlitSurface(vies[1], NULL, screenSurface, &posVies[1]);
		SDL_BlitSurface(vies[2], NULL, screenSurface, &posVies[2]);
		SDL_BlitSurface(pieces[0], NULL, screenSurface, &posPieces[0]);
		SDL_BlitSurface(pieces[1], NULL, screenSurface, &posPieces[1]);
		SDL_BlitSurface(pieces[2], NULL, screenSurface, &posPieces[2]);
		// affichage de la voiture
		SDL_BlitSurface(voiture.get_surface(), NULL, screenSurface, voiture.get_position());
	} else { // perdu
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
					case SDLK_RIGHT:
				    if (!voiture.isStopped())
				     	voiture.get_position()->x+=4;
						break;
					case SDLK_LEFT:
				    if (!voiture.isStopped())
				     	voiture.get_position()->x-=2;
						break;
					case SDLK_SPACE:
				    if (!voiture.isStopped())
							voiture.enableSaut();
						break;
				}
				break;
		}

		// interaction de la voiture avec tous les artefacts
		for (std::list<Artefact*>::iterator it = artefacts.begin(); it != artefacts.end(); it++) {
			(*it)->interact(voiture);
		}
		voiture.gestionSaut();
		voiture.gestionPiste(piste);
		affichage();
	}
}

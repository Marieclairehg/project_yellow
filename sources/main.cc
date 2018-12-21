#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

int main(int argc, char **argv) {   
	bool continuer = 1;
	SDL_Event event;
	// Notre fenêtre
	SDL_Window* window(0);

	SDL_Surface* screenSurface = NULL;
	SDL_Surface *voiture = NULL, *background = NULL;

	SDL_Rect posVoiture, posBG;
	posVoiture.x = 0;
	posVoiture.y = 80;
	posBG.x = 0;
	posBG.y = 0;
	voiture = IMG_Load("../voiture.png");
	background = IMG_Load("../carte_small.png");

	// Initialisation de la SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}

	// Création de la fenêtre
	window = SDL_CreateWindow("Jeu Yellow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 409, 100, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}
	//Get window surface 
	screenSurface = SDL_GetWindowSurface( window ); 
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
					case SDLK_UP: // Flèche haut
				                posVoiture.y--;	
						break;
					case SDLK_DOWN: // Flèche bas
						posVoiture.y++;
						break;
					case SDLK_RIGHT: // Flèche droite
						posVoiture.x++;
						break;
					case SDLK_LEFT: // Flèche gauche
						posVoiture.x--;
					break;
				}
				break;
		}
		SDL_BlitSurface(background, NULL, screenSurface, &posBG);
		SDL_BlitSurface(voiture, NULL, screenSurface, &posVoiture);
		SDL_UpdateWindowSurface( window ); 
	}

	// On quitte la SDL
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}


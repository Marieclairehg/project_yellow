#include "Voiture.hh"

Voiture::Voiture(): vie(1), nbPieces(0), saut(0), v(IMG_Load("images/voiture.png")), stopped(0) {
	posVoiture.x = 0;
	posVoiture.y = 255;
	int t[63] = {3,3,3,3,3,3,3,3,3,3,3,3,
							 2,2,2,2,2,2,2,2,2,
							 1,1,1,1,1,1,1,1,1,
							 0,0,0,
							 -1,-1,-1,-1,-1,-1,-1,-1,-1,
							 -2,-2,-2,-2,-2,-2,-2,-2,-2,
							 -3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3};
	for (int i = 0 ; i < 63 ; i++) {
		tableSaut[i] = t[i];
	}
}

SDL_Surface* Voiture::get_surface() {
	return v;
}

SDL_Rect* Voiture::get_position() {
	return &posVoiture;
}

int Voiture::get_vies() {
	return vie;
}

int Voiture::get_pieces() {
	return nbPieces;
}

void Voiture::set_vies(int v) {
	vie = v;
	if (vie < 0)
		vie = 0;
	if (vie >  3)
		vie = 3;
}

void Voiture::set_pieces(int p) {
	nbPieces = p;
	if (nbPieces < 0)
		nbPieces = 0;
	if (nbPieces > 999)
		nbPieces = 999;
}

void Voiture::enableSaut() {
	sautEnable = 1;
}

void Voiture::disableSaut() {
	sautEnable = 0;
	saut = 0;
}

void Voiture::stop() {
	stopped = 1;
}

bool Voiture::isStopped() {
	return stopped;
}

void Voiture::gestionSaut() { // vers classe Voiture
	// gestion du saut
	if (sautEnable) {
		posVoiture.y-=tableSaut[saut];
		//voiture.get_position()->x+=2;
		saut++;
		if (saut == 63) {
			sautEnable = 0;
			saut = 0;
		}
	}
}

void Voiture::gestionPiste(SDL_Surface *piste) {
	//gestion piste
	Uint32 *pixels;
	Uint32 px;
	SDL_PixelFormat *fmt = piste->format;
	pixels = ((Uint32*)piste->pixels);
	SDL_LockSurface(piste);
	px = pixels[(posVoiture.y + posVoiture.h - 3) * piste->w + (posVoiture.x + posVoiture.w - 10)];
	Uint8 r, g, b;
	SDL_GetRGB(px, fmt, &r, &g, &b);
	//std::cout << "R : " << (int)r << " G : " << (int)g << " B : " << (int)b << std::endl;
	if (!sautEnable && !stopped) {
		if ((int)r == 47 && (int)g == 107 && (int)b == 47) { // coin bas avant = vert
			v = IMG_Load("images/voiture.png");
		} else if ((int)r == 49 && (int)g == 31 && (int)b == 31){ // coin bas avant = marron
			posVoiture.y-=2;
			v = IMG_Load("images/voiture2.png");
		} else { // coin bas avant = air
			posVoiture.y+=2;
			v = IMG_Load("images/voiture3.png");
		}
	}
	SDL_UnlockSurface(piste);
}

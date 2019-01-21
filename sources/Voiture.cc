#include "Voiture.hh"

Voiture::Voiture(): vie(1), nbPieces(0), v(IMG_Load("images/voiture.png")) {
	posVoiture.x = 0;
	posVoiture.y = 250;
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
	if (nbPieces > 1000000)
		nbPieces = 1000000;
}

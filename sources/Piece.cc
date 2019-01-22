#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Piece.hh"

Piece::Piece(int x, int y) : Bonus(x, y, (char*)"images/piece+1.png"), enabled(1) {
}

bool Piece::isEnabled() {
  return enabled;
}

void Piece::disable() {
  enabled = 0;
}

void Piece::interact(Voiture &v) {
  // gestion bonus piece
	if (enabled) {
		if (((v.get_position()->x + v.get_position()->w) > Artefact::position.x) &&
				(v.get_position()->x < (Artefact::position.x + Artefact::position.w)) &&
				((v.get_position()->y + v.get_position()->h) > Artefact::position.y) &&
				(v.get_position()->y < (Artefact::position.y + Artefact::position.h))) {
			v.set_pieces(v.get_pieces() + 1);
			s = NULL;
      enabled = 0;
		}
	}
}

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Trou.hh"

Trou::Trou(int x, int y) : Malus(x, y, (char*)"images/trou.png") {}

void Trou::interact(Voiture &v) {
  // collision Trou --> retour au début et perte d'une vie
	if (((v.get_position()->x + v.get_position()->w) > Artefact::position.x) &&
			(v.get_position()->x < (Artefact::position.x + Artefact::position.w)) &&
			((v.get_position()->y + v.get_position()->h) > Artefact::position.y) &&
			(v.get_position()->y < (Artefact::position.y + Artefact::position.h))) {
		v.set_vies(v.get_vies() - 1);
		v.get_position()->x = 0;
		v.get_position()->y = 255;
    v.disableSaut();
	}
}

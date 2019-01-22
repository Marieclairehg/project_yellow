#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Vie.hh"

Vie::Vie(int x, int y) : Bonus(x, y, (char*)"images/coeur+1.png"), enabled(1) {}

bool Vie::isEnabled() {
  return enabled;
}

void Vie::disable() {
  enabled = 0;
}

void Vie::interact(Voiture &v) {
  // gestion bonus vie
  if (enabled) {
    if (((v.get_position()->x + v.get_position()->w) > Artefact::position.x) &&
        (v.get_position()->x < (position.x + position.w)) &&
        ((v.get_position()->y + v.get_position()->h) > position.y) &&
        (v.get_position()->y < (position.y + position.h))) {
      //std::cout << "Vie +1" << std::endl;
      v.set_vies(v.get_vies() + 1);
      s = NULL;
      enabled = 0;
    }
  }
}

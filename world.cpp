#include "world.h"
#include "object.h"

void World::update(){
  player->update(*this);
  for(unsigned int i = 0; i < platforms.size(); i++)
    platforms[i]->update(*this);
}

void World::draw(SDL_Renderer* renderer, double interp){
  /* Render platforms first */
  for(unsigned int i = 0; i < platforms.size(); i++)
    platforms[i]->draw(renderer, interp);

  /* Render players last */
  player->draw(renderer, interp);
}

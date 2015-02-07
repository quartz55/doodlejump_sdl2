#include "object.h"
#include "world.h"
#include "inputcomponent.h"
#include "physicscomponent.h"
#include "graphicscomponent.h"

void Object
::update(World& world){
  input_->update(*this, world);
  physics_->update(*this, world);
}

void Object
::draw(SDL_Renderer* renderer, double interp){
  graphics_->update(*this, renderer, interp);
}

void Object
::send(message msg){
  input_->receive(msg);
  physics_->receive(msg);
  physics_->receive(msg);
}

#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include "messages.h"

class World;
class InputComponent;
class PhysicsComponent;
class GraphicsComponent;

class Object{

  InputComponent* input_;
  PhysicsComponent* physics_;
  GraphicsComponent* graphics_;
  
public:
  int x,y,w,h;
  double xspeed,yspeed;

  Object(InputComponent* input,
         PhysicsComponent* physics,
         GraphicsComponent* graphics)
    :input_(input), physics_(physics), graphics_(graphics)
  {}

  void update(World& world);
  void draw(SDL_Renderer* renderer, double interp);
  void send(message msg);
  
};

#endif

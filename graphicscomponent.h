#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <SDL2/SDL.h>
#include <algorithm>
#include "globals.h"
#include "messages.h"

class Object;

class GraphicsComponent{
public:
  virtual ~GraphicsComponent(){}
  virtual void update(Object& obj, SDL_Renderer* renderer, double interp)=0;
  virtual void receive(message msg){}
};


class GeneralGraphicsComponent : public GraphicsComponent{
  int r,g,b,a;
public:
  GeneralGraphicsComponent(int r, int g, int b, int a)
    :r(r),g(g),b(b),a(a)
  {}
  virtual void update(Object& obj, SDL_Renderer* renderer, double interp);
};

#endif

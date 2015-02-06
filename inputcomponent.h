#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include <SDL2/SDL.h>

class Object;
class World;

class InputComponent{
public:
  virtual ~InputComponent(){}
  virtual void update(Object& obj, World& world)=0;
};

class PlayerInputComponent : public InputComponent{
  bool *moveright, *moveleft;
  const double speed;
public:
  PlayerInputComponent(bool *moveright, bool *moveleft)
    :moveright(moveright),moveleft(moveleft),speed(0.7)
  {}
  virtual void update(Object& obj, World& world);
};

class DemoInputComponent : public InputComponent{
public:
  virtual void update(Object& obj, World& world);
};

class PlatformInputComponent : public InputComponent{
public:
  virtual void update(Object& obj, World& world);
};

#endif

#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include <SDL2/SDL.h>
#include "messages.h"

class Object;
class World;

class InputComponent{
public:
  virtual ~InputComponent(){}
  virtual void update(Object& obj, World& world)=0;
  virtual void receive(message msg){};
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
  Object *target, *prev_target;
  const double speed;

  double calc_distance(Object& obj1, Object& obj2);
  Object* get_target(Object& obj, World& world);
public:
  DemoInputComponent()
    :target(NULL),prev_target(NULL),speed(0.7)
  {}
  virtual void update(Object& obj, World& world);
  virtual void receive(message msg);
};

class PlatformInputComponent : public InputComponent{
public:
  virtual void update(Object& obj, World& world);
};

#endif

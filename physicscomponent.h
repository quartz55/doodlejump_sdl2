#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "globals.h"
#include "messages.h"
#include <vector>

class Object;
class World;

class PhysicsComponent{
public:
  virtual ~PhysicsComponent(){}
  virtual void update(Object& obj, World& world)=0;
  virtual void receive(message msg){}
};

class PlayerPhysicsComponent : public PhysicsComponent{
  bool checkCollisions(Object& player, std::vector<Object*> &platforms);

public:
  virtual void update(Object& obj, World& world);
};

class PlatformPhysicsComponent : public PhysicsComponent{
  void checkDistances(Object* platform, std::vector<Object*> &platforms);
public:
  virtual void update(Object& obj, World& world);
};

#endif

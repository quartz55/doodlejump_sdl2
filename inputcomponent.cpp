#include "inputcomponent.h"

#include "object.h"
#include "world.h"

void PlayerInputComponent
::update(Object& obj, World& world){
  if(*moveright) obj.xspeed += speed;
  else if(*moveleft) obj.xspeed -= speed;
}

void DemoInputComponent
::update(Object& obj, World& world){
}

void PlatformInputComponent
::update(Object& obj, World& world){
}

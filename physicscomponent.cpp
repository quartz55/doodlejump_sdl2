#include "physicscomponent.h"
#include "object.h"
#include "world.h"

bool PlayerPhysicsComponent
::checkCollisions(Object& player, std::vector<Object*> &platforms){
  for(unsigned int i = 0; i < platforms.size(); i++){
    if(player.yspeed > 0)
      if(player.x < platforms[i]->x+platforms[i]->w
         && player.x+player.w > platforms[i]->x
         && player.y+5*player.h/6 < platforms[i]->y+platforms[i]->h
         && player.y+player.h > platforms[i]->y){
        player.y = platforms[i]->y-player.h;
        return true;
      }
  }
  return false;
}

void PlayerPhysicsComponent
::update(Object& obj, World& world){
  // Gravity
  obj.yspeed+=0.65;
  obj.yspeed*=0.99;
  
  if(obj.x+obj.xspeed > SCREEN_WIDTH){
    obj.x = 0;
  }
  else if(obj.x+obj.w+obj.xspeed < 0){
    obj.x = SCREEN_WIDTH-obj.w;
  }

  if(checkCollisions(obj, world.get_platforms())){
    obj.yspeed = -22;
    obj.send(PLAYER_JUMP);
  }

  obj.xspeed*=0.93;
  obj.x+=obj.xspeed;

  if(obj.y+obj.yspeed >= SCREEN_HEIGHT/2) {
    obj.y+=obj.yspeed;
    scroll = false;
  }
  else {
    obj.y=SCREEN_HEIGHT/2;
    scroll = true;
  }
}

/** @brief Ensures minimum distance between platforms */
void PlatformPhysicsComponent
::checkDistances(Object* platform, std::vector<Object*> &platforms){
  for(unsigned int i = 1; i < platforms.size(); i++)
    if(platform != platforms[i])
      while(abs(platform->y-platforms[i]->y)<=50){
          platform->y++;
      }
}

void PlatformPhysicsComponent
::update(Object& obj, World& world){
  checkDistances(&obj, world.get_platforms());

  Object* player = world.get_player();
  if(scroll && player->yspeed < 0) obj.yspeed = -player->yspeed;

  if(obj.y+obj.yspeed > SCREEN_HEIGHT){
    obj.y = -obj.h-rand() % 100;
    obj.x = rand()%SCREEN_WIDTH;
  }

  if(obj.x+obj.w+obj.xspeed > SCREEN_WIDTH) obj.x = SCREEN_WIDTH-obj.w;
  else if(obj.x+obj.xspeed < 0) obj.x = 0;
  
  obj.x+=obj.xspeed;
  obj.y+=obj.yspeed;
}

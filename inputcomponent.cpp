#include "inputcomponent.h"

#include "globals.h"
#include "object.h"
#include "world.h"
#include <math.h>
#include <algorithm>
#include <vector>

void PlayerInputComponent
::update(Object& obj, World& world){
  if(*moveright) obj.xspeed += speed;
  else if(*moveleft) obj.xspeed -= speed;
  else if(fabs(obj.xspeed) < 0.1) obj.xspeed = 0;
}

double DemoInputComponent
::calc_distance(Object& obj1, Object& obj2){
  int x_distance;
  if(obj2.x+obj2.w/2 >= SCREEN_WIDTH/2){
    if(obj1.x-obj1.w/2 >= SCREEN_WIDTH/2){
      x_distance = abs(obj2.x-obj1.x);
    }
    else{
      int normal_distance = abs(obj1.x-obj2.x);
      int warp_distance = obj1.x+(SCREEN_WIDTH-obj2.x+obj2.w);
      x_distance = std::min(normal_distance, warp_distance);
    }
  }
  else{
    if(obj1.x-obj1.w/2 <= SCREEN_WIDTH/2){
      x_distance = abs(obj2.x-obj1.x);
    }
    else{
      int normal_distance = abs(obj1.x-obj2.x);
      int warp_distance = (SCREEN_WIDTH-obj1.x)+obj2.x;
      x_distance = std::min(normal_distance, warp_distance);
    }
  }

  return sqrt(pow(x_distance, 2) + pow(abs(obj2.y-obj1.y), 2));
}

Object* DemoInputComponent
::get_target(Object& obj, World& world){
  std::vector<Object*> platforms = world.get_platforms();
  if(platforms.empty()) return NULL;

  Object* temp_target = NULL;
  double target_distance = 99999;
  for(unsigned int i = 0; i < platforms.size(); i++){
    double temp_distance = calc_distance(obj, *platforms[i]);
    if(temp_distance < target_distance
       && platforms[i]->y >= SCREEN_HEIGHT/2-platforms[i]->h
       && platforms[i]->y < obj.y
       && platforms[i] != temp_target){
      temp_target = platforms[i];
      target_distance = temp_distance;
    }
  }
  return temp_target;
}

void DemoInputComponent
::receive(message msg){
  if(msg == PLAYER_JUMP){
    this->prev_target = target;
    this->target = NULL;
  }
}

void DemoInputComponent
::update(Object& obj, World& world){
  if(target == NULL){
    target = get_target(obj, world);
    return;
  }

  // double speed_ = std::max(calc_distance(obj, *target)/(SCREEN_WIDTH*0.8), speed);
  double speed_ = speed;

  /* Only move if not inside the hitbox X boundaries */
  if(!(obj.x+obj.w < target->x+target->w
       && obj.x > target->x)){
    if(target->x+target->w/2 >= SCREEN_WIDTH/2){
      if(obj.x-obj.w/2 >= SCREEN_WIDTH/2){
        if(target->x+target->w/2 < obj.x+obj.w/2) obj.xspeed -= speed_;
        else obj.xspeed += speed_;
      }
      else{
        int normal_distance = abs(obj.x-target->x);
        int warp_distance = obj.x+(SCREEN_WIDTH-target->x+target->w);
        if(normal_distance <= warp_distance) obj.xspeed += speed_;
        else obj.xspeed -= speed_;
      }
    }
    else{
      if(obj.x-obj.w/2 <= SCREEN_WIDTH/2){
        if(target->x+target->w/2 < obj.x+obj.w/2) obj.xspeed -= speed_;
        else obj.xspeed += speed_;
      }
      else{
        int normal_distance = abs(obj.x-target->x);
        int warp_distance = (SCREEN_WIDTH-obj.x)+target->x;
        if(normal_distance <= warp_distance) obj.xspeed -= speed_;
        else obj.xspeed += speed_;
      }
    }
  }
  else if(fabs(obj.xspeed) < 0.5) obj.xspeed = 0;
}

void PlatformInputComponent
::update(Object& obj, World& world){
}

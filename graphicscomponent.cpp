#include "graphicscomponent.h"
#include "object.h"

void GeneralGraphicsComponent
::update(Object& obj, SDL_Renderer* renderer, double interp){
  int x_interp = obj.x+(int)(interp*obj.xspeed);
  int y_interp = obj.y+(int)(interp*obj.yspeed);
  SDL_Rect rect = {x_interp,y_interp,obj.w,obj.h};
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderFillRect(renderer, &rect);
}

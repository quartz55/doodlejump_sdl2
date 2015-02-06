#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class World;

class Game{

private:
  /* Members */
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event e;
  bool done;

  World* world;
  bool moveleft, moveright;
  
  /* Methods */
  void handleInput();
  void update();
  void render(double interp);
  void exit();

public:
  Game():window(NULL),renderer(NULL),done(false){}
  bool init();
  void loop();
};

#endif

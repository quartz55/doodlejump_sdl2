#include <iostream>
#include <time.h>
#include <unistd.h>
#include <vector>

#include "game.h"

#include "object.h"
#include "globals.h"
#include "world.h"

/* Components */
#include "physicscomponent.h"
#include "inputcomponent.h"
#include "graphicscomponent.h"

#define NPLATS 8
#define FPS 60

bool Game::init(){
  /* SDL stuff
   *   Make window and renderer */
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}
  else{
    window = SDL_CreateWindow("Doodle Jump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  }

  srand(time(NULL));

  /* Game World */
  World* game_world = new World();
  this->world = game_world;

  // Player
  // Object* pl = new Object(new PlayerInputComponent(&moveright, &moveleft),
  //                         new PlayerPhysicsComponent(),
  //                         new GeneralGraphicsComponent(255,255,255,255));
  Object* pl = new Object(new DemoInputComponent(),
                          new PlayerPhysicsComponent(),
                          new GeneralGraphicsComponent(255,255,255,255));
  pl->w=20;
  pl->h=40;
  pl->x = SCREEN_WIDTH/2-pl->w/2;
  pl->y = SCREEN_HEIGHT-pl->h-15;
  pl->yspeed = -22;
  world->change_player(pl);

  // Platforms
  for(unsigned int i = 0; i < NPLATS; i++){
    Object* plat = new Object(new PlatformInputComponent(),
                              new PlatformPhysicsComponent(),
                              new GeneralGraphicsComponent(100,190,230,255));
    plat->w = 70;
    plat->h = 15;

    if(i==0) plat->x = SCREEN_WIDTH/2-plat->w/2;
    else plat->x = rand()%SCREEN_WIDTH-plat->w;

    plat->y = SCREEN_HEIGHT-(i*100);
    
    world->add_platform(plat); /* Add platform to the world */
  }

  return true;
}

void Game::handleInput(){
  while(SDL_PollEvent(&e) != 0){
    switch(e.type){
    case SDL_QUIT:
      done = true;
      break;
    case SDL_KEYDOWN:
      if(e.key.keysym.sym == SDLK_ESCAPE) done = true;
      if(e.key.keysym.sym == SDLK_a) moveleft = true;
      if(e.key.keysym.sym == SDLK_d) moveright = true;
      break;
    case SDL_KEYUP:
      if(e.key.keysym.sym == SDLK_a) moveleft = false;
      if(e.key.keysym.sym == SDLK_d) moveright = false;
      break;
    }
  }
}

void Game::update(){
  world->update();

  Object* pl = world->get_player();
  if(pl->y+pl->h >= SCREEN_HEIGHT) done = true;

}

void Game::render(double interp){
  /* Clean renderer */
  SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
  SDL_RenderClear(renderer);

  /* Draw all objects to renderer */
  world->draw(renderer, interp);

  /* Draw renderer */
  SDL_RenderPresent(renderer);
}

void Game::loop(){
  while(!done){
    handleInput();
    update();
    render(0); /* No Interp */

    SDL_Delay(FPS_TO_MS(FPS));
  }
  exit();
}

void Game::exit(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  
  window = NULL;
  renderer = NULL;
  
	SDL_Quit();
}

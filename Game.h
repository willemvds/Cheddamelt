#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "Event.h"
#include "Surface.h"

class Game : public Event {
private:
  bool running;
  SDL_Surface* displaySurface;
  SDL_Surface* testSurface;
public:
  Game();
  int OnExecute();
  bool OnInit();
  void OnEvent(SDL_Event* event);
  void OnExit();
  void OnLoop();
  void OnRender();
  void OnCleanup();
};

#endif
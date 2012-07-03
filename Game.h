#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "Event.h"
#include "Surface.h"

class Game : public Event {
private:
  bool running;
  SDL_Surface* displaySurface;
  
  SDL_Surface* gridSurface;
  SDL_Surface* xSurface;
  SDL_Surface* oSurface;

  int grid[9];
  int currentPlayer;

  enum {
    GRID_TYPE_NONE = 0,
    GRID_TYPE_X,
    GRID_TYPE_O
  };

public:
  Game();
  int OnExecute();
  bool OnInit();
  
  void OnEvent(SDL_Event* event);
  void OnLButtonDown(int x, int y);
  
  void OnExit();
  void OnLoop();
  void OnRender();
  void OnCleanup();
  void Reset();

  void SetCell(int id, int type);
};

#endif

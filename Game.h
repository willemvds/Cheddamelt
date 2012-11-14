#ifndef GAME_H
#define GAME_H

//#include <direct.h>
#include <unistd.h>

#include <SDL/SDL.h>

#include "Define.h"
#include "Area.h"
#include "Camera.h"
#include "Entity.h"
#include "Event.h"
#include "Player.h"
#include "Surface.h"
#include "Animation.h"

class Game : public Event {
private:
  bool running;
  char* cwd;
  SDL_Surface* displaySurface;
  SDL_Surface* testSurface;
  Animation yoshiAnim;

  Entity entity1;
  Entity entity2;

  Player player1;
  Player player2;
public:
  Game();
  char* getCwd();
  int OnExecute();
  bool OnInit();
  void OnEvent(SDL_Event* event);
  void OnExit();
  void OnLoop();
  void OnRender();
  void OnCleanup();
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
};

#endif

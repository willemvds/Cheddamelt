#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "Entity.h"

class Player : public Entity
{
public:
  Player(void);
  bool Load(char* filename, int width, int height, int maxFrames);
  void OnLoop();
  void OnRender(SDL_Surface* displaySurface);
  void OnCleanup();
  void OnAnimate();
  void OnCollision(Entity* entity);
};

#endif
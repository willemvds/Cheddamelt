#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include <SDL.h>
#include "Animation.h"
#include "Surface.h"

class Entity
{
public:
  Entity();
  virtual ~Entity();
  static std::vector<Entity*> entityList;

protected:
  Animation animControl;
  SDL_Surface* entitySurface;

public:
  float x;
  float y;
  int width;
  int height;
  int animState;

  virtual bool Load(char* filename, int width, int height, int maxFrames);
  virtual void OnLoop();
  virtual void OnRender(SDL_Surface* displaySurface);
  virtual void OnCleanup();
};

#endif
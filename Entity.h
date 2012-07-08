#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include <SDL.h>
#include "Animation.h"
#include "Area.h"
#include "Camera.h"
#include "FPS.h"
#include "Surface.h"

enum {
  ENTITY_TYPE_GENERIC = 0,
  ENTITY_TYPE_PLAYER
};

enum {
  ENTITY_FLAG_NONE = 0,
  ENTITY_FLAG_GRAVITY = 0x00000001,
  ENTITY_FLAG_GHOST = 0x00000002,
  ENTITY_FLAG_MAPONLY = 0x00000004
};

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
  bool moveLeft;
  bool moveRight;
  int type;
  bool dead;
  int flags;
  int animState;

protected:
  float speedX;
  float speedY;
  float accelX;
  float accelY;
public:
  float maxSpeedX;
  float maxSpeedY;
protected:
  int currentFrameCol;
  int currentFrameRow;
  int colBoxX;
  int colBoxY;
  int colBoxWidth;
  int colBoxHeight;
public:
  virtual bool Load(char* filename, int width, int height, int maxFrames);
  virtual void OnLoop();
  virtual void OnRender(SDL_Surface* displaySurface);
  virtual void OnAnimate();
  virtual void OnCollision(Entity* entity);
  virtual void OnCleanup();

  void OnMove(float moveX, float moveY);
  void StopMove();
  bool Collides(int oX, int oY, int oW, int oH);
private:
  bool posValid(int newX, int newY);
  bool posValidTile(Tile* tile);
  bool posValidEntity(Entity* entity, int newX, int newY);
};

class EntityCollision {
public:
  EntityCollision();
  static std::vector<EntityCollision> entityCollisionList;
  Entity* entityA;
  Entity* entityB;
};

#endif
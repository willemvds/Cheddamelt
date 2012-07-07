#include "Entity.h"

std::vector<Entity*> Entity::entityList;

Entity::Entity() {
  entitySurface = NULL;
  x = 0.0f;
  y = 0.0f;
  width = 0;
  height = 0;
  animState = 0;
}

Entity::~Entity() {
}

bool Entity::Load(char* filename, int width, int height, int maxFrames) {
  if ((entitySurface = Surface::Load(filename)) == NULL) {
    return false;
  }

  Surface::Transparent(entitySurface, 255, 0, 255);

  this->height = height;
  this->width = width;
  animControl.maxFrames = maxFrames;
  
  return true;
}

void Entity::OnLoop() {
  animControl.OnAnimate();
}

void Entity::OnRender(SDL_Surface* displaySurface) {
  if (entitySurface == NULL || displaySurface == NULL) {
    return;
  }

  Surface::DrawRegion(displaySurface, entitySurface, x, y, animState * width, animControl.GetCurrentFrame() * height, width, height);
}

void Entity::OnCleanup() {
  if (entitySurface) {
    SDL_FreeSurface(entitySurface);
  }
  
  entitySurface = NULL;
}
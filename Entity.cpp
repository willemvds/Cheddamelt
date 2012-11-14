#include "Entity.h"

std::vector<Entity*> Entity::entityList;
std::vector<EntityCollision> EntityCollision::entityCollisionList;

EntityCollision::EntityCollision() {
  entityA = NULL;
  entityA = NULL;
}

Entity::Entity() {
  entitySurface = NULL;
  x = 0.0f;
  y = 0.0f;
  width = 0;
  height = 0;
  animState = 0;

  type = ENTITY_TYPE_GENERIC;
  dead = false;
  flags = ENTITY_FLAG_GRAVITY;

  speedX = 0;
  speedY = 0;
  maxSpeedX = 5;
  maxSpeedY = 5;
  currentFrameCol = 0;
  currentFrameRow = 0;
  colBoxX = 0;
  colBoxY = 0;
  colBoxWidth = 0;
  colBoxHeight = 0;
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
  if (moveLeft == false && moveRight == false) {
    StopMove();
  }
  if (moveLeft) {
    accelX = -0.5;
  }
  if (moveRight) {
    accelX = 0.5;
  }
  if (flags & ENTITY_FLAG_GRAVITY) {
    accelY = 0.75f;
  }
  speedX += accelX * FPS::fpsControl.getSpeedFactor();
  speedY += accelY * FPS::fpsControl.getSpeedFactor();

  if (speedX > maxSpeedX) speedX = maxSpeedX;
  if (speedX < -maxSpeedX) speedX = -maxSpeedX;
  if (speedY > maxSpeedY) speedY = maxSpeedY;
  if (speedY < -maxSpeedY) speedY = -maxSpeedY;

  OnAnimate();
  OnMove(speedX, speedY);
}

void Entity::OnCollision(Entity* entity) {

}

void Entity::OnMove(float moveX, float moveY) {
  if (moveX == 0 && moveY == 0) {
    return;
  }

  double newX = 0;
  double newY = 0;
  moveX *= FPS::fpsControl.getSpeedFactor();
  moveY *= FPS::fpsControl.getSpeedFactor();

  if (moveX != 0) {
    newX = FPS::fpsControl.getSpeedFactor();
    if (moveX < 0) {
      newX *= -1;
    }
  }

  if (moveY != 0) {
    newY = FPS::fpsControl.getSpeedFactor();
    if (moveY < 0) {
      newY *= -1;
    }
  }

  while (true) {
    if (flags & ENTITY_FLAG_GHOST) {
      posValid((int)(x + newX), (int)(y + newY)); // notify about collision, no action
      x += newX;
      y += newY;
    } else {
      if (posValid((int)(x + newX), (int)(y + newY))) {
        x += newX;
      } else {
        speedX = 0;
      }

      if (posValid((int)(y + newY), (int)(y + newY))) {
        y += newY;
      } else {
        speedY = 0;
      }
    }

    moveX += -newX;
    moveY += -newY;

    if (newX > 0 && moveX <= 0) newX = 0;
    if (newX < 0 && moveX >= 0) newX = 0;
    if (newY > 0 && moveY <= 0) newY = 0;
    if (newY < 0 && moveY >= 0) newY = 0;
    if (moveX == 0) newX = 0;
    if (moveY == 0) newY = 0;

    if (moveX == 0 && moveY == 0)
      break;
    if (newX == 0 && newY == 0)
      break;
  }
}

void Entity::StopMove() {
  if (speedX > 0) {
    accelX = -1;
  }

  if (speedX < 0) {
    accelX = 1;
  }

  if (speedX < 2.0f && speedX > -2.0f) {
    accelX = 0;
    speedX = 0;
  }
}

bool Entity::Collides(int oX, int oY, int oW, int oH) {
  int left1, left2;
  int right1, right2;
  int top1, top2;
  int bottom1, bottom2;

  int tX = (int)x + colBoxX;
  int tY = (int)y + colBoxY;

  left1 = tX;
  left2 = oX;
  right1 = left1 + width - 1 - colBoxWidth;
  right2 = oX + oW - 1;
  top1 = tY;
  top2 = oY;
  bottom1 = top1 + height - 1 - colBoxHeight;
  bottom2 = oY + oH - 1;

  if (bottom1 < top2) return false;
  if (top1 > bottom2) return false;
  if (right1 < left2) return false;
  if (left1 > right2) return false;

  return true;
}

bool Entity::posValid(int newX, int newY) {
  int startX = (newX + colBoxX) / TILE_SIZE;
  int startY = (newY + colBoxY) / TILE_SIZE;
  int endX = ((newX + colBoxX) + width - colBoxWidth - 1) / TILE_SIZE;
  int endY = ((newY + colBoxY) + height - colBoxHeight - 1) / TILE_SIZE;

  for (int iY = startY; iY <= endY; iY++) {
    for (int iX = startX; iX <= endX; iX++) {
      Tile* tile = Area::areaControl.getTile(iX * TILE_SIZE, iY * TILE_SIZE);
      if (posValidTile(tile) == false) {
        return false;
      }
    }
  }

  if (flags ^ ENTITY_FLAG_MAPONLY) {
    for (int i = 0; i < entityList.size(); i++) {
      if (posValidEntity(entityList[i], newX, newY) == false) {
        return false;
      }
    }
  }

  return true;
}

bool Entity::posValidTile(Tile* tile) {
  if (tile == NULL) {
    return true;
  }

  if (tile->typeId == TILE_TYPE_BLOCK) {
    return false;
  }

  return true;
}

bool Entity::posValidEntity(Entity* entity, int newX, int newY) {
  if (this != entity && entity != NULL && entity->dead == false
    && entity->flags ^ ENTITY_FLAG_MAPONLY &&
    entity->Collides(newX + colBoxX, newY + colBoxY, width - colBoxWidth - 1, height - colBoxHeight - 1)) {

    EntityCollision ec;
    ec.entityA = this;
    ec.entityB = entity;
    EntityCollision::entityCollisionList.push_back(ec);

    return false;
  }

  return true;
}

void Entity::OnAnimate() {
  if (moveLeft) {
    currentFrameCol = 0;
  } else if (moveRight) {
    currentFrameCol = 1;
  }
  animControl.OnAnimate();
}

void Entity::OnRender(SDL_Surface* displaySurface) {
  if (entitySurface == NULL || displaySurface == NULL) {
    return;
  }

  //Surface::DrawRegion(displaySurface, entitySurface, x, y, animState * width, animControl.GetCurrentFrame() * height, width, height);
  Surface::DrawRegion(displaySurface, entitySurface, x - Camera::cameraControl.getX(), y - Camera::cameraControl.getY(),
    currentFrameCol * width, (currentFrameRow + animControl.GetCurrentFrame()) * height, width, height);
}

void Entity::OnCleanup() {
  if (entitySurface) {
    SDL_FreeSurface(entitySurface);
  }

  entitySurface = NULL;
}

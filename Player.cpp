#include "Player.h"

Player::Player(void) {
}

bool Player::Load(char* filename, int width, int height, int maxFrames) {
  return Entity::Load(filename, width, height, maxFrames);
}

void Player::OnLoop() {
  Entity::OnLoop();
}

void Player::OnRender(SDL_Surface* displaySurface) {
  Entity::OnRender(displaySurface);
}

void Player::OnAnimate() {
  if (speedX != 0) {
    animControl.maxFrames = 8;
  } else {
    animControl.maxFrames = 0;
  }

  Entity::OnAnimate();
}

void Player::OnCollision(Entity* entity) {
  Entity::OnCollision(entity);
}

void Player::OnCleanup() {
  Entity::OnCleanup();
}

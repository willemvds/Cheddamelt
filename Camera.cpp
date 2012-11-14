#include "Camera.h"

Camera Camera::cameraControl;

Camera::Camera(void)
{
  x = 0;
  y = 0;
  targetX = NULL;
  targetY = NULL;
  targetMode = TARGET_MODE_NORMAL;
}

void Camera::OnMove(int moveX, int moveY) {
  x += moveX;
  y += moveY;
}

int Camera::getX() {
  if (targetX != NULL) {
    if (targetMode == TARGET_MODE_CENTER) {
      return *targetX - (WINDOWWIDTH / 2);
    }
    return *targetX;
  }
  return x;
}

int Camera::getY() {
  if (targetY != NULL) {
    if (targetMode == TARGET_MODE_CENTER) {
      return *targetY - (WINDOWHEIGHT / 2);
    }
    return *targetY;
  }
  return y;
}

void Camera::setPos(int x, int y) {
  this->x = x;
  this->y = y;
}

void Camera::setTarget(float* x, float* y) {
  this->targetX = x;
  this->targetY = y;
}

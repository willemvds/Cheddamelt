#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>
#include "Define.h"

enum {
  TARGET_MODE_NORMAL = 0,
  TARGET_MODE_CENTER
};

class Camera
{
public:
  Camera(void);
private:
  int x;
  int y;
  int* targetX;
  int* targetY;
public:
  static Camera cameraControl;
  int targetMode;
  void OnMove(int moveX, int moveY);
  int getX();
  int getY();
  void setPos(int x, int y);
  void setTarget(int* x, int* y);
};

#endif
#ifndef FPS_H
#define FPS_H

#include <SDL.h>

class FPS
{
public:
  FPS(void);
private:
  int oldTime;
  int lastTime;
  float speedFactor;
  int numFrames;
  int frames;
public:
  static FPS fpsControl;
  void OnLoop();
  int getFPS();
  float getSpeedFactor();
};

#endif
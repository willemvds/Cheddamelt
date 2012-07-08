#include "FPS.h"

FPS FPS::fpsControl;

FPS::FPS(void)
{
  oldTime = 0;
  lastTime = 0;
  speedFactor = 0.0;
  frames = 0;
  numFrames = 0;
}

void FPS::OnLoop() {
  Uint32 ticks = SDL_GetTicks();
  if (oldTime + 1000 < ticks) {
    oldTime = ticks;
    numFrames = frames;
    frames = 0;
  }

  speedFactor = ((ticks - lastTime) / 1000.0f) * 32.0f;
  lastTime = ticks;
  frames++;
}

int FPS::getFPS() {
  return numFrames;
}

float FPS::getSpeedFactor() {
  return speedFactor;
}
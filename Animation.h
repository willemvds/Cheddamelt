#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL/SDL.h>

class Animation {
private:
  int currentFrame;
  int frameInc;
  int frameRate;
  long oldTime;
public:
  int maxFrames;
  bool oscillate;
  Animation();
  void OnAnimate();
  void SetFrameRate(int rate);
  void SetCurrentFrame(int frame);
  int GetCurrentFrame();
};

#endif

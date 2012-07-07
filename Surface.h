#ifndef SURFACE_H
#define SURFACE_H

#include <SDL.h>
#include <SDL_image.h>

class Surface {
public:
  Surface();
  static SDL_Surface* Load(char* filename);
  static bool Draw(SDL_Surface* destSurface, SDL_Surface* srcSurface, int x, int y);
  static bool DrawRegion(SDL_Surface* destSurface, SDL_Surface* srcSurface, int x, int y, int x2, int y2, int w, int h);
  static bool Transparent(SDL_Surface* destSurface, int R, int G, int B);
};

#endif
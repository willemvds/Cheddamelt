#include "Surface.h"

Surface::Surface() {
}

SDL_Surface* Surface::Load(char* filename) {
  SDL_Surface* tempSurface = NULL;
  SDL_Surface* returnSurface = NULL;

  if ((tempSurface = SDL_LoadBMP(filename)) == NULL) {
    return NULL;
  }

  returnSurface = SDL_DisplayFormat(tempSurface);
  SDL_FreeSurface(tempSurface);
  return returnSurface;
}

bool Surface::Draw(SDL_Surface* destSurface, SDL_Surface* srcSurface, int x, int y) {
  if (destSurface == NULL || srcSurface == NULL) {
    return false;
  }

  SDL_Rect destRect;
  destRect.x = x;
  destRect.y = y;

  SDL_BlitSurface(srcSurface, NULL, destSurface, &destRect);

  return true;
}

bool Surface::DrawRegion(SDL_Surface* destSurface, SDL_Surface* srcSurface, int x, int y, int x2, int y2, int w, int h) {
  if (destSurface == NULL || srcSurface == NULL) {
    return false;
  }

  SDL_Rect destRect;
  destRect.x = x;
  destRect.y = y;

  SDL_Rect srcRect;
  srcRect.x = x2;
  srcRect.y = y2;
  srcRect.w = w;
  srcRect.h = h;

  SDL_BlitSurface(srcSurface, &srcRect, destSurface, &destRect);

  return true;
}
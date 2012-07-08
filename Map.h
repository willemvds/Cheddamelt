#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SDL.h>

#include "Tile.h"
#include "Surface.h"

class Map
{
public:
  Map();
private:
  std::vector<Tile> tileList;
public:
  SDL_Surface* tilesetSurface;
  Tile* getTile(int x, int y);
  bool Load(char* filename);
  void OnRender(SDL_Surface* displaySurface, int mapX, int mapY);
};

#endif
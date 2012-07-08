#ifndef AREA_H
#define AREA_H

#include "Map.h"

class Area
{
public:
  Area(void);
private:
  int areaSize;
  SDL_Surface* tilesetSurface;
public:
  static Area areaControl;
  std::vector<Map> mapList;

  Map* getMap(int x, int y);
  Tile* getTile(int x, int y);

  bool Load(char* filename);
  void OnRender(SDL_Surface* displaySurface, int cameraX, int cameraY);
  void OnCleanup();
};

#endif
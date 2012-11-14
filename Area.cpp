#include "Area.h"

Area Area::areaControl;

Area::Area(void)
{
  areaSize = 0;
}

bool Area::Load(char* filename) {
  mapList.clear();

  FILE* fileHandle = fopen(filename, "r");

  if (fileHandle == NULL) {
    return false;
  }

  char tilesetFilename[255];

  fscanf(fileHandle, "%s\n", tilesetFilename);
  if ((tilesetSurface = Surface::Load(tilesetFilename)) == false) {
    fclose(fileHandle);
    return false;
  }

  fscanf(fileHandle, "%d\n", &areaSize);

  for (int x = 0; x < areaSize; x++) {
    for (int y = 0; y < areaSize; y++) {
      char mapFilename[255];
      fscanf(fileHandle, "%s", mapFilename);

      Map tempMap;
      if (tempMap.Load(mapFilename) == false) {
        fclose(fileHandle);
        return false;
      }

      tempMap.tilesetSurface = tilesetSurface;
      mapList.push_back(tempMap);
    }
    fscanf(fileHandle, "\n");
  }
  fclose(fileHandle);
  return true;
}

Map* Area::getMap(int x, int y) {
  int mapWidth = MAP_WIDTH * TILE_SIZE;
  int mapHeight = MAP_WIDTH * TILE_SIZE;

  int id = (x / mapWidth) + ((y / mapHeight) * areaSize);
  if (id < 0 || id >= mapList.size()) {
    return NULL;
  }

  return &mapList[id];
}

Tile* Area::getTile(int x, int y) {
  int mapWidth = MAP_WIDTH * TILE_SIZE;
  int mapHeight = MAP_HEIGHT * TILE_SIZE;
  Map* map = getMap(x, y);
  if (map == NULL) {
    return NULL;
  }

  x = x % mapWidth;
  y = y % mapHeight;

  return map->getTile(x, y);
}

void Area::OnRender(SDL_Surface* displaySurface, int cameraX, int cameraY) {
  int mapWidth = MAP_WIDTH * TILE_SIZE;
  int mapHeight = MAP_HEIGHT * TILE_SIZE;

  int firstId = -cameraX / mapWidth;
  firstId = firstId + ((-cameraY / mapHeight) * areaSize);

  for (int i = 0; i < 4; i++) {
    int id = firstId + ((i / 2) * areaSize) + (i % 2);
    if (id < 0 || id >= mapList.size())
      continue;

    int x = ((id % areaSize) * mapWidth) + cameraX;
    int y = ((id / areaSize) * mapHeight) + cameraY;
    mapList[id].OnRender(displaySurface, x, y);
  }
}

void Area::OnCleanup() {
  if (tilesetSurface) {
    SDL_FreeSurface(tilesetSurface);
  }

  mapList.clear();
}

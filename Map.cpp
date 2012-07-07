#include "Map.h"

Map::Map(void)
{
  tilesetSurface = NULL;
}

bool Map::Load(char* filename) {
  tileList.clear();
  FILE* fileHandle = fopen(filename, "r");
  if (fileHandle == NULL) {
    return false;
  }

  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      Tile tempTile;
      fscanf(fileHandle, "%d:%d", &tempTile.tileId, &tempTile.typeId);
      tileList.push_back(tempTile);
    }
    fscanf(fileHandle, "\n");
  }
  fclose(fileHandle);
  return true;
}

void Map::OnRender(SDL_Surface* displaySurface, int mapX, int mapY) {
  if (tilesetSurface == NULL) {
    return;
  }

  int tilesetWidth = tilesetSurface->w / TILE_SIZE;
  int tilesetHeight = tilesetSurface->h / TILE_SIZE;

  int id = 0;

  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      if (tileList[id].typeId == TILE_TYPE_NONE) {
        id++;
        continue;
      }

      int tX = mapX + (x * TILE_SIZE);
      int tY = mapY + (y * TILE_SIZE);

      int tilesetX = (tileList[id].tileId % tilesetWidth) * TILE_SIZE;
      int tilesetY = (tileList[id].tileId * tilesetHeight) * TILE_SIZE;

      Surface::DrawRegion(displaySurface, tilesetSurface, tX, tY, tilesetX, tilesetY, TILE_SIZE, TILE_SIZE);

      id++;
    }
  }
}
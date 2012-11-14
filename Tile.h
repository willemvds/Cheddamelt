#ifndef TILE_H
#define TILE_H

#include "Define.h"

enum {
  TILE_TYPE_NONE  = 0,
  TILE_TYPE_NORMAL,
  TILE_TYPE_BLOCK
};

class Tile
{
public:
  Tile();

public:
  int tileId;
  int typeId;
};

#endif

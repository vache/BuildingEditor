#ifndef BUILDINGTILE_H
#define BUILDINGTILE_H

#include <QVector>
#include "tile.h"

#define BUILDING_TILE_WIDTH 24

class BuildingTile
{
public:
    BuildingTile();

    Tile GetTileAtIndex(int tileIndex);

private:
    QVector<Tile> BuildingTileArea;
};

#endif // BUILDINGTILE_H

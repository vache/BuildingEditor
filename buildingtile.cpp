#include "buildingtile.h"

BuildingTile::BuildingTile()
{
}

Tile BuildingTile::GetTileAtIndex(int tileIndex)
{
    return BuildingTileArea.at(tileIndex);
}

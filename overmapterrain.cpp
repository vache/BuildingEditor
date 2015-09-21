#include "overmapterrain.h"

OvermapTerrain::OvermapTerrain(bool active) : _active(active)
{
}

Tile OvermapTerrain::GetTileAtIndex(int tileIndex)
{
    return BuildingTileArea.at(tileIndex);
}

Tile& OvermapTerrain::GetTile(Tripoint p)
{
    return _tiles[p];
}

void OvermapTerrain::SetTile(Tripoint p, Tile t)
{
    _tiles[p] = t;
}

QList<Tile> OvermapTerrain::GetTiles()
{
    return _tiles.values();
}

void OvermapTerrain::SetActive(bool active)
{
    _active = active;

    if (_active)
    {
        _tiles.clear();
        Tile t;
        for (int i = 0; i < OVERMAP_TERRAIN_WIDTH; i++)
        {
            for (int j = 0; j < OVERMAP_TERRAIN_WIDTH; j++)
            {
                _tiles[Tripoint(i, j, 0)] = t; // TODO z level
            }
        }
    }
    else
    {
        _tiles.clear();
    }
}

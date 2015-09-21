#ifndef OVERMAPTERRAIN_H
#define OVERMAPTERRAIN_H

#include <QVector>
#include <QMap>
#include "tripoint.h"
#include "tile.h"

#define OVERMAP_TERRAIN_WIDTH 24

class OvermapTerrain
{
public:
    OvermapTerrain(bool active = false);

    inline bool IsActive() const { return _active; }
    void SetActive(bool active);
    Tile GetTileAtIndex(int tileIndex);
    Tile& GetTile(Tripoint p);
    void SetTile(Tripoint p, Tile t);
    QList<Tile> GetTiles();

private:
    bool _active;
    QVector<Tile> BuildingTileArea;
    QMap<Tripoint, Tile> _tiles;
};

#endif // OVERMAPTERRAIN_H

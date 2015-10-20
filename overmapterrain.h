#ifndef OVERMAPTERRAIN_H
#define OVERMAPTERRAIN_H

#include <QVector>
#include <QMap>
#include "tripoint.h"
#include "tile.h"
#include "omtdata.h"

#define OVERMAP_TERRAIN_WIDTH 24

class OvermapTerrain
{
public:
    OvermapTerrain(bool active = false);

    inline bool IsActive() const { return _active; }
    void SetActive(bool active);
    Tile& GetTile(Tripoint p);
    void SetTile(Tripoint p, Tile t);
    void SetTile(int row, int col, Tile t);

    void SetData(OMTData data) { _data = data; }
    OMTData GetData() const { return _data; }

    QList<Tile> GetTiles();

private:
    bool _active;
    QVector<Tile> BuildingTileArea;
    QMap<Tripoint, Tile> _tiles;
    OMTData _data;
};

#endif // OVERMAPTERRAIN_H

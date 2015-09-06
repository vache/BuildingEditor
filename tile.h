#ifndef TILE_H
#define TILE_H

#include <QList>
#include <QChar>
#include <QColor>

#include "terrain.h"
#include "furniture.h"

class Tile
{
public:
    Tile();
    // Convert to role enum...
    QChar GetChar(QString role) const;
    QList<QChar> GetExportChars() const;
    QChar GetDisplayChar() const;
    QChar GetTerrainChar() const;
    QChar GetFurnitureChar() const;

    QColor GetForegroundColor() const;
    QColor GetBackgroundColor() const;

    inline void SetTerrain(QString terrain) { _terrain = terrain; }
    inline void SetFurniture(QString furniture) { _furniture = furniture; }
    inline QString GetTerrainID() const { return _terrain; }
    inline QString GetFurnitureID() const { return _furniture; }

    bool ExportEquivalent(const Tile& other) const;
    bool operator==(const Tile& other) const;

private:
    QString _terrain;
    QString _furniture;
};

#endif // TILE_H


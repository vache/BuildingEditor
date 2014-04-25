#ifndef TILE_H
#define TILE_H

#include <QChar>
#include <QColor>

class Tile
{
public:
    Tile();
    QChar GetExportChar();
    QChar GetDisplayChar();
    QChar GetTerrainChar();
    QChar GetFurnitureChar();

    QColor GetForegroundColor();
    QColor GetBackgroundColor();
};

#endif // TILE_H

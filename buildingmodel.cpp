#include "buildingmodel.h"
#include <QBrush>
#include <QVector>
#include <QDebug>
#include <QDateTime>

BuildingModel::BuildingModel(bool active[][10], QObject *parent) :
    QAbstractTableModel(parent), _rows(0), _cols(0)
{
    int maxX = 0;
    int maxY = 0;
    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            OvermapTerrain t;
            t.SetActive(active[row][col]);
            _omts[Tripoint(col, row, 0)] = t;

            if (active[row][col])
            {
                maxX = qMax(maxX, col+1);
                maxY = qMax(maxY, row+1);
            }
        }
    }

    _rows = maxY * OVERMAP_TERRAIN_WIDTH;
    _cols = maxX * OVERMAP_TERRAIN_WIDTH;
}

int BuildingModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _rows;
}

int BuildingModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _cols;
}

// this method ends up being very expensive, called many times on scroll, move, etc.
// maybe consider making maps use pointers for values?
// or do away with the maps in favor of basic lists?
QVariant BuildingModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    Tripoint p = GetOMTIndex(index);
    Tripoint tp = GetTileIndex(index);
    OvermapTerrain omt = _omts[p];

    // output if we have inactive tiles for disjointed specials, ex: O  O
    if (!omt.IsActive())
    {
        switch(role)
        {
        case Qt::DisplayRole:
            return QChar(' ');
        case Qt::BackgroundRole:
            return QBrush(Qt::gray);
        case Qt::ForegroundRole:
            return QBrush(Qt::gray);
        case ExportRole:
            return QChar(' ');
        default:
            return QVariant();
        }
    }

    Tile tile = omt.GetTile(tp);

    switch(role)
    {
    case Qt::DisplayRole:
        return tile.GetDisplayChar();
    case Qt::BackgroundRole:
        return QBrush(tile.GetBackgroundColor());
    case Qt::ForegroundRole:
        return QBrush(tile.GetForegroundColor());
    default:
        return QVariant();
    }

    return QVariant();
}

bool BuildingModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Tile t = GetTileFromIndex(index);
    switch(role)
    {
    case TerrainRole:
        t.SetTerrain(value.toString());
        // TODO clunky way of doing this.  pointers would probably make this better as well
        _omts[GetOMTIndex(index)].SetTile(GetTileIndex(index), t);
        emit dataChanged(index, index);
        return true;
    case FurnitureRole:
        t.SetFurniture(value.toString());
        _omts[GetOMTIndex(index)].SetTile(GetTileIndex(index), t);
        emit dataChanged(index, index);
        return true;
    default:
        return false;
    }
    return false;
}

QList<OvermapTerrain> BuildingModel::GetOvermapTerrains()
{
    return _omts.values();
}

Tripoint BuildingModel::GetOMTIndex(const QModelIndex& index) const
{
    // for a 10x10, index will be 0-239, 0-239
    int x = index.column() / OVERMAP_TERRAIN_WIDTH;
    int y = index.row() / OVERMAP_TERRAIN_WIDTH;
    int z = 0; // TODO fill in

    return Tripoint(x, y, z);
}

OvermapTerrain BuildingModel::GetOMTFromIndex(const QModelIndex & index)
{
    return _omts[GetOMTIndex(index)];
}

Tripoint BuildingModel::GetTileIndex(const QModelIndex& index) const
{
    // for a 10x10, index will be 0-239, 0-239
    int x = index.column() % OVERMAP_TERRAIN_WIDTH;
    int y = index.row() % OVERMAP_TERRAIN_WIDTH;
    int z = 0; // TODO fill in

    return Tripoint(x, y, z);
}

Tile BuildingModel::GetTileFromIndex(const QModelIndex & index)
{
    return GetOMTFromIndex(index).GetTile(GetTileIndex(index));
}

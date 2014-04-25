#include "buildingmodel.h"
#include <QBrush>

BuildingModel::BuildingModel(int dimension, QObject *parent) :
    _dimension(dimension), QAbstractTableModel(parent)
{
}

int BuildingModel::rowCount(const QModelIndex &parent) const
{
    return _dimension * BUILDING_TILE_WIDTH;
}

int BuildingModel::columnCount(const QModelIndex &parent) const
{
    return _dimension * BUILDING_TILE_WIDTH;
}

QVariant BuildingModel::data(const QModelIndex &index, int role) const
{
    Tile tile = this->GetTileAtIndex(index);

    switch(role)
    {
    case Qt::DisplayRole:
        return tile.GetDisplayChar();
        break;
    case Qt::BackgroundRole:
        return QBrush(tile.GetBackgroundColor());
        break;
    case Qt::ForegroundRole:
        return QBrush(tile.GetForegroundColor());
        break;
    default:
        return QVariant();
        break;
    }
}

Tile BuildingModel::GetTileAtIndex(QModelIndex modelIndex) const
{
    //   x
    // y 0 1 2
    //   3 4 5
    //   6 7 8
    // tile 0: (0, 0) to (23, 23), tile 1: (24, 0) to (47, 23), tile 2: (48, 0) to (71, 23)
    // tile 3: (0, 24) to (23, 47), tile 4: (24, 24) to (47, 47), tile 5: (48, 24) to (71, 47)
    // tile 6: (0, 48) to (23, 71), tile 7: (24, 48) to (47, 71), tile 8: (48, 48) to (71, 71)

    int buildingTileIndex = ((modelIndex.row() / BUILDING_TILE_WIDTH) * _dimension) +
            (modelIndex.column() / BUILDING_TILE_WIDTH);

    BuildingTile tile = _tiles.at(buildingTileIndex);

    int tileIndex = ((modelIndex.row() % BUILDING_TILE_WIDTH) * BUILDING_TILE_WIDTH) +
            (modelIndex.column() % BUILDING_TILE_WIDTH);

    return tile.GetTileAtIndex(tileIndex);
}

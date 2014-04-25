#ifndef BUILDINGMODEL_H
#define BUILDINGMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "buildingtile.h"
#include "tile.h"

class BuildingModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit BuildingModel(int dimension, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

signals:

public slots:

private:
    QVector<BuildingTile> _tiles;
    int _dimension;

    Tile GetTileAtIndex(QModelIndex modelIndex) const;
};

#endif // BUILDINGMODEL_H

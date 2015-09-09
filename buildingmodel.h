#ifndef BUILDINGMODEL_H
#define BUILDINGMODEL_H

#include <QAbstractTableModel>
#include <QMap>
#include "overmapterrain.h"
#include "tile.h"
#include "tripoint.h"

enum CustomRoles { ExportRole = Qt::UserRole + 1, FeatureTypeRole, TerrainRole, FurnitureRole,
                   TrapRole, MonsterGroupRole };

class BuildingModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit BuildingModel(bool active[][10], QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    QList<OvermapTerrain> GetOvermapTerrains();

signals:

public slots:

private:
    int _rows;
    int _cols;
    QMap<Tripoint, OvermapTerrain> _omts;

    Tripoint GetOMTIndex(const QModelIndex &index) const;
    OvermapTerrain GetOMTFromIndex(const QModelIndex & index);
    Tripoint GetTileIndex(const QModelIndex &index) const;
    Tile GetTileFromIndex(const QModelIndex & index);
};

#endif // BUILDINGMODEL_H

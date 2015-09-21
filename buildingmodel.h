#ifndef BUILDINGMODEL_H
#define BUILDINGMODEL_H

#include <QAbstractTableModel>
#include <QMap>
#include <QVector>
#include "overmapterrain.h"
#include "tile.h"
#include "tripoint.h"

enum CustomRoles { ExportRole = Qt::UserRole + 1, FeatureTypeRole, TerrainRole, FurnitureRole,
                   TrapRole, MonsterGroupRole, ItemGroupRole, ItemRole, MonsterRole, VehicleRole,
                   ToiletRole, NpcRole, VendingRole, SignRole };

// convert to LINE_XXXX to match cata convention?
enum DirectionalLine { NS = 0, EW, NE, NW, SE, SW, NES, NSW, NEW, ESW, NESW };
enum DirectionBits { NORTH=1, EAST=(1<<1), SOUTH=(1<<2), WEST=(1<<3) };

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
    Tripoint GetOMTIndex(int row, int column) const;
    OvermapTerrain GetOMTFromIndex(const QModelIndex & index) const;
    Tripoint GetTileIndex(const QModelIndex &index) const;
    Tripoint GetTileIndex(int row, int column) const;
    Tile GetTileFromIndex(const QModelIndex & index) const;

    QChar GetLineDrawingChar(const QModelIndex & index) const;
};

#endif // BUILDINGMODEL_H

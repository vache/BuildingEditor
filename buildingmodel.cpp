#include "buildingmodel.h"
#include <QBrush>
#include <QVector>
#include <QDebug>
#include <QDateTime>
#include "features.h"

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
    {
        if (tile.IsLineDrawing())
        {
            return GetLineDrawingChar(index);
        }
        return tile.GetDisplayChar();
    }
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
    OvermapTerrain omt = GetOMTFromIndex(index);
    if (!omt.IsActive())
    {
        return false;
    }
    Tile t = omt.GetTile(GetTileIndex(index));
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
    case TrapRole:
        t.SetTrap(value.toString());
        _omts[GetOMTIndex(index)].SetTile(GetTileIndex(index), t);
        emit dataChanged(index, index);
        return true;
    case MonsterGroupRole:
        t.SetMonsterGroup(value.value<MonsterGroup>());
        _omts[GetOMTIndex(index)].SetTile(GetTileIndex(index), t);
        emit dataChanged(index, index);
        return true;
    case ItemGroupRole:
        t.SetItemGroup(value.value<ItemGroup>());
        _omts[GetOMTIndex(index)].SetTile(GetTileIndex(index), t);
        emit dataChanged(index, index);
    case MonsterRole:
        t.SetMonster(value.toString());
        _omts[GetOMTIndex(index)].SetTile(GetTileIndex(index), t);
        emit dataChanged(index, index);
        return true;
    case ItemRole:
        t.AddItem(value.toString());
        _omts[GetOMTIndex(index)].SetTile(GetTileIndex(index), t);
        emit dataChanged(index, index);
        return true;
    case VehicleRole:
        t.SetVehicle(value.value<Vehicle>());
        _omts[GetOMTIndex(index)].SetTile(GetTileIndex(index), t);
        emit dataChanged(index, index);
        return true;
    case ToiletRole:
        t.SetToilet(value.toBool());
        _omts[GetOMTIndex(index)].SetTile(GetTileIndex(index), t);
        emit dataChanged(index, index);
        return true;
    case NpcRole:
        t.SetNPC(value.toString());
        _omts[GetOMTIndex(index)].SetTile(GetTileIndex(index), t);
        emit dataChanged(index, index);
        break;
    case SignRole:
        qDebug() << value.toString();
        t.SetSignage(value.toString());
        _omts[GetOMTIndex(index)].SetTile(GetTileIndex(index), t);
        emit dataChanged(index, index);
        break;
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
    return GetOMTIndex(index.row(), index.column());
}

Tripoint BuildingModel::GetOMTIndex(int row, int column) const
{
    // for a 10x10, index will be 0-239, 0-239
    int x = column / OVERMAP_TERRAIN_WIDTH;
    int y = row / OVERMAP_TERRAIN_WIDTH;
    int z = 0; // TODO fill in

    return Tripoint(x, y, z);
}

OvermapTerrain BuildingModel::GetOMTFromIndex(const QModelIndex & index) const
{
    return _omts[GetOMTIndex(index)];
}

Tripoint BuildingModel::GetTileIndex(const QModelIndex& index) const
{
    return GetTileIndex(index.row(), index.column());
}

Tripoint BuildingModel::GetTileIndex(int row, int column) const
{
    int x = column % OVERMAP_TERRAIN_WIDTH;
    int y = row % OVERMAP_TERRAIN_WIDTH;
    int z = 0;

    return Tripoint(x, y, z);
}

Tile BuildingModel::GetTileFromIndex(const QModelIndex & index) const
{
    return GetOMTFromIndex(index).GetTile(GetTileIndex(index));
}

QChar BuildingModel::GetLineDrawingChar(const QModelIndex & index) const
{
    // NS, EW, NE, NW, ES, SW, NES, NSW, NEW, ESW, NESW
    static QList<QChar> lineDrawingChars = { 0x2502, 0x2500, 0x2514, 0x2518, 0x250C, 0x2510, 0x251C, 0x2524, 0x2534, 0x252C, 0x253C };

    int neighbors = 0;
    QModelIndex adjacent = this->index(index.row(), index.column()+1);
    if (adjacent.isValid())
    {
        QString terrain = GetTileFromIndex(adjacent).GetTerrainID();
        if (Features::GetTerrain(terrain).HasFlag("CONNECT_TO_WALL") || Features::GetTerrain(terrain).HasFlag("AUTO_WALL_SYMBOL"))
        {
            neighbors |= EAST;
        }
    }

    adjacent = this->index(index.row(), index.column()-1);
    if (adjacent.isValid())
    {
        QString terrain = GetTileFromIndex(adjacent).GetTerrainID();
        if (Features::GetTerrain(terrain).HasFlag("CONNECT_TO_WALL") || Features::GetTerrain(terrain).HasFlag("AUTO_WALL_SYMBOL"))
        {
            neighbors |= WEST;
        }
    }

    adjacent = this->index(index.row()-1, index.column());
    if (adjacent.isValid())
    {
        QString terrain = GetTileFromIndex(adjacent).GetTerrainID();
        if (Features::GetTerrain(terrain).HasFlag("CONNECT_TO_WALL") || Features::GetTerrain(terrain).HasFlag("AUTO_WALL_SYMBOL"))
        {
            neighbors |= NORTH;
        }
    }

    adjacent = this->index(index.row()+1, index.column());
    if (adjacent.isValid())
    {
        QString terrain = GetTileFromIndex(adjacent).GetTerrainID();
        if (Features::GetTerrain(terrain).HasFlag("CONNECT_TO_WALL") || Features::GetTerrain(terrain).HasFlag("AUTO_WALL_SYMBOL"))
        {
            neighbors |= SOUTH;
        }
    }

    switch(neighbors)
    {
    case 0:
    case (NORTH | EAST | SOUTH | WEST):
        return lineDrawingChars[NESW];
    case (NORTH):
    case (SOUTH):
    case (NORTH | SOUTH):
        return lineDrawingChars[NS];
    case (EAST):
    case (WEST):
    case (EAST | WEST):
        return lineDrawingChars[EW];
    case (NORTH | EAST):
        return lineDrawingChars[NE];
    case (SOUTH | EAST):
        return lineDrawingChars[SE];
    case (NORTH | EAST | SOUTH):
        return lineDrawingChars[NES];
    case (NORTH | WEST):
        return lineDrawingChars[NW];
    case (NORTH | EAST | WEST):
        return lineDrawingChars[NEW];
    case (SOUTH | WEST):
        return lineDrawingChars[SW];
    case (NORTH | SOUTH | WEST):
        return lineDrawingChars[NSW];
    case (EAST | SOUTH | WEST):
        return lineDrawingChars[ESW];
    default:
        return lineDrawingChars[NESW];
    }
}

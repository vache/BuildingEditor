#ifndef TILE_H
#define TILE_H

#include <QList>
#include <QChar>
#include <QColor>
#include "itemgroup.h"
#include "monstergroup.h"
#include "vehicle.h"
#include <QDebug>

class Tile
{
public:
    Tile();
    // TODO Convert to role enum...
    QChar GetChar(QString role) const;
    QList<QChar> GetExportChars() const;

    QChar GetDisplayChar() const;
    QChar GetTerrainChar() const;
    QChar GetFurnitureChar() const;
    QChar GetTrapChar() const;

    QColor GetForegroundColor() const;
    QColor GetBackgroundColor() const;

    //inline void SetTerrain(QString terrain) { _terrain = terrain; }
    void SetTerrain(QString terrain);
    //inline void SetFurniture(QString furniture) { _furniture = furniture; }
    void SetFurniture(QString furniture);
    //inline void SetTrap(QString trap) { _trap = trap; }
    void SetTrap(QString trap);
    inline void SetMonsterGroup(MonsterGroup monGroup) { _monsterGroup = monGroup; }
    void AddItem(QString item);
    inline void SetMonster(QString monster) { _monster = monster; }
    inline void SetItemGroup(ItemGroup itemGroup) { _itemGroup = itemGroup; }
    inline void SetVehicle(Vehicle vehicle) { _vehicle = vehicle; }
    inline void SetToilet(bool toilet) { _toilet = toilet; }

    inline QString GetTerrainID() const { return _terrain; }
    inline QString GetFurnitureID() const { return _furniture; }
    inline QString GetTrapID() const { return _trap; }
    inline MonsterGroup GetMonsterGroup() const { return _monsterGroup; }
    inline QList<QString> GetItems() const { return _items; }
    inline QString GetMonster() const { return _monster; }
    inline ItemGroup GetItemGroup() const { return _itemGroup; }
    inline Vehicle GetVehicle() const { return _vehicle; }
    inline bool GetToilet() const { return _toilet; }

    bool ExportEquivalent(const Tile& other) const;
    bool operator==(const Tile& other) const;

    Tile& operator=(const Tile& other);

private:
    QString _terrain;
    QString _furniture;
    QString _trap;
    MonsterGroup _monsterGroup;
    QStringList _items;
    QString _monster;
    ItemGroup _itemGroup;
    Vehicle _vehicle;
    bool _toilet; // TODO this shouldnt be a bool for long, but it works for this release.
};

#endif // TILE_H


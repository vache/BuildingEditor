#ifndef TILE_H
#define TILE_H

#include <QList>
#include <QChar>
#include <QColor>
#include "itemgroup.h"
#include "monstergroup.h"
#include "vehicle.h"
#include "gaspump.h"
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
    void SetNPC(QString npc);
    void SetSignage(QString signage);
    inline void SetRadiation(int radiation) { _radiation = radiation; }
    void SetVending(QString vending);
    void SetGasPump(GasPump gasPump);

    inline QString GetTerrainID() const { return _terrain; }
    inline QString GetFurnitureID() const { return _furniture; }
    inline QString GetTrapID() const { return _trap; }
    inline MonsterGroup GetMonsterGroup() const { return _monsterGroup; }
    inline QList<QString> GetItems() const { return _items; }
    inline QString GetMonster() const { return _monster; }
    inline ItemGroup GetItemGroup() const { return _itemGroup; }
    inline Vehicle GetVehicle() const { return _vehicle; }
    inline bool GetToilet() const { return _toilet; }
    inline QString GetNPC() const { return _npc; }
    inline QString GetSignage() const { return _signage; }
    inline int GetRadiation() const { return _radiation; }
    inline QString GetVending() const { return _vending; }
    inline GasPump GetGasPump() const { return _gasPump; }

    bool IsLineDrawing() const;

    bool ExportEquivalent(const Tile& other) const;
    bool operator==(const Tile& other) const;

    //Tile& operator=(const Tile& other);

    void DumpTileData();

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
    QString _vending;
    QString _npc;
    QString _signage;
    int _radiation;
    GasPump _gasPump;
};

#endif // TILE_H


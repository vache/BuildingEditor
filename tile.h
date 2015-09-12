#ifndef TILE_H
#define TILE_H

#include <QList>
#include <QChar>
#include <QColor>
#include "itemgroup.h"
#include "monstergroup.h"
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

    inline void SetTerrain(QString terrain) { _terrain = terrain; }
    inline void SetFurniture(QString furniture) { _furniture = furniture; }
    inline void SetTrap(QString trap) { _trap = trap; }
    inline void SetMonsterGroup(MonsterGroup monGroup) { _monsterGroup = monGroup; }
    inline void AddItem(QString item) { _items.append(item); }
    inline void SetMonster(QString monster) { _monster = monster; }
    inline void SetItemGroup(ItemGroup itemGroup) { _itemGroup = itemGroup; }

    inline QString GetTerrainID() const { return _terrain; }
    inline QString GetFurnitureID() const { return _furniture; }
    inline QString GetTrapID() const { return _trap; }
    inline MonsterGroup GetMonsterGroup() const { return _monsterGroup; }
    inline QList<QString> GetItems() const { return _items; }
    inline QString GetMonster() const { return _monster; }
    inline ItemGroup GetItemGroup() const { return _itemGroup; }

    bool ExportEquivalent(const Tile& other) const;
    bool operator==(const Tile& other) const;

private:
    QString _terrain;
    QString _furniture;
    QString _trap;
    MonsterGroup _monsterGroup;
    QList<QString> _items;
    QString _monster;
    ItemGroup _itemGroup;
};

#endif // TILE_H


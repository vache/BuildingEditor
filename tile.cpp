#include "tile.h"
#include "features.h"
#include <QDebug>

// TODO review all placement to ensure still valid.  double check with added specals

Tile::Tile() : _terrain(null_terrain.GetID()), _furniture(null_furniture.GetID()), _trap(null_trap.GetID()),
    _monsterGroup(null_monster_group), _items(QStringList()),_monster(""), _itemGroup(null_item_group),
    _vehicle(null_vehicle), _toilet(false), _vending(""), _npc(""), _signage(""), _radiation(0), _gasPump(GasPump()),
    _rubble(null_rubble)
{
}

QChar Tile::GetChar(QString role) const
{
    if (role == "terrain")
    {
        return GetTerrainChar();
    }
    else if (role == "furniture")
    {
        return GetFurnitureChar();
    }
    else if (role == "trap")
    {
        return GetTrapChar();
    }
    else
    {
        return QChar(' ');
    }
}

QList<QChar> Tile::GetExportChars() const
{
    QList<QChar> preferredChars;
    QString temp = _furniture;
    temp.remove("f_");
    if (_furniture != "f_null")
    {
        Furniture f = Features::GetFurniture(_furniture);
        preferredChars.append(f.GetSymbol());
        preferredChars.append(temp[0]);
        preferredChars.append(temp[0].toUpper());
    }
    else if (_trap != "tr_null")
    {
        temp = _trap;
        temp.remove("tr_");
        Trap tr = Features::GetTrap(_trap);
        preferredChars.append(tr.GetSymbol());
        preferredChars.append(temp[0]);
        preferredChars.append(temp[0].toUpper());
    }
    else
    {
        temp = _terrain;
        temp.remove("t_");
        Terrain t = Features::GetTerrain(_terrain);
        if (t.HasFlag("AUTO_WALL_SYMBOL"))
        {
            preferredChars.append('|');
            preferredChars.append('-');
        }
        else if (t.HasFlag("FLAT") || t.HasFlag("ROAD"))
        {
            preferredChars.append('.');
            preferredChars.append('_');
            preferredChars.append('`');
        }
        else
        {
            preferredChars.append(t.GetSymbol());
        }
        preferredChars.append(temp[0]);
        preferredChars.append(temp[0].toUpper());
    }
    return preferredChars;
}

QChar Tile::GetDisplayChar() const
{
    if (_furniture != "f_null")
    {
        return GetFurnitureChar();
    }
    else if (_trap != "tr_null")
    {
        return GetTrapChar();
    }
    return GetTerrainChar();
}

QChar Tile::GetTerrainChar() const
{
    return Features::GetTerrain(_terrain).GetSymbol();
}

QChar Tile::GetFurnitureChar() const
{
    return Features::GetFurniture(_furniture).GetSymbol();
}

QChar Tile::GetTrapChar() const
{
    return Features::GetTrap(_trap).GetSymbol();
}

QColor Tile::GetForegroundColor() const
{
    if (_furniture != "f_null")
    {
        return Features::GetFurniture(_furniture).GetForeground();
    }
    else if (_trap != "tr_null")
    {
        return Features::GetTrap(_trap).GetForeground();
    }
    return Features::GetTerrain(_terrain).GetForeground();
}

QColor Tile::GetBackgroundColor() const
{
    if (!_vehicle.GetID().isEmpty())
    {
        return QColor(Qt::blue);
    }
    else if (_toilet)
    {
        return QColor(Qt::cyan);
    }
    else if (!_itemGroup.GetID().isEmpty() || !_items.isEmpty())
    {
        return QColor(Qt::green);
    }
    else if (!_monsterGroup.GetID().isEmpty() || !_monster.isEmpty())
    {
        return QColor(Qt::red);
    }
    else if (_furniture != "f_null")
    {
        return Features::GetFurniture(_furniture).GetBackground();
    }
    else if (_trap != "tr_null")
    {
        return Features::GetTrap(_trap).GetBackground();
    }
    return Features::GetTerrain(_terrain).GetBackground();
}

void Tile::SetTerrain(QString terrain)
{
    _terrain = terrain;
    if (Features::GetTerrain(terrain).HasFlag("NO_FURNITURE"))
    {
        _furniture = null_furniture.GetID();
    }
    if (Features::GetTerrain(terrain).HasFlag("NO_TRAPS"))
    {
        _trap = null_trap.GetID();
    }
    if (Features::GetTerrain(terrain).HasFlag("NO_MONSTERS"))
    {
        _monster = "";
        _monsterGroup = null_monster_group;
    }
    if (Features::GetTerrain(terrain).HasFlag("NOITEM") ||
        Features::GetTerrain(terrain).HasFlag("DESTROY_ITEM"))
    {
        _items.clear();
        _itemGroup = null_item_group;
    }
    if (Features::GetTerrain(terrain).HasFlag("FLAT") ||
        Features::GetTerrain(terrain).HasFlag("TINY"))
    {
        _vehicle = null_vehicle;
    }
}

void Tile::SetFurniture(QString furniture)
{
    if (Features::GetTerrain(_terrain).HasFlag("NO_FURNITURE"))
    {
        return;
    }
    _furniture = furniture;
    _trap = null_trap.GetID();

    if (Features::GetFurniture(furniture).HasFlag("NO_MONSTERS"))
    {
        _monster = "";
        _monsterGroup = null_monster_group;
    }
    if (Features::GetFurniture(furniture).HasFlag("NOITEM") ||
        Features::GetFurniture(furniture).HasFlag("DESTROY_ITEM"))
    {
        _items.clear();
        _itemGroup = null_item_group;
    }
    if (Features::GetFurniture(furniture).HasFlag("FLAT") ||
        Features::GetFurniture(furniture).HasFlag("TINY"))
    {
        _vehicle = null_vehicle;
    }
}

void Tile::SetTrap(QString trap)
{
    if (Features::GetTerrain(_terrain).HasFlag("NO_TRAPS") ||
        _furniture != null_furniture.GetID())
    {
        return;
    }
    _trap = trap;

    if (Features::GetTrap(trap).HasFlag("NO_MONSTERS"))
    {
        _monsterGroup = null_monster_group;
        _monster = "";
    }
}

void Tile::AddItem(QString item)
{
    if (Features::GetTerrain(_terrain).HasFlag("NOITEM") ||
        Features::GetTerrain(_terrain).HasFlag("DESTROY_ITEM") ||
        Features::GetFurniture(_furniture).HasFlag("NOITEM") ||
        Features::GetFurniture(_furniture).HasFlag("DESTROY_ITEM"))
    {
        return;
    }
    if (!item.isEmpty())
    {
        _items.append(item);
    }
    else if (item.isEmpty())
    {
        _items.clear();
    }
}

void Tile::SetNPC(QString npc)
{
    if (Features::GetTerrain(_terrain).HasFlag("NO_MONSTERS") ||
        Features::GetFurniture(_furniture).HasFlag("NO_MONSTERS") ||
        Features::GetTrap(_trap).HasFlag("NO_MONSTERS") ||
        !_monster.isEmpty())
    {
        return;
    }
    _npc = npc;
}

void Tile::SetSignage(QString signage)
{
    // this will automatically overwrite whatever furniture is placed here with a sign, must allow furniture
    if (Features::GetTerrain(_terrain).HasFlag("NO_FURNITURE"))
    {
        qDebug() << "Terrain does not allow for signs";
        return;
    }
    // will force out traps if a trap is there, since furniture overrides traps
    if (_trap != null_trap.GetID())
    {
        _trap = null_trap.GetID();
    }
    _signage = signage;
}

void Tile::SetVending(QString vending)
{
    // this will automatically overwrite whatever furniture is placed here with a vending machine, must allow furniture
    if (Features::GetTerrain(_terrain).HasFlag("NO_FURNITURE"))
    {
        qDebug() << "Terrain does not allow for vending machines";
        return;
    }
    // will force out traps if a trap is there, since furniture overrides traps
    if (_trap != null_trap.GetID())
    {
        _trap = null_trap.GetID();
    }
    _vending = vending;
}

void Tile::SetGasPump(GasPump gasPump)
{
    // only erase the terrain on tiles that actually have a gas pump
    if (gasPump.GetFuel() == "" && _gasPump.GetFuel() == "")
    {
        return;
    }
    else if (gasPump.GetFuel() == "" && _gasPump.GetFuel() != "")
    {
        SetTerrain(null_terrain.GetID());
    }
    else if (gasPump.GetFuel() == "diesel")
    {
        SetTerrain("t_diesel_pump");
    }
    else
    {
        SetTerrain("t_gas_pump");
    }
    _gasPump = gasPump;
}

void Tile::SetRubble(Rubble rubble)
{
    _rubble = rubble;
}

bool Tile::IsLineDrawing() const
{
    return Features::GetTerrain(_terrain).HasFlag("AUTO_WALL_SYMBOL");
}

bool Tile::ExportEquivalent(const Tile &other) const
{
    // TODO this will need more logic later
    if (_terrain == other._terrain && _furniture == other._furniture)
    {
        return true;
    }
    return false;
}

bool Tile::operator ==(const Tile & other) const
{
    // TODO this is a dirty dirty hack designed to help the json group tiles better.
    // worth implementing a real == function?
    return ExportEquivalent(other);
}

//Tile & Tile::operator =(const Tile & other)
//{
//    _terrain = other._terrain;
//    _furniture = other._furniture;
//    _trap = other._trap;
//    _items = other._items;
//    _itemGroup = other._itemGroup;
//    _monster = other._monster;
//    _monsterGroup = other._monsterGroup;
//    _vehicle = other._vehicle;
//    _toilet = other._toilet;
//    _npc = other._npc;
//    _vending = other._vending;
//    _gasPump = other._gasPump;
//    _signage = other._signage;
//    _radiation = other._radiation;

//    return *this;
//}

void Tile::DumpTileData()
{
    qDebug() << "Terrain:" << _terrain;
    qDebug() << "Furniture:" << _furniture;
    qDebug() << "Trap" << _trap;
    qDebug() << "Monster Group:" << _monsterGroup.GetID();
    qDebug() << "Monster:" << _monster;
    qDebug() << "Item Group:" << _itemGroup.GetID();
    qDebug() << "First Item:" << _items.at(0);
    qDebug() << "Vehicle:" << _vehicle.GetID();
    qDebug() << "NPC:" << _npc;
    qDebug() << "Signage:" << _signage;
    qDebug() << "Radiation:" << _radiation;
}

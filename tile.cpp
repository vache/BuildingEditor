#include "tile.h"
#include "features.h"
#include <QDebug>

Tile::Tile() : _terrain("t_null"), _furniture("f_null"), _trap("tr_null"), _monsterGroup("")
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
        if (t.HasFlag("WALL") || t.HasFlag("AUTO_WALL_SYMBOL"))
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
    if (_furniture != "f_null")
    {
        return Features::GetFurniture(_furniture).GetBackground();
    }
    else if (_trap != "tr_null")
    {
        return Features::GetTrap(_trap).GetBackground();
    }
    return Features::GetTerrain(_terrain).GetBackground();
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
    return ExportEquivalent(other);
}

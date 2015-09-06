#include "tile.h"
#include "features.h"
#include <QDebug>

Tile::Tile()
{
    _terrain = "t_null";
    _furniture = "f_null";
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
        Furniture f = Features::GetFeature(_furniture, Furn).value<Furniture>();
        preferredChars.append(f.GetSymbol());
        preferredChars.append(temp[0]);
        preferredChars.append(temp[0].toUpper());
    }
//    else if ("_trap" != "tr_null") // TODO obviously
//    {

//    }
    else
    {
        temp = _terrain;
        temp.remove("t_");
        Terrain t = Features::GetFeature(_terrain, Ter).value<Terrain>();
        if (t.HasFlag("WALL") || t.HasFlag("AUTO_WALL_SYMBOL"))
        {
            preferredChars.append('|');
            preferredChars.append('-');
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
    return GetTerrainChar();
}

QChar Tile::GetTerrainChar() const
{
    return Features::GetFeature(_terrain, Ter).value<Terrain>().GetSymbol();
}

QChar Tile::GetFurnitureChar() const
{
    return Features::GetFeature(_furniture, Furn).value<Furniture>().GetSymbol();
}

QColor Tile::GetForegroundColor() const
{
    if (_furniture != "f_null")
    {
        return Features::GetFeature(_furniture, Furn).value<Furniture>().GetForeground();
    }
    return Features::GetFeature(_terrain, Ter).value<Terrain>().GetForeground();
}

QColor Tile::GetBackgroundColor() const
{
    if (_furniture != "f_null")
    {
        return Features::GetFeature(_furniture, Furn).value<Furniture>().GetBackground();
    }
    return Features::GetFeature(_terrain, Ter).value<Terrain>().GetBackground();
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

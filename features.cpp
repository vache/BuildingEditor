#include "features.h"

#include <QDebug>

Features::Features()
{
}

// TODO: tons of duplication here, simplify?

QMap<QString, Terrain> Features::_terrains = QMap<QString, Terrain>();
QMap<QString, Furniture> Features::_furnitures = QMap<QString, Furniture>();
QMap<QString, Trap> Features::_traps = QMap<QString, Trap>();
QMap<QString, MonsterGroup> Features::_monsterGroups = QMap<QString, MonsterGroup>();
QSet<QString> Features::_modded = QSet<QString>();
QMap<QString, QString> Features::_belongsToMod = QMap<QString, QString>();

void Features::AddTerrain(QString terrainID, Terrain t, QString mod)
{
    _terrains.insert(terrainID, t);
    if (mod != "")
    {
        _belongsToMod[terrainID] = mod;
    }
}

void Features::AddFurniture(QString furnitureID, Furniture f, QString mod)
{
    _furnitures.insert(furnitureID, f);
    if (mod != "")
    {
        _belongsToMod[furnitureID] = mod;
    }
}

void Features::AddTrap(QString trapID, Trap tr, QString mod)
{
    _traps.insert(trapID, tr);
    if (mod != "")
    {
        _belongsToMod[trapID] = mod;
    }
}

void Features::AddMonsterGroup(QString monGroupID, MonsterGroup mg, QString mod)
{
    _monsterGroups.insert(monGroupID, mg);
    if (mod != "")
    {
        _belongsToMod[monGroupID] = mod;
    }
}

QVariant Features::GetFeature(QString featureID, Feature featureType)
{
    switch (featureType)
    {
    case F_Terrain:
        return QVariant::fromValue(_terrains[featureID]);
    case F_Furniture:
        return QVariant::fromValue(_furnitures[featureID]);
    case F_Trap:
        return QVariant::fromValue(_traps[featureID]);
    default:
        return QVariant();
    }
}

Terrain Features::GetTerrain(QString terrainID)
{
    if (_terrains.contains(terrainID))
    {
        return _terrains[terrainID];
    }
    return Terrain();
}

Furniture Features::GetFurniture(QString furnitureID)
{
    if (_furnitures.contains(furnitureID))
    {
        return _furnitures[furnitureID];
    }
    return Furniture();
}

Trap Features::GetTrap(QString trapID)
{
    if (_traps.contains(trapID))
    {
        return _traps[trapID];
    }
    return Trap();
}

MonsterGroup Features::GetMonsterGroup(QString monsterGroupID)
{
    if (_monsterGroups.contains(monsterGroupID))
    {
        return _monsterGroups[monsterGroupID];
    }
    return MonsterGroup("");
}


bool Features::IsModded(QString id)
{
    return Features::_modded.contains(id);
}

QString Features::BelongsToMod(QString id)
{
    return Features::_belongsToMod[id];
}

QStringList Features::ModList()
{
    foreach(QString key, Features::_belongsToMod.keys())
    {
        qDebug() << key << "belongs to mod" << Features::_belongsToMod[key];
    }
    // the double conversion removes non-unique values
    return Features::_belongsToMod.values().toSet().toList();
}

QString Features::TypeName(Feature f)
{
    switch (f)
    {
    case F_Terrain:
        return "terrain";
    case F_Furniture:
        return "furniture";
    case F_Trap:
        return "trap";
    case F_MonsterGroup:
        return "monster group";
    case F_Item:
        return "item";
    case F_Monster:
        return "monster";
    case F_ItemGroup:
        return "item group";
    case F_Vehicle:
        return "vehicle";
    case F_Toilet:
        return "toilet";
    case F_NPC:
        return "npc";
    case F_Vending:
        return "vending";
    case F_Sign:
        return "sign";
    case F_Radiation:
        return "radiation";
    case F_GasPump:
        return "gas pump";
    case F_Rubble:
        return "rubble";
    case F_Field:
        return "field";
    default:
        return "";
    }
}

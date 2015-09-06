#include "features.h"

#include <QDebug>

Features::Features()
{
}

QMap<QString, Terrain> Features::_terrains = QMap<QString, Terrain>();
QMap<QString, Furniture> Features::_furnitures = QMap<QString, Furniture>();
QSet<QString> Features::_modded = QSet<QString>();
QMap<QString, QString> Features::_belongsToMod = QMap<QString, QString>();

void Features::AddTerrain(QString terrainID, Terrain t, QString mod)
{
    Features::_terrains.insert(terrainID, t);
    if (mod != "")
    {
        Features::_belongsToMod[terrainID] = mod;
    }
}

void Features::AddFurniture(QString furnitureID, Furniture f, QString mod)
{
    Features::_furnitures.insert(furnitureID, f);
    if (mod != "")
    {
        Features::_belongsToMod[furnitureID] = mod;
    }
}

QVariant Features::GetFeature(QString featureID, Feature featureType)
{
    switch (featureType)
    {
    case Ter:
        return QVariant::fromValue(Features::_terrains[featureID]);
    case Furn:
        return QVariant::fromValue(Features::_furnitures[featureID]);
    default:
        return QVariant();
    }
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

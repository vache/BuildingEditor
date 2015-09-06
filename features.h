#ifndef FEATURES_H
#define FEATURES_H

#include <QMap>
#include <QVariant>
#include "furniture.h"
#include "terrain.h"
#include "buildingmodel.h"

enum Feature { Ter = TerrainRole, Furn = FurnitureRole };
Q_DECLARE_METATYPE(Feature)

class Features
{
public:
    static void AddTerrain(QString terrainID, Terrain t, QString mod);
    static void AddFurniture(QString furnitureID, Furniture f, QString mod);
    static QVariant GetFeature(QString featureID, Feature featureType);
    static bool IsModded(QString id);
    static QString BelongsToMod(QString id);
    static QStringList ModList();

private:
    static QMap<QString, Terrain> _terrains;
    static QMap<QString, Furniture> _furnitures;
    static QMap<QString, QString> _belongsToMod;
    static QSet<QString> _modded;

    Features();
};

#endif // FEATURES_H

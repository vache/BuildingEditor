#ifndef FEATURES_H
#define FEATURES_H

#include <QMap>
#include <QVariant>
#include "drawableitem.h"
#include "buildingmodel.h"

//TODO im tired of this thing, its a duplicate of the custom roles.  get rid of it.
enum Feature { F_Terrain = TerrainRole, F_Furniture = FurnitureRole, F_Trap = TrapRole,
               F_MonsterGroup = MonsterGroupRole, F_Item = ItemRole, F_Monster = MonsterRole,
               F_ItemGroup = ItemGroupRole, F_Vehicle = VehicleRole, F_Toilet = ToiletRole,
               F_NPC = NpcRole, F_Vending = VendingRole, F_Sign = SignRole,
               F_Radiation = RadiationRole };
Q_DECLARE_METATYPE(Feature)

class Features
{
public:
    static void AddTerrain(QString terrainID, Terrain t, QString mod);
    static void AddFurniture(QString furnitureID, Furniture f, QString mod);
    static void AddTrap(QString trapID, Trap tr, QString mod);
    static void AddMonsterGroup(QString monGroupID, MonsterGroup mg, QString mod);

    static QVariant GetFeature(QString featureID, Feature featureType);

    static Terrain GetTerrain(QString terrainID);
    static Furniture GetFurniture(QString furnitureID);
    static Trap GetTrap(QString trapID);
    static MonsterGroup GetMonsterGroup(QString monsterGroupID);

    static bool IsModded(QString id);
    static QString BelongsToMod(QString id);
    static QStringList ModList();

private:
    static QMap<QString, Terrain> _terrains;
    static QMap<QString, Furniture> _furnitures;
    static QMap<QString, Trap> _traps;
    static QMap<QString, MonsterGroup> _monsterGroups;

    static QMap<QString, QString> _belongsToMod;
    static QSet<QString> _modded;

    Features();
};

#endif // FEATURES_H

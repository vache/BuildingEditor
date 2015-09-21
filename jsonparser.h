#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include <QObject>
#include <QString>

//#include "furniture.h"
//#include "terrain.h"
//#include "trap.h"
#include "drawableitem.h"
#include "monstergroup.h"
#include "itemgroup.h"
#include "vehicle.h"

/*
 * This class pulls data needed to make a mapgen file from the game's relevant json files
 */

class JsonParser : public QObject
{
Q_OBJECT
public:
    JsonParser();
    void Parse(QString directory);

private:
    void ParseDrawableItem(QJsonObject &object);
    void ParseItemGroup(QJsonObject &object);
    void ParseItem(QJsonObject &object);
    void ParseMonsterGroup(QJsonObject &object);
    void ParseMonster(QJsonObject &object);
    void ParseVehicle(QJsonObject &object);
    void ParseVehicleGroup(QJsonObject &object);
    void ParseNPC(QJsonObject& object);

    void ProcessObject(QJsonObject& object);

    QString _currentMod;

signals:
    void ParsingStarted();
    void ParsingFinished();

    void ParsedTerrain(Terrain, QString);
    void ParsedFurniture(Furniture, QString);
    void ParsedTrap(Trap, QString);

    void ParsedItem(QString, QString, QChar, QString);
    void ParsedItemGroup(ItemGroup, QString);
    void ParsedMonster(QString, QString, QChar, QString);
    void ParsedMonsterGroup(MonsterGroup, QString);

    void ParsedVehicle(Vehicle, QString);
    void ParsedNPC(QString, QString, QString, QString, QString);
};

#endif // JSONPARSER_H

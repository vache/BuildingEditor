#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include <QObject>
#include <QString>

#include "furniture.h"
#include "terrain.h"
#include "trap.h"

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
    void ParseTerrain(QJsonObject &object);
    void ParseFurniture(QJsonObject &object);
    void ParseTrap(QJsonObject &object);
    void ParseItemGroup(QJsonObject &object);
    void ParseItem(QJsonObject &object);
    void ParseMonsterGroup(QJsonObject &object);
    void ParseMonster(QJsonObject &object);
    void ParseVehicle(QJsonObject &object);
    void ParseVehicleGroup(QJsonObject &object);

    void ProcessObject(QJsonObject& object);

    QString _currentMod;

signals:
    void ParsingStarted();
    void ParsingFinished();

    void ParsedTerrain(Terrain, QString);
    void ParsedFurniture(Furniture, QString);
    void ParsedTrap(Trap, QString);
};

#endif // JSONPARSER_H

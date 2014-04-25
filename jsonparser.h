#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "furniture.h"
#include "terrain.h"
#include "trap.h"

class JsonParser
{
public:
    JsonParser();

private:
    void Parse();
    void ParseTerrain();
    void ParseFurniture();
    void ParseTrap();
    void ParseTheRest();

signals:

};

#endif // JSONPARSER_H

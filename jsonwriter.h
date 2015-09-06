#ifndef JSONWRITER_H
#define JSONWRITER_H

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "overmapterrain.h"
#include "buildingmodel.h"

/*
 * This class writes the created building to a json file in a game readable format
 */

class JsonWriter
{
public:
    JsonWriter();
    void Write(BuildingModel* model);
    void WriteOMT(OvermapTerrain t);
};

#endif // JSONWRITER_H

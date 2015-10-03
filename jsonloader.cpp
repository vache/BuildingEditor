#include "jsonloader.h"
#include <QFile>
#include <QDebug>

JsonLoader::JsonLoader(QObject *parent) : QObject(parent)
{

}

void JsonLoader::Load(QString filename)
{
    QFile jsonFile(filename);
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QJsonParseError jsonError;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonFile.readAll(), &jsonError);

    if (jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << jsonError.errorString();
        return;
    }

    if (jsonDoc.isEmpty() || jsonDoc.isNull())
    {
        qDebug() << "Empty or Null Json Doc";
        return;
    }

    QJsonObject object;
    if (jsonDoc.isArray())
    {
        QJsonArray array = jsonDoc.array();

        for (QJsonArray::const_iterator it = array.constBegin(); it != array.constEnd(); it++)
        {
            if ((*it).isObject())
            {
                object = (*it).toObject();
                ProcessObject(object);
            }
        }
    }
    else if (jsonDoc.isObject())
    {
        object = jsonDoc.object();
        ProcessObject(object);
    }
    else
    {
        qDebug() << "jsonDoc is not object or array";
    }
}

void JsonLoader::ProcessObject(QJsonObject &object)
{
    if (object.contains("type"))
    {
        QString type = object.value("type").toString();
        if (type == "overmap_special")
        {
            ParseSpecial(object);
        }
        else if (type == "mapgen")
        {
            ParseMapgen(object);
        }
        else if (type == "overmap_terrain")
        {
            ParseOvermapTerrain(object);
        }
    }
}

void JsonLoader::ParseSpecial(QJsonObject &object)
{
    Q_UNUSED(object);
}

void JsonLoader::ParseMapgen(QJsonObject &object)
{
    if (object.value("method").toString() != "json" || !object.contains("object"))
    {
        return;
    }

    QJsonObject mapgenObject;
    mapgenObject = object.value("object").toObject();

    QString fillID = mapgenObject.value("fill_ter").toString("t_null");

    QHash<QChar, QString> terrainMappings;
    QJsonObject terrainObject;
    terrainObject = mapgenObject.value("terrain").toObject();
    foreach (QString key, terrainObject.keys())
    {
        qDebug() << key << terrainObject[key].toString();
        if (terrainObject[key].toString() != "t_null")
        {
            terrainMappings[key[0]] = terrainObject[key].toString();
        }
        else
        {
            terrainMappings[key[0]] = fillID;
        }
    }

    QHash<QChar, QString> furnitureMappings;
    QJsonObject furnitureObject;
    furnitureObject = mapgenObject.value("furniture").toObject();
    foreach (QString key, furnitureObject.keys())
    {
        qDebug() << key << furnitureObject[key].toString();
        furnitureMappings[key[0]] = furnitureObject[key].toString();
    }

    QJsonArray rowsArray = mapgenObject.value("rows").toArray();
    if (rowsArray.count() != OVERMAP_TERRAIN_WIDTH)
    {
        qDebug() << "Sanity check failed, \"rows\" does not have" << OVERMAP_TERRAIN_WIDTH << "rows";
        return;
    }

    OvermapTerrain* omt = new OvermapTerrain(true);
    for (int row = 0; row < rowsArray.count(); row++)
    {
        QString rowString = rowsArray[row].toString();
        qDebug() << rowString;
        if (rowString.length() != OVERMAP_TERRAIN_WIDTH)
        {
            qDebug() << "Sanity check failed, row" << row << "is not" << OVERMAP_TERRAIN_WIDTH << "characters";
            return;
        }
        for (int col = 0; col < rowString.length(); col++)
        {
            Tile t;
            t.SetTerrain(terrainMappings[rowString[col]]);
            if (furnitureMappings.contains(rowString[col]))
            {
                t.SetFurniture(furnitureMappings[rowString[col]]);
            }

            omt->SetTile(Tripoint(col, row, 0), t);
        }
    }

    if (mapgenObject.contains("place_traps"))
    {
        QJsonArray trapArray = mapgenObject["place_traps"].toArray();
        for (int i = 0; i < trapArray.count(); i++)
        {
            QJsonObject trapObject = trapArray[i].toObject();

            int x = trapObject["x"].toInt();
            int y = trapObject["y"].toInt();
            QString trap = trapObject["trap"].toString();

            omt->GetTile(Tripoint(x, y, 0)).SetTrap(trap);
        }
    }

    if (mapgenObject.contains("place_items"))
    {
        QJsonArray itemsArray = mapgenObject["place_items"].toArray();
        for (int i = 0; i < itemsArray.count(); i++)
        {
            QJsonObject itemsObject = itemsArray[i].toObject();

            QPair<int, int> x;
            QPair<int, int> y;
            if (itemsObject["x"].isArray())
            {
                x.first = itemsObject["x"].toArray()[0].toInt();
                x.second = itemsObject["x"].toArray()[1].toInt();
            }
            else
            {
                x.first = itemsObject["x"].toInt();
                x.second = itemsObject["x"].toInt();
            }

            if (itemsObject["y"].isArray())
            {
                y.first = itemsObject["y"].toArray()[0].toInt();
                y.second = itemsObject["y"].toArray()[1].toInt();
            }
            else
            {
                y.first = itemsObject["y"].toInt();
                y.second = itemsObject["y"].toInt();
            }
            QString group = itemsObject["item"].toString();
            int chance = itemsObject["chance"].toInt();

            for (int xx = x.first; xx <= x.second; xx++)
            {
                for (int yy = y.first; yy <= y.second; yy++)
                {
                    omt->GetTile(Tripoint(xx, yy, 0)).SetItemGroup(ItemGroup(group, chance));
                }
            }
        }
    }

    emit OmtLoaded(omt);
}

void JsonLoader::ParseOvermapTerrain(QJsonObject &object)
{
    Q_UNUSED(object);
}

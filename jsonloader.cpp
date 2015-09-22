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

    QJsonArray rowsArray = mapgenObject.value("rows").toArray();
    QString rows = "";
    for (QJsonArray::const_iterator it = rowsArray.constBegin(); it != rowsArray.constEnd(); it++)
    {
        rows.append((*it).toString());
        qDebug() << (*it).toString();
    }

    QJsonObject terrainObject;
    terrainObject = mapgenObject.value("terrain").toObject();
    foreach (QString key, terrainObject.keys())
    {
        qDebug() << key << terrainObject[key].toString();
    }

    QJsonObject furnitureObject;
    furnitureObject = mapgenObject.value("furniture").toObject();
    foreach (QString key, furnitureObject.keys())
    {
        qDebug() << key << furnitureObject[key].toString();
    }

}

void JsonLoader::ParseOvermapTerrain(QJsonObject &object)
{
    Q_UNUSED(object);
}

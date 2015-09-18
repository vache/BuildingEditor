#include "jsonparser.h"

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QByteArray>

#include <QDebug>

/*
Rough workflow:
Read all json files in <cataroot>/data/json
If "type" == terrain -> ParseTerrain
-- "type" == furniture -> ParseFurniture
-- "type" == trap -> ParseTrap
-- "type" == (item, item_group, monster, monster group) -> ParseTheRest()
*/

JsonParser::JsonParser()
{
}

void JsonParser::Parse(QString directory)
{
    emit ParsingStarted();
    QDir dir(directory);

    foreach (QFileInfo subdir, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        int index = subdir.absoluteFilePath().indexOf("mods");
        if (index != -1)
        {
            index += 5;
            int endex = subdir.absoluteFilePath().indexOf("/");
            _currentMod = subdir.absoluteFilePath().mid(index, endex - index);
        }
        else
        {
            _currentMod = "";
        }
        Parse(subdir.absoluteFilePath());
    }

    foreach (QFileInfo jsonFileInfo, dir.entryInfoList(QStringList("*.json"), QDir::Files))
    {
        qDebug() << "Parsing Filename: " << jsonFileInfo.absoluteFilePath();

        QFile file(jsonFileInfo.absoluteFilePath());
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();

        QJsonObject object;

        if (doc.isArray())
        {
            QJsonArray array = doc.array();

            for (QJsonArray::const_iterator it = array.constBegin(); it != array.constEnd(); it++)
            {
                if ((*it).isObject())
                {
                    object = (*it).toObject();
                    ProcessObject(object);
                }
            }
        }
        else if (doc.isObject())
        {
            object = doc.object();
            ProcessObject(object);
        }
    }
    emit ParsingFinished();
}

void JsonParser::ParseDrawableItem(QJsonObject &object)
{
    QString description = object.value("name").toString("invalid name");
    QString id = object.value("id").toString("invalid_id");

    if (description == "")
    {
        description = id;
    }

    QChar symbol = object.value("symbol").toString("#").at(0);
    // line drawing terrain (walls)
    if (object.value("symbol").toString().contains("LINE"))
    {
        symbol = 0x253C;
    }
    nc_color color = nc_color();
    if (object.contains("color"))
    {
        color = color_from_string(object.value("color").toString());
    }
    else if (object.contains("bgcolor"))
    {
        color = bgcolor_from_string(object.value("bgcolor").toString());
    }
    QSet<QString> flags;

    if (object.contains("flags"))
    {
        foreach (QJsonValue v, object.value("flags").toArray())
        {
            flags.insert(v.toString());
        }
    }

    if (object.value("type").toString() == "terrain")
    {
        if (object["move_cost"].toInt() == 0)
        {
            flags.insert("NO_MONSTERS");
            flags.insert("NO_TRAPS");
            flags.insert("NO_FURNITURE");
        }

        Terrain t(id, description, symbol, color, flags);

        qDebug() << "Terrain" << id << "belongs to" << _currentMod;

        emit ParsedTerrain(t, _currentMod);
    }
    else if (object.value("type").toString() == "furniture")
    {
        flags.insert("NO_TRAPS");
        if (object["move_cost_mod"].toInt() == -1)
        {
            flags.insert("NO_MONSTERS");
        }

        Furniture f(id, description, symbol, color, flags);

        qDebug() << "Furniture" << id << "belongs to" << _currentMod;

        emit ParsedFurniture(f, _currentMod);
    }
    else if(object.value("type").toString() == "trap")
    {
        flags.insert("NO_FURNITURE");
        if (object.value("benign").toBool(false) == false)
        {
            flags.insert("NO_MONSTERS");
        }

        Trap tr(id, description, symbol, color, flags);

        qDebug() << "Trap" << id << "belongs to" << _currentMod;

        emit ParsedTrap(tr, _currentMod);
    }
}

// Needs id, name, symbol, color, certain flags (NOITEM?), move cost?
void JsonParser::ParseTerrain(QJsonObject &object)
{
    QString description = object.value("name").toString("invalid name");
    QString id = object.value("id").toString("invalid_id");
    QChar symbol = object.value("symbol").toString("#").at(0);
    // line drawing terrain (walls)
    if (object.value("symbol").toString().contains("LINE"))
    {
        symbol = 0x253C;
    }
    nc_color color = nc_color();
    if (object.contains("color"))
    {
        color = color_from_string(object.value("color").toString());
    }
    else if (object.contains("bgcolor"))
    {
        color = bgcolor_from_string(object.value("bgcolor").toString());
    }
    QSet<QString> flags;

    if (object["move_cost"].toInt() == 0)
    {
        flags.insert("NO_MONSTERS");
        flags.insert("NO_TRAPS");
        flags.insert("NO_FURNITURE");
    }

    if (object.contains("flags"))
    {
        foreach (QJsonValue v, object.value("flags").toArray())
        {
            flags.insert(v.toString());
        }
    }

    Terrain t(id, description, symbol, color, flags);

    qDebug() << "Terrain" << id << "belongs to" << _currentMod;

    emit ParsedTerrain(t, _currentMod);
}

void JsonParser::ParseFurniture(QJsonObject &object)
{
    QString description = object.value("name").toString("invalid name");
    QString id = object.value("id").toString("invalid_id");
    QChar symbol = object.value("symbol").toString("#").at(0);
    nc_color color = nc_color();
    if (object.contains("color"))
    {
        color = color_from_string(object.value("color").toString());
    }
    else if (object.contains("bgcolor"))
    {
        color = bgcolor_from_string(object.value("bgcolor").toString());
    }
    QSet<QString> flags;

    if (object["move_cost_mod"].toInt() == -1)
    {
        flags.insert("NO_TRAPS");
        flags.insert("NO_MONSTERS");
    }

    if (object.contains("flags"))
    {
        foreach (QJsonValue v, object.value("flags").toArray())
        {
            flags.insert(v.toString());
        }
    }

    Furniture f(id, description, symbol, color, flags);

    qDebug() << "Furniture" << id << "belongs to" << _currentMod;

    emit ParsedFurniture(f, _currentMod);
}

void JsonParser::ParseTrap(QJsonObject &object)
{
    //May be removed at any time
    Q_UNUSED(object)
}

void JsonParser::ParseItemGroup(QJsonObject &object)
{
    QString id = object.value("id").toString("invalid_id");
    ItemGroup ig(id);

    emit ParsedItemGroup(ig, _currentMod);
}

void JsonParser::ParseItem(QJsonObject &object)
{
    QString name = object.value("name").toString("invalid name");
    QString id = object.value("id").toString("invalid_id");
    QChar symbol = object.value("symbol").toString("?")[0];

    emit ParsedItem(name, id, symbol, _currentMod);
}

void JsonParser::ParseMonsterGroup(QJsonObject &object)
{
    QString name = object.value("name").toString("invalid group");
    MonsterGroup mg(name);

    emit ParsedMonsterGroup(mg, _currentMod);
}

void JsonParser::ParseMonster(QJsonObject &object)
{
    QString name = object.value("name").toString("invalid name");
    QString id = object.value("id").toString("invalid_id");
    QChar symbol = object.value("symbol").toString("?")[0];

    emit ParsedMonster(name, id, symbol, _currentMod);
}

void JsonParser::ParseVehicle(QJsonObject &object)
{
    QString name = object.value("name").toString("invalid name");
    QString id = object.value("id").toString("invalid_id");
    Vehicle vehicle(id, name);

    emit ParsedVehicle(vehicle, _currentMod);
}

// json spawning from vehicle groups is unimplemented currently
void JsonParser::ParseVehicleGroup(QJsonObject &object)
{
    Q_UNUSED(object)
}

// item types: AMMO, GENERIC, GUN, ARMOR, BIONIC_ITEM, BOOK, COMESTIBLE, CONTAINER, TOOL, GUNMOD, TOOL_ARMOR, VAR_VEH_PART, INSTRUMENT
void JsonParser::JsonParser::ProcessObject(QJsonObject &object)
{
    static QStringList itemTypes = {"AMMO", "GENERIC", "GUN", "ARMOR", "BIONIC_ITEM", "BOOK",
                                    "COMESTIBLE", "CONTAINER", "TOOL", "GUNMOD", "TOOL_ARMOR",
                                    "VAR_VEH_PART", "INSTRUMENT"};
    static QStringList drawableTypes = { "terrain", "furniture", "trap" };

    if (object.contains("type"))
    {
        QString type = object.value("type").toString("unknown");

//        if (type == "terrain")
//        {
//            ParseTerrain(object);
//        }
//        else if (type == "furniture")
//        {
//            ParseFurniture(object);
//        }
//        else if (type == "trap")
//        {
//            ParseTrap(object);
//        }
        if (drawableTypes.contains(type))
        {
            ParseDrawableItem(object);
        }
        else if (type == "item_group")
        {
            ParseItemGroup(object);
        }
        else if (type == "monstergroup")
        {
            ParseMonsterGroup(object);
        }
        else if (type == "MONSTER")
        {
            ParseMonster(object);
        }
        else if (itemTypes.contains(type))
        {
            ParseItem(object);
        }
        else if (type == "vehicle")
        {
            ParseVehicle(object);
        }
        else if (type == "vehicle_group")
        {
            ParseVehicleGroup(object);
        }
    }
}

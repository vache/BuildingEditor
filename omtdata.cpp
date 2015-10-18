#include "omtdata.h"
#include <QJsonArray>

OMTData::OMTData() : _readOnly(false), _id(""), _name(""), _rotate(true),
    _knownUp(false), _knownDown(false), _color("black"), _seeCost(0), _extras("none"), _sidewalk(true),
    _allowRoad(false)
{
    _symbols.append(32);
}

OMTData OMTData::FromJson(QJsonObject &object)
{
    OMTData data;

    data.SetReadOnly();
    data.SetID(object.value("id").toString());
    data.SetName(object.value("name").toString());
    data.SetRotate(object.value("rotate").toBool(false));
    data.SetKnownUp(object.value("known_up").toBool(false));
    data.SetKnownDown(object.value("known_down").toBool(false));
    data.SetColor(object.value("color").toString());
    data.SetSeeCost(object.value("see_cost").toInt(0));
    data.SetExtras(object.value("extras").toString());
    data.SetSidewalk(object.value("sidewalk").toBool(false));
    data.SetAllowRoads(object.value("allow_road").toBool(false));
    QList<int> symbols;
    if (object.value("sym").isArray())
    {
        QJsonArray jsonSymbols = object.value("sym").toArray();
        foreach (QJsonValue symbol, jsonSymbols)
        {
            symbols.append(symbol.toInt());
        }
    }
    else
    {
        symbols.append(object.value("sym").toInt());
    }
    data.SetSymbols(symbols);

    return data;
}

QJsonObject OMTData::ToJson()
{
    QJsonObject out;

    out["type"] = "overmap_terrain";
    out["id"] = _id;
    out["name"] = _name;
    out["rotate"] = _rotate;
    if (_symbols.count() == 1)
    {
        out["sym"] = _symbols[0];
    }
    else
    {
        QJsonArray symArray;
        symArray.append(_symbols[0]);
        symArray.append(_symbols[1]);
        symArray.append(_symbols[2]);
        symArray.append(_symbols[3]);
        out["sym"] = symArray;
    }
    out["known_up"] = _knownUp;
    out["known_down"] = _knownDown;
    out["color"] = _color;
    out["see_cost"] = _seeCost;
    out["extras"] = _extras;
    out["sidewalk"] = _sidewalk;
    out["allow_road"] = _allowRoad;

    return out;
}

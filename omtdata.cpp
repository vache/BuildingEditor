#include "omtdata.h"

OMTData::OMTData() : _readOnly(false), _id(""), _name(""), _rotate(true), _symbols(QList<QChar>()),
    _knownUp(false), _knownDown(false), _color("black"), _seeCost(0), _extras("none"), _sidewalk(true),
    _allowRoad(false)
{

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

    return data;
}

QJsonObject OMTData::ToJson()
{
    QJsonObject out;

    out["type"] = "overmap_terrain";
    out["id"] = _id;
    out["name"] = _name;
    out["rotate"] = _rotate;
    out["sym"] = _symbols[0].unicode();
    out["known_up"] = _knownUp;
    out["known_down"] = _knownDown;
    out["color"] = _color;
    out["see_cost"] = _seeCost;
    out["extras"] = _extras;
    out["sidewalk"] = _sidewalk;
    out["allow_road"] = _allowRoad;

    return out;
}

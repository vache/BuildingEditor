#include "overmapspecialdata.h"

#include <QJsonArray>

QJsonObject SpecialLayoutEntry::ToJson() const
{
    QJsonObject object;
    object["point"] = location.ToJson();
    object["connect"] = connection;
    object["overmap"] = overmapTerrainID;
    return object;
}

OvermapSpecialData::OvermapSpecialData()
{

}

QJsonObject OvermapSpecialData::ToJson() const
{
    QJsonObject specialObject;

    specialObject["type"] = "overmap_special";
    specialObject["id"] = _id;

    QJsonArray overmaps;
    foreach (SpecialLayoutEntry entry, _layout)
    {
        overmaps.append(entry.ToJson());
    }
    specialObject["overmaps"] = overmaps;

    specialObject["locations"] = QJsonArray::fromStringList(_locations);

    QJsonArray cityDistance;
    cityDistance.append(_minCityDistance);
    cityDistance.append(_maxCityDistance);
    specialObject["city_distance"] = cityDistance;

    QJsonArray occurrences;
    occurrences.append(_minOccurrences);
    occurrences.append(_maxOccurrences);
    specialObject["occurrences"] = occurrences;

    specialObject["rotate"] = _rotate;

    specialObject["flags"] = QJsonArray::fromStringList(_flags);

    return specialObject;
}

OvermapSpecialData OvermapSpecialData::FromJson(QJsonObject &object)
{
    OvermapSpecialData data;
    data.SetID(object.value("id").toString());

    QJsonArray locationArray = object.value("locations").toArray();
    foreach (QJsonValue value, locationArray)
    {
        data.AddLocation(value.toString());
    }

    QJsonArray cityDistanceArray = object.value("city_distance").toArray();
    data.SetMinCityDistance(cityDistanceArray[0].toInt());
    data.SetMaxCityDistance(cityDistanceArray[1].toInt());

    QJsonArray occurrencesArray = object.value("occurrences").toArray();
    data.SetMinOccurrences(occurrencesArray[0].toInt());
    data.SetMaxOccurrences(occurrencesArray[1].toInt());

    QJsonArray flagsArray = object.value("flags").toArray();
    foreach (QJsonValue value, flagsArray)
    {
        data.AddFlag(value.toString());
    }

    data.SetRotate(object.value("rotate").toBool(false));
    data.SetUnique(object.value("unique").toBool(false));

    return data;
}

void OvermapSpecialData::AddLayoutEntry(Tripoint point, QString id, QString connection)
{
    SpecialLayoutEntry entry;
    entry.connection = connection;
    entry.location = point;
    entry.overmapTerrainID = id;
    _layout.append(entry);
}

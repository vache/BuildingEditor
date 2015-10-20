#ifndef OVERMAPSPECIALDATA_H
#define OVERMAPSPECIALDATA_H

#include <QString>
#include <QVector>
#include <QJsonObject>
#include "omtdata.h"
#include "tripoint.h"

struct SpecialLayoutEntry
{
    QString overmapTerrainID;
    QString connection;
    Tripoint location;
    QJsonObject ToJson() const;
};

class OvermapSpecialData
{
public:
    OvermapSpecialData();

    QJsonObject ToJson() const;
    static OvermapSpecialData FromJson(QJsonObject& object);

    inline void SetID(QString id) { _id = id; }
    inline void SetLayout(QVector<SpecialLayoutEntry> layout) { _layout = layout; }
    void AddLayoutEntry(Tripoint point, QString id, QString connection);
    inline void SetLocations(QStringList locations) { _locations = locations; }
    inline void AddLocation(QString location) { _locations.append(location); }
    inline void SetFlags(QStringList flags) { _flags = flags; }
    inline void AddFlag(QString flag) { _flags.append(flag); }
    inline void SetRotate(bool rotate) { _rotate = rotate; }
    inline void SetUnique(bool unique) { _unique = unique; }
    inline void SetMinCityDistance(int minDistance) { _minCityDistance = minDistance; }
    inline void SetMaxCityDistance(int maxDistance) { _maxCityDistance = maxDistance; }
    inline void SetMinOccurrences(int minOccurrences) { _minOccurrences = minOccurrences; }
    inline void SetMaxOccurrences(int maxOccurrences) { _maxOccurrences = maxOccurrences; }
    inline void SetOMTData(QVector<OMTData> data) { _overmapData = data; }

    inline bool HasLocation(QString location) { return _locations.contains(location); }
    inline bool HasFlag(QString flag) { return _flags.contains(flag); }

    inline QString GetID() const { return _id; }
    inline QVector<SpecialLayoutEntry> GetLayout() const { return _layout; }
    inline QStringList GetLocaations() const { return _locations; }
    inline QStringList GetFlags() const { return _flags; }
    inline bool GetRotates() const { return _rotate; }
    inline bool GetUnique() const { return _unique; }
    inline int GetMinCityDistance() const { return _minCityDistance; }
    inline int GetMaxCityDistance() const { return _maxCityDistance; }
    inline int GetMinOccurrences() const { return _minOccurrences; }
    inline int GetMaxOccurrences() const { return _maxOccurrences; }
    inline QVector<OMTData> GetOMTData() const { return _overmapData; }

private:
    // Only used internally
    QVector<OMTData> _overmapData;
    // These all get exported
    QString _id;
    QVector<SpecialLayoutEntry> _layout;
    QStringList _locations;
    QStringList _flags;
    bool _rotate;
    bool _unique;
    int _minCityDistance;
    int _maxCityDistance;
    int _minOccurrences;
    int _maxOccurrences;
};

#endif // OVERMAPSPECIALDATA_H

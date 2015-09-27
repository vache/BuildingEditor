#ifndef OMTDATA_H
#define OMTDATA_H

#include <QString>
#include <QList>
#include <QJsonObject>
#include <QMetaType>
#include "colors.h"

class OMTData
{
public:
    OMTData();

    static OMTData FromJson(QJsonObject & object);
    QJsonObject ToJson();

    bool IsReadOnly() const { return _readOnly; }

    QString GetID() const { return _id; }
    QString GetName() const { return _name; }
    bool GetRotates() const { return _rotate; }
    QList<QChar> GetSymbols() const { return _symbols; }
    bool GetKnownUp() const { return _knownUp; }
    bool GetKnownDown() const { return _knownDown; }
    QString GetColor() const { return _color; }
    int GetSeeCost() const { return _seeCost; }
    QString GetExtras() const { return _extras; }
    bool GetSidewalk() const { return _sidewalk; }
    bool GetAllowedRoad() const { return _allowRoad; }

    void SetID(QString id) { _id = id; }
    void SetName(QString name) { _name = name; }
    void SetRotate(bool rotate) { _rotate = rotate; }

    void SetKnownUp(bool knownUp) { _knownUp = knownUp; }
    void SetKnownDown(bool knownDown) { _knownDown = knownDown; }
    void SetColor(QString color) { _color = color; }
    void SetSeeCost(int seeCost) { _seeCost = seeCost; }
    void SetExtras(QString extras) { _extras = extras; }
    void SetSidewalk(bool sidewalk) { _sidewalk = sidewalk; }
    void SetAllowRoads(bool allowRoad) { _allowRoad = allowRoad; }

private:
    void SetReadOnly() { _readOnly = true; }
    bool _readOnly;

    QString _id;
    QString _name;
    bool _rotate;
    QList<QChar> _symbols;
    bool _knownUp;
    bool _knownDown;
    QString _color;
    int _seeCost;
    QString _extras;
    bool _sidewalk;
    bool _allowRoad;
};

Q_DECLARE_METATYPE(OMTData)

#endif // OMTDATA_H

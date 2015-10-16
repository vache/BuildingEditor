#ifndef OVERMAPSPECIALDATA_H
#define OVERMAPSPECIALDATA_H

#include <QString>
#include <QVector>
#include <QJsonObject>

class OvermapSpecialData
{
public:
    OvermapSpecialData();

    QJsonObject ToJson();
signals:

public slots:

private slots:

private:
    QString _id;
    QVector<bool> _layout;
    bool _rotate;
    bool _unique;
    int _minCityDistance;
    int _maxCityDistance;
    int _minOccurrences;
    int _maxOccurrences;
};

#endif // OVERMAPSPECIALDATA_H

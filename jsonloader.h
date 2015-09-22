#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>

#include "overmapterrain.h"

class JsonLoader : public QObject
{
    Q_OBJECT
public:
    explicit JsonLoader(QObject *parent = 0);

    void Load(QString filename);

signals:
    void OmtLoaded(OvermapTerrain*);
public slots:

private:
    void ProcessObject(QJsonObject& object);
    void ParseSpecial(QJsonObject& object);
    void ParseMapgen(QJsonObject& object);
    void ParseOvermapTerrain(QJsonObject& object);
};

#endif // JSONLOADER_H

#ifndef BUILDINGEDITOR_H
#define BUILDINGEDITOR_H

#include <QMainWindow>
#include <QMap>
#include "buildingmodel.h"
#include "buildingeditorview.h"
#include "terrain.h"
#include "furniture.h"
#include "features.h"

namespace Ui {
class BuildingEditor;
}

class BuildingEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit BuildingEditor(QWidget *parent = 0);
    ~BuildingEditor();

private slots:

    void ZLevelSliderChanged(int value);

    void NewBuilding();
    void NewTerrain(Terrain t, QString mod);
    void NewFurniture(Furniture f, QString mod);

    void Write();


private:
    Ui::BuildingEditor *ui;

    BuildingModel* m;

    QStringList _allIDs;
    QMap<QString, QString> _modIDs;
};

#endif // BUILDINGEDITOR_H

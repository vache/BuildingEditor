#ifndef BUILDINGEDITOR_H
#define BUILDINGEDITOR_H

#include <QMainWindow>
#include <QMap>
#include "buildingmodel.h"
#include "buildingeditorview.h"
//#include "terrain.h"
//#include "furniture.h"
#include "drawableitem.h"
#include "features.h"
#include "itemgroup.h"
#include <QActionGroup>

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
    void NewTrap(Trap tr, QString mod);
    void NewItem(QString name, QString id, QChar symbol, QString mod);
    void NewItemGroup(ItemGroup ig, QString mod);
    void NewMonster(QString name, QString id, QChar symbol, QString mod);
    void NewMonsterGroup(MonsterGroup mg, QString mod);

    void Write();

private:
    Ui::BuildingEditor *ui;

    BuildingModel* m;
    QActionGroup* _tools;

    QStringList _allIDs;
    QMap<QString, QString> _modIDs;

signals:
    void SelectedBox();
};

#endif // BUILDINGEDITOR_H

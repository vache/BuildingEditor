#ifndef BUILDINGEDITOR_H
#define BUILDINGEDITOR_H

#include <QMainWindow>
#include <QMap>
#include "buildingmodel.h"
#include "buildingeditorview.h"
#include "omtdialog.h"
#include "drawableitem.h"
#include "features.h"
#include "itemgroup.h"
#include "vehicle.h"
#include <QActionGroup>
// test...
#include <QListWidgetItem>
#include "searchmodel.h"

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
    void Open();

    void NewTerrain(Terrain t, QString mod);
    void NewFurniture(Furniture f, QString mod);
    void NewTrap(Trap tr, QString mod);
    void NewItem(QString name, QString id, QChar symbol, QString mod);
    void NewItemGroup(ItemGroup ig, QString mod);
    void NewMonster(QString name, QString id, QChar symbol, QString mod);
    void NewMonsterGroup(MonsterGroup mg, QString mod);
    void NewVehicle(Vehicle veh, QString mod);
    void NewNPC(QString id, QString name, QString faction, QString comment, QString mod);

    void Write();

    void SetObjectEditorMode(QListWidgetItem* i);
    void ObjectEditorModified();

    void Search();
    void OnSearchSelect();
    void HideSearchArea();

    void SetCurrentPage(QListWidgetItem* item);

private:
    Ui::BuildingEditor *ui;

    BuildingModel* m;
    SearchModel* _searchModel;
    QActionGroup* _tools;

    QStringList _allIDs;
    QMap<QString, QString> _modIDs;

    QListWidgetItem* _currentItem;

    OMTDialog _omtDialog;

    void SetupFields();

signals:
    void CurrentFeatureChanged(QListWidgetItem*);
};

#endif // BUILDINGEDITOR_H

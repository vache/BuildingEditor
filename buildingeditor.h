#ifndef BUILDINGEDITOR_H
#define BUILDINGEDITOR_H

#include <QMainWindow>
#include "building.h"

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

    void NewBuilding();

private:
    Ui::BuildingEditor *ui;

    Building* _currentBuilding;


};

#endif // BUILDINGEDITOR_H

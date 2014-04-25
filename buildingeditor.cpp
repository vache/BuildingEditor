#include "buildingeditor.h"
#include "ui_buildingeditor.h"

BuildingEditor::BuildingEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BuildingEditor)
{
    ui->setupUi(this);
}

BuildingEditor::~BuildingEditor()
{
    delete ui;
}

void BuildingEditor::NewBuilding()
{
    int dimension = 3;

    if(NULL == _currentBuilding)
    {
        _currentBuilding = new Building(dimension);
    }
    else
    {
        // check for dirty, prompt to save, proceed
    }

    ui->tableView->setModel(_currentBuilding->_model);
}


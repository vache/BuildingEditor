#include "buildingeditor.h"
#include "ui_buildingeditor.h"

#include "jsonparser.h"
#include "jsonwriter.h"

#include <QDebug>

// convert to LINE_XXXX to match cata convention?
enum DirectionalLine { NS = 0, EW, NE, NW, SE, SW, NES, NSW, NEW, ESW, NESW };

BuildingEditor::BuildingEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BuildingEditor), m(NULL)
{
    ui->setupUi(this);

    JsonParser p;

    connect(&p, SIGNAL(ParsedTerrain(Terrain, QString)), this, SLOT(NewTerrain(Terrain, QString)));
    connect(&p, SIGNAL(ParsedFurniture(Furniture, QString)), this, SLOT(NewFurniture(Furniture, QString)));
    connect(ui->zLevelSlider, SIGNAL(valueChanged(int)), this, SLOT(ZLevelSliderChanged(int)));
    connect(ui->terrainWidget, SIGNAL(itemClicked(QListWidgetItem*)), ui->tableView, SLOT(FeatureSelected(QListWidgetItem*)));
    connect(ui->furnitureWidget, SIGNAL(itemClicked(QListWidgetItem*)), ui->tableView, SLOT(FeatureSelected(QListWidgetItem*)));

    p.Parse("c:/code/Cataclysm-DDA/data");

    ui->mainToolBar->addAction("Write", this, SLOT(Write()));

    // TEST CODE
    QList<QChar> test;
    // NS, EW, NE, NW, ES, SW, NES, NSW, NEW, ESW, NESW
    test << 0x2502 << 0x2500 << 0x2514 << 0x2518 << 0x250C << 0x2510 << 0x251C << 0x2524
         << 0x2534 << 0x252C << 0x253C;

    QString blah = "";
    foreach (QChar ch, test)
    {
        blah.append(ch);
    }
    blah.append(test[NESW]);
    ui->statusBar->showMessage(blah);

    bool active[10][10];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (i == 0 && j == 0)
            {
                active[i][j] = true;
            }
            else
            {
                active[i][j] = false;
            }
        }
    }
    m = new BuildingModel(active);

    ui->tableView->setModel(m);

    foreach (QString mod, Features::ModList())
    {
        qDebug() << mod;
    }

    // END TEST CODE
}

BuildingEditor::~BuildingEditor()
{
    delete ui;
}

void BuildingEditor::ZLevelSliderChanged(int value)
{
    ui->zLevelLE->setText(QString::number(value));
}

void BuildingEditor::NewBuilding()
{

//    int dimension = 3;

//    if(NULL == _currentBuilding)
//    {
//        _currentBuilding = new Building(dimension);
//    }
//    else
//    {
//        // check for dirty, prompt to save, proceed
//    }

//    ui->tableView->setModel(_currentBuilding->_model);
}

void BuildingEditor::NewTerrain(Terrain t, QString mod)
{
    Features::AddTerrain(t.GetID(), t, mod);

    QString displayText = QString("%1 - %2").arg(t.GetSymbol()).arg(t.GetDescription());
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->terrainWidget);
    item->setToolTip(t.GetID());
    item->setData(Qt::UserRole, t.GetID());
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(Ter));
}

void BuildingEditor::NewFurniture(Furniture f, QString mod)
{
    Features::AddFurniture(f.GetID(), f, mod);

    QString displayText = QString("%1 - %2").arg(f.GetSymbol()).arg(f.GetDescription());
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->furnitureWidget);
    item->setToolTip(f.GetID());
    item->setData(Qt::UserRole, f.GetID());
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(Furn));
}

void BuildingEditor::Write()
{
    JsonWriter w;
    w.Write(m);
}

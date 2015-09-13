#include "buildingeditor.h"
#include "ui_buildingeditor.h"

#include "jsonparser.h"
#include "jsonwriter.h"

#include <QDebug>

// convert to LINE_XXXX to match cata convention?
enum DirectionalLine { NS = 0, EW, NE, NW, SE, SW, NES, NSW, NEW, ESW, NESW };

BuildingEditor::BuildingEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BuildingEditor), m(NULL), _currentItem(NULL)
{
    ui->setupUi(this);

    JsonParser p;

    connect(&p, SIGNAL(ParsedTerrain(Terrain, QString)), this, SLOT(NewTerrain(Terrain, QString)));
    connect(&p, SIGNAL(ParsedFurniture(Furniture, QString)), this, SLOT(NewFurniture(Furniture, QString)));
    connect(&p, SIGNAL(ParsedTrap(Trap,QString)), this, SLOT(NewTrap(Trap,QString)));
    connect(&p, SIGNAL(ParsedItem(QString,QString,QChar,QString)), this, SLOT(NewItem(QString,QString,QChar,QString)));
    connect(&p, SIGNAL(ParsedMonster(QString,QString,QChar,QString)), this, SLOT(NewMonster(QString,QString,QChar,QString)));
    connect(&p, SIGNAL(ParsedItemGroup(ItemGroup,QString)), this, SLOT(NewItemGroup(ItemGroup,QString)));
    connect(&p, SIGNAL(ParsedMonsterGroup(MonsterGroup,QString)), this, SLOT(NewMonsterGroup(MonsterGroup,QString)));
    connect(&p, SIGNAL(ParsedVehicle(Vehicle,QString)), this, SLOT(NewVehicle(Vehicle,QString)));
    connect(ui->zLevelSlider, SIGNAL(valueChanged(int)), this, SLOT(ZLevelSliderChanged(int)));
    connect(ui->gridBox, SIGNAL(clicked(bool)), ui->tableView, SLOT(setShowGrid(bool)));

    // TODO simplify!
    connect(ui->terrainWidget, SIGNAL(itemClicked(QListWidgetItem*)), ui->tableView, SLOT(FeatureSelected(QListWidgetItem*)));
    connect(ui->furnitureWidget, SIGNAL(itemClicked(QListWidgetItem*)), ui->tableView, SLOT(FeatureSelected(QListWidgetItem*)));
    connect(ui->trapWidget, SIGNAL(itemClicked(QListWidgetItem*)), ui->tableView, SLOT(FeatureSelected(QListWidgetItem*)));
    connect(ui->itemWidget, SIGNAL(itemClicked(QListWidgetItem*)), ui->tableView, SLOT(FeatureSelected(QListWidgetItem*)));
    connect(ui->monsterWidget, SIGNAL(itemClicked(QListWidgetItem*)), ui->tableView, SLOT(FeatureSelected(QListWidgetItem*)));
    connect(ui->itemGroupWidget, SIGNAL(itemClicked(QListWidgetItem*)), ui->tableView, SLOT(FeatureSelected(QListWidgetItem*)));
    connect(ui->monsterGroupWidget, SIGNAL(itemClicked(QListWidgetItem*)), ui->tableView, SLOT(FeatureSelected(QListWidgetItem*)));
    connect(ui->vehicleWidget, SIGNAL(itemClicked(QListWidgetItem*)), ui->tableView, SLOT(FeatureSelected(QListWidgetItem*)));

    connect(ui->terrainWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->furnitureWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->trapWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->itemWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->monsterWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->itemGroupWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->monsterGroupWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->vehicleWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));

    connect(this, SIGNAL(CurrentFeatureChanged(QListWidgetItem*)), ui->tableView, SLOT(FeatureSelected(QListWidgetItem*)));

    // TODO should be a better way...
    connect(ui->itemGroupChance, SIGNAL(valueChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->monsterGroupChance, SIGNAL(valueChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->monsterGroupDensity, SIGNAL(valueChanged(double)), this, SLOT(ObjectEditorModified()));
    connect(ui->vehicleChance, SIGNAL(valueChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->vehicleStatus, SIGNAL(currentIndexChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->vehicleDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(ObjectEditorModified()));

    p.Parse("c:/code/Cataclysm-DDA/data");

    ui->mainToolBar->addAction("Write", this, SLOT(Write()));
    ui->mainToolBar->addSeparator();

    _tools =  new QActionGroup(ui->mainToolBar);
    QAction* penAction = new QAction("Pen", _tools);
    penAction->setData(QVariant::fromValue<Tool>(Pen));
    penAction->setCheckable(true);
    penAction->setChecked(true);
    connect(penAction, SIGNAL(triggered()), ui->tableView, SLOT(ToolChanged()));

    QAction* filledRectAction = new QAction("Filled Rect", _tools);
    filledRectAction->setData(QVariant::fromValue<Tool>(FilledRectangle));
    filledRectAction->setCheckable(true);
    connect(filledRectAction, SIGNAL(triggered()), ui->tableView, SLOT(ToolChanged()));

    QAction* hollowRectAction = new QAction("Hollow Rect", _tools);
    hollowRectAction->setData(QVariant::fromValue<Tool>(HollowRectangle));
    hollowRectAction->setCheckable(true);
    connect(hollowRectAction, SIGNAL(triggered()), ui->tableView, SLOT(ToolChanged()));

    ui->mainToolBar->addActions(_tools->actions());

    ui->itemGroupEditor->setVisible(false);
    ui->monsterGroupEditor->setVisible(false);
    ui->itemEditor->setVisible(false);
    ui->vehicleEditor->setVisible(false);

    ui->vehicleStatus->addItem("Undamaged", 0);
    ui->vehicleStatus->addItem("Lightly Damaged", -1);
    ui->vehicleStatus->addItem("Disabled", 1);

    ui->vehicleDirection->addItem("North", 0);
    ui->vehicleDirection->addItem("East", 1);
    ui->vehicleDirection->addItem("South", 2);
    ui->vehicleDirection->addItem("West", 3);
    ui->vehicleDirection->addItem("Random", 4);

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
//    active[0][1] = true;
//    active[1][1] = true;

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

    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1 - %2%3").arg(t.GetSymbol()).arg(t.GetDescription()).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->terrainWidget);
    item->setToolTip(t.GetID());
    item->setData(Qt::UserRole, t.GetID());
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(F_Terrain));
}

void BuildingEditor::NewFurniture(Furniture f, QString mod)
{
    Features::AddFurniture(f.GetID(), f, mod);

    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1 - %2%3").arg(f.GetSymbol()).arg(f.GetDescription()).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->furnitureWidget);
    item->setToolTip(f.GetID());
    item->setData(Qt::UserRole, f.GetID());
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(F_Furniture));
}

void BuildingEditor::NewTrap(Trap tr, QString mod)
{
    Features::AddTrap(tr.GetID(), tr, mod);

    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1 - %2%3").arg(tr.GetSymbol()).arg(tr.GetDescription()).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->trapWidget);
    item->setToolTip(tr.GetID());
    item->setData(Qt::UserRole, tr.GetID());
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(F_Trap));
}

void BuildingEditor::NewItem(QString name, QString id, QChar symbol, QString mod)
{
    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1 - %2%3").arg(symbol).arg(name).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->itemWidget);
    item->setToolTip(id);
    item->setData(Qt::UserRole, id);
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(F_Item));
}

void BuildingEditor::NewItemGroup(ItemGroup ig, QString mod)
{
    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1%2").arg(ig.GetID()).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->itemGroupWidget);
    item->setData(Qt::UserRole, QVariant::fromValue(ig));
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(F_ItemGroup));
}

void BuildingEditor::NewMonster(QString name, QString id, QChar symbol, QString mod)
{
    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1 - %2%3").arg(symbol).arg(name).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->monsterWidget);
    item->setToolTip(id);
    item->setData(Qt::UserRole, id);
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(F_Monster));
}

void BuildingEditor::NewMonsterGroup(MonsterGroup mg, QString mod)
{
    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1%2").arg(mg.GetID()).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->monsterGroupWidget);
    item->setData(Qt::UserRole, QVariant::fromValue(mg));
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(F_MonsterGroup));
}

void BuildingEditor::NewVehicle(Vehicle veh, QString mod)
{
    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1%2").arg(veh.GetName()).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->vehicleWidget);
    item->setToolTip(veh.GetID());
    item->setData(Qt::UserRole, QVariant::fromValue(veh));
    item->setData(FeatureTypeRole, QVariant::fromValue(F_Vehicle));
}


void BuildingEditor::Write()
{
    JsonWriter w;
    w.Write(m);
}

void BuildingEditor::SetObjectEditorMode(Feature f)
{
    ui->itemGroupEditor->setVisible(false);
    ui->monsterGroupEditor->setVisible(false);
    ui->itemEditor->setVisible(false);
    switch(f)
    {
        case F_Terrain:
            break;
        case F_Furniture:
            break;
        case F_Trap:
            break;
        case F_ItemGroup:
            ui->itemGroupEditor->setVisible(true);
            break;
        case F_MonsterGroup:
            ui->monsterGroupEditor->setVisible(true);
            break;
        case F_Item:
            break;
        case F_Monster:
            break;
        default:
            break;
    }
}

void BuildingEditor::SetObjectEditorMode(QListWidgetItem* i)
{
    _currentItem = i;

    Feature f = i->data(FeatureTypeRole).value<Feature>();
    QVariant v = i->data(Qt::UserRole);

    ui->itemGroupEditor->setVisible(false);
    ui->monsterGroupEditor->setVisible(false);
    ui->itemEditor->setVisible(false);
    ui->vehicleEditor->setVisible(false);

    switch(f)
    {
        case F_Terrain:
            break;
        case F_Furniture:
            break;
        case F_Trap:
            break;
        case F_ItemGroup:
        {
            ui->itemGroupEditor->setVisible(true);
            ui->itemGroupName->setText(v.value<ItemGroup>().GetID());
            ui->itemGroupChance->setValue(v.value<ItemGroup>().GetChance());
            break;
        }
        case F_MonsterGroup:
            ui->monsterGroupEditor->setVisible(true);
            ui->monsterGroupName->setText(v.value<MonsterGroup>().GetID());
            ui->monsterGroupDensity->setValue(v.value<MonsterGroup>().GetDensity());
            ui->monsterGroupChance->setValue(v.value<MonsterGroup>().GetChance());
            break;
        case F_Item:
        {
            ui->itemEditor->setVisible(true);
            break;
        }
        case F_Monster:
            break;
        case F_Vehicle:
            ui->vehicleEditor->setVisible(true);
            ui->vehicleID->setText(v.value<Vehicle>().GetID());
            ui->vehicleName->setText(v.value<Vehicle>().GetName());
            ui->vehicleChance->setValue(v.value<Vehicle>().GetChance());
            ui->vehicleStatus->setCurrentIndex(ui->vehicleStatus->findData(v.value<Vehicle>().GetStatus()));
            ui->vehicleDirection->setCurrentIndex(ui->vehicleDirection->findData(v.value<Vehicle>().GetDirection()));
            break;
        default:
            break;
    }
}

void BuildingEditor::ObjectEditorModified()
{
    if (_currentItem == NULL)
    {
        return;
    }
    Feature f = _currentItem->data(FeatureTypeRole).value<Feature>();
    QVariant v = _currentItem->data(Qt::UserRole);

    switch(f)
    {
        case F_Terrain:
            break;
        case F_Furniture:
            break;
        case F_Trap:
            break;
        case F_ItemGroup:
        {
            ItemGroup ig = v.value<ItemGroup>();
            ig.SetChance(ui->itemGroupChance->value());
            _currentItem->setData(Qt::UserRole, QVariant::fromValue(ig));
            emit CurrentFeatureChanged(_currentItem);
            break;
        }
        case F_MonsterGroup:
        {
            MonsterGroup mg = v.value<MonsterGroup>();
            mg.SetChance(ui->monsterGroupChance->value());
            mg.SetDensity(ui->monsterGroupDensity->value());
            _currentItem->setData(Qt::UserRole, QVariant::fromValue(mg));
            emit CurrentFeatureChanged(_currentItem);
            break;
        }
        case F_Item:
            break;
        case F_Monster:
            break;
        case F_Vehicle:
        {
            Vehicle veh = v.value<Vehicle>();
            veh.SetChance(ui->vehicleChance->value());
            veh.SetStatus(ui->vehicleStatus->itemData(ui->vehicleStatus->currentIndex()).toInt());
            veh.SetDirection(ui->vehicleDirection->itemData(ui->vehicleDirection->currentIndex()).toInt());
            _currentItem->setData(Qt::UserRole, QVariant::fromValue(veh));
            emit CurrentFeatureChanged(_currentItem);
            break;
        }
        default:
            break;
    }
}

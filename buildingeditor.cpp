#include "buildingeditor.h"
#include "ui_buildingeditor.h"

#include "jsonparser.h"
#include "jsonwriter.h"
#include "jsonloader.h"

#include "gaspump.h"
#include "field.h"

#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>

BuildingEditor::BuildingEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BuildingEditor), m(NULL), _currentItem(NULL)
{
    ui->setupUi(this);

    QCoreApplication::setApplicationName("Cataclysm Building Editor");
    QCoreApplication::setOrganizationName("vache");

    ui->zLevelLE->setHidden(true);
    ui->zLevelSlider->setHidden(true);

    JsonParser p;

    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(NewBuilding()));
    connect(ui->actionShow, SIGNAL(triggered()), &_omtDialog, SLOT(show()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(Open()));

    connect(&p, SIGNAL(ParsedTerrain(Terrain, QString)), this, SLOT(NewTerrain(Terrain, QString)));
    connect(&p, SIGNAL(ParsedFurniture(Furniture, QString)), this, SLOT(NewFurniture(Furniture, QString)));
    connect(&p, SIGNAL(ParsedTrap(Trap,QString)), this, SLOT(NewTrap(Trap,QString)));
    connect(&p, SIGNAL(ParsedItem(QString,QString,QChar,QString)), this, SLOT(NewItem(QString,QString,QChar,QString)));
    connect(&p, SIGNAL(ParsedMonster(QString,QString,QChar,QString)), this, SLOT(NewMonster(QString,QString,QChar,QString)));
    connect(&p, SIGNAL(ParsedItemGroup(ItemGroup,QString)), this, SLOT(NewItemGroup(ItemGroup,QString)));
    connect(&p, SIGNAL(ParsedMonsterGroup(MonsterGroup,QString)), this, SLOT(NewMonsterGroup(MonsterGroup,QString)));
    connect(&p, SIGNAL(ParsedVehicle(Vehicle,QString)), this, SLOT(NewVehicle(Vehicle,QString)));
    connect(&p, SIGNAL(ParsedNPC(QString,QString,QString,QString,QString)), this, SLOT(NewNPC(QString,QString,QString,QString,QString)));
    connect(&p, SIGNAL(ParsedOMT(OMTData)), &_omtDialog, SLOT(AddOMTData(OMTData)));
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
    connect(ui->npcWidget, SIGNAL(itemClicked(QListWidgetItem*)), ui->tableView, SLOT(FeatureSelected(QListWidgetItem*)));
    connect(ui->specialsWidget, SIGNAL(itemClicked(QListWidgetItem*)), ui->tableView, SLOT(FeatureSelected(QListWidgetItem*)));

    connect(ui->terrainWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->furnitureWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->trapWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->itemWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->monsterWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->itemGroupWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->monsterGroupWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->vehicleWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->npcWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));
    connect(ui->specialsWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetObjectEditorMode(QListWidgetItem*)));

    connect(this, SIGNAL(CurrentFeatureChanged(QListWidgetItem*)), ui->tableView, SLOT(FeatureSelected(QListWidgetItem*)));

    // TODO should be a better way...
    connect(ui->itemGroupChance, SIGNAL(valueChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->monsterGroupChance, SIGNAL(valueChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->monsterGroupDensity, SIGNAL(valueChanged(double)), this, SLOT(ObjectEditorModified()));
    connect(ui->vehicleChance, SIGNAL(valueChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->vehicleStatus, SIGNAL(currentIndexChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->vehicleDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->vehicleCustomDirection, SIGNAL(valueChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->vehicleFuel, SIGNAL(valueChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->signageText, SIGNAL(textChanged(QString)), this, SLOT(ObjectEditorModified()));
    connect(ui->radiationAmount, SIGNAL(valueChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->vending, SIGNAL(currentIndexChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->minFuel, SIGNAL(valueChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->maxFuel, SIGNAL(valueChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->fuelType, SIGNAL(currentIndexChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->rubbleType, SIGNAL(currentIndexChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->floorType, SIGNAL(currentIndexChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->overwrite, SIGNAL(clicked(bool)), this, SLOT(ObjectEditorModified()));
    connect(ui->placeItems, SIGNAL(clicked(bool)), this, SLOT(ObjectEditorModified()));
    connect(ui->fieldName, SIGNAL(currentIndexChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->fieldAge, SIGNAL(valueChanged(int)), this, SLOT(ObjectEditorModified()));
    connect(ui->fieldDensity, SIGNAL(valueChanged(int)), this, SLOT(ObjectEditorModified()));

    // TODO move all UI init to own methods.

    SetupFields();

    // Erasers need to go in before the parser does its thing!
    // NOTE: for some reason, tr_null is defined in traps.json (unlike everything else) so skip it here
    // though we may want to actually add it for the sake of consistency
    // NOTE: also note, terrain should never be null, so dont let them change it back to null.
    QListWidgetItem* f_null = new QListWidgetItem("Erase Furniture", ui->furnitureWidget);
    f_null->setData(Qt::UserRole, "f_null");
    f_null->setData(FeatureTypeRole, QVariant::fromValue(F_Furniture));
    Features::AddFurniture("f_null", Furniture(), "");

    QListWidgetItem* ig_null = new QListWidgetItem("Erase Item Group", ui->itemGroupWidget);
    ig_null->setData(Qt::UserRole, QVariant::fromValue(ItemGroup()));
    ig_null->setData(FeatureTypeRole, QVariant::fromValue(F_ItemGroup));

    QListWidgetItem* mg_null = new QListWidgetItem("Erase Monster Group", ui->monsterGroupWidget);
    mg_null->setData(Qt::UserRole, QVariant::fromValue(MonsterGroup()));
    mg_null->setData(FeatureTypeRole, QVariant::fromValue(F_MonsterGroup));

    QListWidgetItem* mon_null = new QListWidgetItem("Erase Monster", ui->monsterWidget);
    mon_null->setData(Qt::UserRole, "");
    mon_null->setData(FeatureTypeRole, QVariant::fromValue(F_Monster));

    QListWidgetItem* i_null = new QListWidgetItem("Erase Items", ui->itemWidget);
    i_null->setData(Qt::UserRole, "");
    i_null->setData(FeatureTypeRole, QVariant::fromValue(F_Item));

    QListWidgetItem* veh_null = new QListWidgetItem("Erase Vehicle", ui->vehicleWidget);
    veh_null->setData(Qt::UserRole, QVariant::fromValue(Vehicle()));
    veh_null->setData(FeatureTypeRole, QVariant::fromValue(F_Vehicle));

    QListWidgetItem* toilet = new QListWidgetItem("Place Toilet Water", ui->specialsWidget);
    toilet->setData(Qt::UserRole, true);
    toilet->setData(FeatureTypeRole, QVariant::fromValue(F_Toilet));

    QListWidgetItem* rem_toilet = new QListWidgetItem("Remove Toilet Water", ui->specialsWidget);
    rem_toilet->setData(Qt::UserRole, false);
    rem_toilet->setData(FeatureTypeRole, QVariant::fromValue(F_Toilet));

    QListWidgetItem* vending = new QListWidgetItem("Add Vending Machine", ui->specialsWidget);
    vending->setData(Qt::UserRole, "vending_food");
    vending->setData(FeatureTypeRole, QVariant::fromValue(F_Vending));

    QListWidgetItem* sign = new QListWidgetItem("Set Signage", ui->specialsWidget);
    sign->setData(Qt::UserRole, "Sign Text");
    sign->setData(FeatureTypeRole, QVariant::fromValue(F_Sign));

    QListWidgetItem* radiation = new QListWidgetItem("Set Radiation", ui->specialsWidget);
    radiation->setData(Qt::UserRole, 0);
    radiation->setData(FeatureTypeRole, QVariant::fromValue(F_Radiation));

    QListWidgetItem* gasPump = new QListWidgetItem("Set Gas Pump", ui->specialsWidget);
    gasPump->setData(Qt::UserRole, QVariant::fromValue(GasPump()));
    gasPump->setData(FeatureTypeRole, QVariant::fromValue(F_GasPump));

    QListWidgetItem* rubble = new QListWidgetItem("Set Rubble", ui->specialsWidget);
    rubble->setData(Qt::UserRole, QVariant::fromValue(Rubble()));
    rubble->setData(FeatureTypeRole, QVariant::fromValue(F_Rubble));

    QListWidgetItem* field = new QListWidgetItem("Set Field", ui->specialsWidget);
    field->setData(Qt::UserRole, QVariant::fromValue(Field()));
    field->setData(FeatureTypeRole, QVariant::fromValue(F_Field));

    ui->vehicleStatus->addItem("Undamaged", 0);
    ui->vehicleStatus->addItem("Lightly Damaged", -1);
    ui->vehicleStatus->addItem("Disabled", 1);

    ui->vehicleDirection->addItem("North", 270);
    ui->vehicleDirection->addItem("East", 0);
    ui->vehicleDirection->addItem("South", 90);
    ui->vehicleDirection->addItem("West", 180);
    //ui->vehicleDirection->addItem("Random", -1);
    ui->vehicleDirection->addItem("Other", -2);

    ui->vending->addItem("none", "");

    ui->fuelType->addItem("none", "");
    ui->fuelType->addItem("gasoline", "gasoline");
    ui->fuelType->addItem("diesel", "diesel");
    ui->fuelType->addItem("random", "random");

    ui->rubbleType->addItem("default", "");
    ui->floorType->addItem("default", "");

    QSettings settings;

    QString dataDir = settings.value("cataclysm_dir", "").toString();
    QString cataclysmDir = QFileDialog::getExistingDirectory(this, "Select Your Cataclysm Data Directory", dataDir);
    if (cataclysmDir.isEmpty())
    {
        // TODO this should show an error terminate the application, this is just for testing...
        cataclysmDir = "c:/code/Cataclysm-DDA/data";
    }
    settings.setValue("cataclysm_dir", cataclysmDir);
    p.Parse(cataclysmDir);

    ui->mainToolBar->addAction("Write", this, SLOT(Write()));
    ui->mainToolBar->addSeparator();

    QAction* eraseAction = ui->mainToolBar->addAction("Erase");
    eraseAction->setCheckable(true);
    eraseAction->setChecked(false);

    connect(eraseAction, SIGNAL(toggled(bool)), ui->tableView, SLOT(SetEraseMode(bool)));

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

    ui->objectEditor->setVisible(false);

    // TEMP TEST CODE
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
    if (QMessageBox::critical(this, "Create new building", "Are you sure you want to continue?\n"
                              "This will delete all unsaved changes!",
                              QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Cancel)
    {
        return;
    }
    bool active[10][10];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            active[i][j] = false;
        }
    }
    active[0][0] = true;
    delete m;
    m = new BuildingModel(active);
    ui->tableView->setModel(m);
}

void BuildingEditor::Open()
{
    QSettings settings;
    QString filename = QFileDialog::getOpenFileName(this, "Select a JSON file to open", settings.value("cataclysm_dir", "").toString(), "JSON (*.json)");

    JsonLoader l;
    connect(&l, SIGNAL(OmtLoaded(OvermapTerrain*)), m, SLOT(OnOmtLoaded(OvermapTerrain*)));
    l.Load(filename);
}

void BuildingEditor::NewTerrain(Terrain t, QString mod)
{
    Features::AddTerrain(t.GetID(), t, mod);

    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1 - %2%3").arg(t.GetSymbol()).arg(t.GetDescription()).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->terrainWidget);
    if (mod.isEmpty())
    {
        item->setToolTip(t.GetID());
    }
    else
    {
        item->setToolTip(QString("%1 - %2").arg(t.GetID()).arg(mod));
    }
    item->setData(Qt::UserRole, t.GetID());
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(F_Terrain));

    ui->floorType->addItem(displayText, t.GetID());
}

void BuildingEditor::NewFurniture(Furniture f, QString mod)
{
    Features::AddFurniture(f.GetID(), f, mod);

    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1 - %2%3").arg(f.GetSymbol()).arg(f.GetDescription()).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->furnitureWidget);
    if (mod.isEmpty())
    {
        item->setToolTip(f.GetID());
    }
    else
    {
        item->setToolTip(QString("%1 - %2").arg(f.GetID()).arg(mod));
    }
    item->setData(Qt::UserRole, f.GetID());
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(F_Furniture));

    ui->rubbleType->addItem(displayText, f.GetID());
}

void BuildingEditor::NewTrap(Trap tr, QString mod)
{
    Features::AddTrap(tr.GetID(), tr, mod);

    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1 - %2%3").arg(tr.GetSymbol()).arg(tr.GetDescription()).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->trapWidget);
    if (mod.isEmpty())
    {
        item->setToolTip(tr.GetID());
    }
    else
    {
        item->setToolTip(QString("%1 - %2").arg(tr.GetID()).arg(mod));
    }
    item->setData(Qt::UserRole, tr.GetID());
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(F_Trap));
}

void BuildingEditor::NewItem(QString name, QString id, QChar symbol, QString mod)
{
    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1 - %2%3").arg(symbol).arg(name).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->itemWidget);
    if (mod.isEmpty())
    {
        item->setToolTip(id);
    }
    else
    {
        item->setToolTip(QString("%1 - %2").arg(id).arg(mod));
    }
    item->setData(Qt::UserRole, id);
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(F_Item));
}

void BuildingEditor::NewItemGroup(ItemGroup ig, QString mod)
{
    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1%2").arg(ig.GetID()).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->itemGroupWidget);
    if (!mod.isEmpty())
    {
        item->setToolTip(mod);
    }
    item->setData(Qt::UserRole, QVariant::fromValue(ig));
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(F_ItemGroup));

    ui->vending->addItem(displayText, ig.GetID());
}

void BuildingEditor::NewMonster(QString name, QString id, QChar symbol, QString mod)
{
    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1 - %2%3").arg(symbol).arg(name).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->monsterWidget);
    if (mod.isEmpty())
    {
        item->setToolTip(id);
    }
    else
    {
        item->setToolTip(QString("%1 - %2").arg(id).arg(mod));
    }
    item->setData(Qt::UserRole, id);
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(F_Monster));
}

void BuildingEditor::NewMonsterGroup(MonsterGroup mg, QString mod)
{
    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1%2").arg(mg.GetID()).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->monsterGroupWidget);
    if (!mod.isEmpty())
    {
        item->setToolTip(mod);
    }
    item->setData(Qt::UserRole, QVariant::fromValue(mg));
    item->setData(FeatureTypeRole, QVariant::fromValue<Feature>(F_MonsterGroup));
}

void BuildingEditor::NewVehicle(Vehicle veh, QString mod)
{
    QString modded = (mod == "") ? "" : " *";
    QString displayText = QString("%1%2").arg(veh.GetName()).arg(modded);
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->vehicleWidget);
    if (mod.isEmpty())
    {
        item->setToolTip(veh.GetID());
    }
    else
    {
        item->setToolTip(QString("%1 - %2").arg(veh.GetID()).arg(mod));
    }
    item->setData(Qt::UserRole, QVariant::fromValue(veh));
    item->setData(FeatureTypeRole, QVariant::fromValue(F_Vehicle));
}

void BuildingEditor::NewNPC(QString id, QString name, QString faction, QString comment, QString mod)
{
    QString displayText = QString("%1 - %2 - %3").arg(id).arg(faction).arg(name);
    QString toolTipText = "";
    // comment and mod are both optional
    if (!comment.isEmpty() && mod.isEmpty())
    {
        toolTipText = comment;
    }
    else if (!mod.isEmpty() && comment.isEmpty())
    {
        toolTipText = mod;
    }
    else if (!mod.isEmpty() && !comment.isEmpty())
    {
        toolTipText = QString("%1 - %2").arg(comment).arg(mod);
    }
    QListWidgetItem* item = new QListWidgetItem(displayText, ui->npcWidget);
    item->setToolTip(toolTipText);
    item->setData(Qt::UserRole, id);
    item->setData(FeatureTypeRole, QVariant::fromValue(F_NPC));
}

void BuildingEditor::Write()
{
    JsonWriter w;
    if (!_omtDialog.GetOMTData().IsReadOnly())
    {
        w.WriteOMTData(_omtDialog.GetOMTData());
    }
    w.Write(m);
}

void BuildingEditor::SetObjectEditorMode(QListWidgetItem* i)
{
    _currentItem = i;

    Feature f = i->data(FeatureTypeRole).value<Feature>();
    QVariant v = i->data(Qt::UserRole);

    ui->objectEditor->setVisible(false);

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
        ui->objectEditor->setVisible(true);
        ui->objectEditor->setCurrentWidget(ui->itemGroupEditor);
        ui->itemGroupName->setText(v.value<ItemGroup>().GetID());
        ui->itemGroupChance->setValue(v.value<ItemGroup>().GetChance());
        break;
    }
    case F_MonsterGroup:
        ui->objectEditor->setVisible(true);
        ui->objectEditor->setCurrentWidget(ui->monsterGroupEditor);
        ui->monsterGroupName->setText(v.value<MonsterGroup>().GetID());
        ui->monsterGroupDensity->setValue(v.value<MonsterGroup>().GetDensity());
        ui->monsterGroupChance->setValue(v.value<MonsterGroup>().GetChance());
        break;
    case F_Item:
    {
        //ui->itemEditor->setVisible(true);
        break;
    }
    case F_Monster:
        break;
    case F_Vehicle:
    {
        ui->objectEditor->setVisible(true);
        ui->objectEditor->setCurrentWidget(ui->vehicleEditor);
        ui->vehicleID->setText(v.value<Vehicle>().GetID());
        ui->vehicleName->setText(v.value<Vehicle>().GetName());
        ui->vehicleChance->setValue(v.value<Vehicle>().GetChance());
        ui->vehicleStatus->setCurrentIndex(ui->vehicleStatus->findData(v.value<Vehicle>().GetStatus()));
        int index = ui->vehicleDirection->findData(v.value<Vehicle>().GetDirection());
        if (index != -1)
        {
            ui->vehicleDirection->setCurrentIndex(index);
        }
        else
        {
            ui->vehicleDirection->setCurrentIndex(ui->vehicleDirection->findData(-2));
            ui->vehicleCustomDirection->setValue(v.value<Vehicle>().GetDirection());
        }
        ui->vehicleFuel->setValue(v.value<Vehicle>().GetFuel());
        break;
    }
    case F_Sign:
        ui->objectEditor->setVisible(true);
        ui->objectEditor->setCurrentWidget(ui->signageEditor);
        ui->signageText->setText(v.toString());
        break;
    case F_Radiation:
        ui->objectEditor->setVisible(true);
        ui->objectEditor->setCurrentWidget(ui->radiationEditor);
        ui->radiationAmount->setValue(v.toInt());
        break;
    case F_Vending:
        ui->objectEditor->setVisible(true);
        ui->objectEditor->setCurrentWidget(ui->vendingEditor);
        ui->vending->setCurrentText(v.toString());
        break;
    case F_GasPump:
        ui->objectEditor->setVisible(true);
        ui->objectEditor->setCurrentWidget(ui->gasPumpEditor);
        ui->fuelType->setCurrentIndex(ui->fuelType->findData(v.value<GasPump>().GetFuel()));
        ui->minFuel->setValue(v.value<GasPump>().GetMinAmount());
        ui->maxFuel->setValue(v.value<GasPump>().GetMaxAmount());
        break;
    case F_Rubble:
        ui->objectEditor->setVisible(true);
        ui->objectEditor->setCurrentWidget(ui->rubbleEditor);
        ui->rubbleType->setCurrentIndex(ui->rubbleType->findData(v.value<Rubble>().GetRubbleType()));
        ui->floorType->setCurrentIndex(ui->floorType->findData(v.value<Rubble>().GetFloorType()));
        ui->placeItems->setChecked(v.value<Rubble>().GetCreateItems());
        ui->overwrite->setChecked(v.value<Rubble>().GetOverwrite());
        break;
    case F_Field:
        ui->objectEditor->setVisible(true);
        ui->objectEditor->setCurrentWidget(ui->fieldEditor);
        ui->fieldName->setCurrentText(v.value<Field>().GetName());
        ui->fieldAge->setValue(v.value<Field>().GetAge());
        ui->fieldDensity->setValue(v.value<Field>().GetDensity());
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

    if (ui->vehicleDirection->itemData(ui->vehicleDirection->currentIndex()).toInt() == -2)
    {
        ui->vehicleCustomDirection->setEnabled(true);
    }
    else
    {
        ui->vehicleCustomDirection->setEnabled(false);
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
        if (ui->vehicleDirection->itemData(ui->vehicleDirection->currentIndex()).toInt() != -2)
        {
            veh.SetDirection(ui->vehicleDirection->itemData(ui->vehicleDirection->currentIndex()).toInt());
        }
        else
        {
            veh.SetDirection(ui->vehicleCustomDirection->value());
        }
        veh.SetFuel(ui->vehicleFuel->value());
        _currentItem->setData(Qt::UserRole, QVariant::fromValue(veh));
        emit CurrentFeatureChanged(_currentItem);
        break;
    }
    case F_Sign:
        qDebug() << ui->signageText->text();
        _currentItem->setData(Qt::UserRole, ui->signageText->text());
        emit CurrentFeatureChanged(_currentItem);
        break;
    case F_Radiation:
        _currentItem->setData(Qt::UserRole, ui->radiationAmount->value());
        emit CurrentFeatureChanged(_currentItem);
        break;
    case F_Vending:
        _currentItem->setData(Qt::UserRole, ui->vending->currentData());
        emit CurrentFeatureChanged(_currentItem);
        break;
    case F_GasPump:
    {
        GasPump gasPump = v.value<GasPump>();
        gasPump.SetFuel(ui->fuelType->currentData().toString());
        gasPump.SetMinAmount(ui->minFuel->value());
        gasPump.SetMaxAmount(ui->maxFuel->value());
        _currentItem->setData(Qt::UserRole, QVariant::fromValue(gasPump));
        emit CurrentFeatureChanged(_currentItem);
        break;
    }
    case F_Rubble:
    {
        Rubble rubble = v.value<Rubble>();
        rubble.SetRubbleType(ui->rubbleType->currentData().toString());
        rubble.SetFloorType(ui->floorType->currentData().toString());
        rubble.SetCreateItems(ui->placeItems->isChecked());
        rubble.SetOverwrite(ui->overwrite->isChecked());
        _currentItem->setData(Qt::UserRole, QVariant::fromValue(rubble));
        emit CurrentFeatureChanged(_currentItem);
        break;
    }
    case F_Field:
    {
        Field field = v.value<Field>();
        field.SetName(ui->fieldName->currentText());
        field.SetAge(ui->fieldAge->value());
        field.SetDensity(ui->fieldDensity->value());
        _currentItem->setData(Qt::UserRole, QVariant::fromValue(field));
        emit CurrentFeatureChanged(_currentItem);
        break;
    }
    default:
        break;
    }
}

void BuildingEditor::SetupFields()
{
    static QStringList fieldIDs = { "fd_blood", "fd_bile", "fd_gibs_flesh", "fd_gibs_veggy", "fd_web",
                                    "fd_slime", "fd_acid", "fd_sap", "fd_sludge", "fd_fire", "fd_rubble",
                                    "fd_smoke", "fd_toxic_gas", "fd_tear_gas", "fd_nuke_gas", "fd_gas_vent",
                                    "fd_fire_vent", "fd_flame_burst", "fd_electricity", "fd_fatigue",
                                    "fd_push_items", "fd_shock_vent", "fd_acid_vent", "fd_plasma", "fd_laser",
                                    "fd_spotlight", "fd_dazzling", "fd_blood_veggy", "fd_blood_insect",
                                    "fd_blood_invertebrate", "fd_gibs_insect", "fd_gibs_invertebrate",
                                    "fd_cigsmoke", "fd_weedsmoke", "fd_cracksmoke", "fd_methsmoke", "fd_bees",
                                    "fd_incendiary", "fd_relax_gas", "fd_fungal_haze", "fd_hot_air1",
                                    "fd_hot_air2", "fd_hot_air3", "fd_hot_air4" };

    foreach (QString fieldID, fieldIDs)
    {
        ui->fieldName->addItem(fieldID, QVariant::fromValue(Field(fieldID, 0, 1)));
    }
}

#include "generalwizardpage.h"
#include "ui_generalwizardpage.h"
#include "newbuildingwizard.h"
#include "jsonparser.h"

#include <QFileDialog>
#include <QSettings>
#include <QDebug>

GeneralWizardPage::GeneralWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::GeneralWizardPage)
{
    ui->setupUi(this);

    connect(ui->existingOMT, SIGNAL(toggled(bool)), ui->existingOmtId, SLOT(setEnabled(bool)));
    connect(ui->existingOMT, SIGNAL(toggled(bool)), ui->newMapgenWeight, SLOT(setEnabled(bool)));
    connect(ui->existingOMT, SIGNAL(toggled(bool)), this, SLOT(SetLastPage(bool)));

    connect(ui->newMapgenWeight, SIGNAL(valueChanged(int)), this, SIGNAL(completeChanged()));
    connect(ui->dataDirectory, SIGNAL(textChanged(QString)), this, SIGNAL(completeChanged()));

    connect(ui->browseButton, SIGNAL(clicked(bool)), this, SLOT(OnBrowse()));

    connect(ui->dataDirectory, SIGNAL(textChanged(QString)), this, SLOT(LoadModList(QString)));
    connect(ui->enableSelectedMod, SIGNAL(clicked(bool)), this, SLOT(EnableSelectedMods()));
    connect(ui->disasbleSelectedMod, SIGNAL(clicked(bool)), this, SLOT(DisableSelectedMods()));
    connect(ui->enabledMods, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(DisableSelectedMod(QListWidgetItem*)));
    connect(ui->disabledMods, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(EnableSelectedMod(QListWidgetItem*)));

    setCommitPage(false);
    setFinalPage(false);

    QSettings settings("vache", "Cataclysm Building Editor");

    QString dataDir = settings.value("cataclysm_dir", "").toString();
    ui->dataDirectory->setText(dataDir);
}

GeneralWizardPage::~GeneralWizardPage()
{
    delete ui;
}

int GeneralWizardPage::nextId() const
{
    if (ui->newSpecial->isChecked())
    {
        return NewBuildingWizard::SPECIAL_PAGE;
    }
    else if (ui->newOMT->isChecked())
    {
        return NewBuildingWizard::OMT_PAGE;
    }
    return -1;
}

bool GeneralWizardPage::isComplete() const
{
    if (ui->dataDirectory->text().isEmpty())
    {
        return false;
    }
    if (ui->existingOMT->isChecked())
    {
        // TODO make sure an OMT ID has been selected.
        if (ui->newMapgenWeight->value() == 0)
        {
            return false;
        }
    }
    return true;
}

bool GeneralWizardPage::isFinalPage() const
{
    if (ui->existingOMT->isChecked())
    {
        return true;
    }
    return false;
}

void GeneralWizardPage::SetLastPage(bool last)
{
    setFinalPage(last);
}

QStringList GeneralWizardPage::GetEnabledMods() const
{
    QStringList mods;
    int count = ui->enabledMods->count();
    for (int i = 0; i < count; i++)
    {
        mods.append(ui->enabledMods->item(0)->text());
    }
    return mods;
}

void GeneralWizardPage::OnBrowse()
{
    QString dir = ui->dataDirectory->text();
    if (!QDir(dir).exists())
    {
        dir = "";
    }
    QString dataDir = QFileDialog::getExistingDirectory(this, "Select Cataclysm DDA Data Directory", dir);
    ui->dataDirectory->setText(dataDir);
}

void GeneralWizardPage::LoadModList(QString dataDirectory)
{
    if (dataDirectory.isEmpty())
    {
        return;
    }

    QStringList modList = JsonParser::FindMods(dataDirectory);

    ui->disabledMods->clear();
    ui->enabledMods->clear();
    ui->belongsToMod->clear();

    ui->disabledMods->addItems(modList);
    ui->belongsToMod->addItems(modList);
}

void GeneralWizardPage::EnableSelectedMods()
{
    QList<QListWidgetItem*> items = ui->disabledMods->selectedItems();

    foreach (QListWidgetItem* item, items)
    {
        ui->enabledMods->addItem(item->text());
        delete item;
    }
    ui->enabledMods->sortItems();
    ui->disabledMods->sortItems();
}

void GeneralWizardPage::DisableSelectedMods()
{
    QList<QListWidgetItem*> items = ui->enabledMods->selectedItems();

    foreach (QListWidgetItem* item, items)
    {
        ui->disabledMods->addItem(item->text());
        delete item;
    }
    ui->enabledMods->sortItems();
    ui->disabledMods->sortItems();
}

void GeneralWizardPage::EnableSelectedMod(QListWidgetItem* item)
{
    ui->enabledMods->addItem(item->text());
    ui->enabledMods->sortItems();
    delete item;
}

void GeneralWizardPage::DisableSelectedMod(QListWidgetItem* item)
{
    ui->disabledMods->addItem(item->text());
    ui->disabledMods->sortItems();
    delete item;
}

void GeneralWizardPage::initializePage()
{
    registerField("PositiveZLevels", ui->positiveZEnabled);
    registerField("ExistingOMT", ui->existingOMT);
    registerField("NewOMT", ui->newOMT);
    registerField("NewSpecial", ui->newSpecial);
}

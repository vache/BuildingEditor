#include "buildinginfodialog.h"
#include "ui_buildinginfodialog.h"

BuildingInfoDialog::BuildingInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuildingInfoDialog)
{
    ui->setupUi(this);

    info = BuildingInfo::GetBuildingInfo();
}

BuildingInfoDialog::~BuildingInfoDialog()
{
    delete ui;
}

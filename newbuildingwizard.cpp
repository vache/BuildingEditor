#include "newbuildingwizard.h"
#include "ui_newbuildingwizard.h"

NewBuildingWizard::NewBuildingWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::NewBuildingWizard)
{
    ui->setupUi(this);
}

NewBuildingWizard::~NewBuildingWizard()
{
    delete ui;
}

#include "generalwizardpage.h"
#include "ui_generalwizardpage.h"

GeneralWizardPage::GeneralWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::GeneralWizardPage)
{
    ui->setupUi(this);
}

GeneralWizardPage::~GeneralWizardPage()
{
    delete ui;
}

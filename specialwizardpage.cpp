#include "specialwizardpage.h"
#include "ui_specialwizardpage.h"

SpecialWizardPage::SpecialWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::SpecialWizardPage)
{
    ui->setupUi(this);
}

SpecialWizardPage::~SpecialWizardPage()
{
    delete ui;
}

void SpecialWizardPage::initializePage()
{
    ui->layout->SetZLevelsEnabled(field("PositiveZLevels").toBool());
}

QVector<bool> SpecialWizardPage::GetLayout()
{
    return ui->layout->GetLayout();
}

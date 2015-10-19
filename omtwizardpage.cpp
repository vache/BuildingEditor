#include "omtwizardpage.h"
#include "ui_omtwizardpage.h"

OMTWizardPage::OMTWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::OMTWizardPage)
{
    ui->setupUi(this);

    connect(ui->widget, SIGNAL(OMTModified()), this, SIGNAL(completeChanged()));
}

OMTWizardPage::~OMTWizardPage()
{
    delete ui;
}

bool OMTWizardPage::isComplete() const
{
    OMTData data = ui->widget->GetOMTData();
    if (data.GetID().isEmpty() || data.GetName().isEmpty() || data.GetSymbols()[0] == 32)
    {
        return false;
    }
    return true;
}

OMTData OMTWizardPage::GetOMTData() const
{
    return ui->widget->GetOMTData();
}

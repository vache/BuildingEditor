#include "newbuildingwizard.h"
#include "ui_newbuildingwizard.h"
#include "generalwizardpage.h"
#include "specialwizardpage.h"

NewBuildingWizard::NewBuildingWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::NewBuildingWizard)
{
    ui->setupUi(this);

    setPage(GENERAL_PAGE, new GeneralWizardPage());
    setPage(SPECIAL_PAGE, new SpecialWizardPage());

    setStartId(GENERAL_PAGE);
}

NewBuildingWizard::~NewBuildingWizard()
{
    delete ui;
}

QVector<bool> NewBuildingWizard::GetLayout()
{
    if (field("NewSpecial").toBool())
    {
        return ((SpecialWizardPage*)page(SPECIAL_PAGE))->GetLayout();
    }
    QVector<bool> layout;
    layout.fill(false, 9 * 9 * 21);
    layout[0] = true;
    return layout;
}

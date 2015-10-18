#include "specialwizardpage.h"
#include "ui_specialwizardpage.h"

SpecialWizardPage::SpecialWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::SpecialWizardPage)
{
    ui->setupUi(this);

    connect(ui->rotate, SIGNAL(toggled(bool)), ui->layout, SLOT(RotateToggled(bool)));
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

OvermapSpecialData SpecialWizardPage::GetData()
{
    OvermapSpecialData data;
    data.SetID(ui->specialId->text());
    for (int z = 10; z >= -10; z--)
    {
        for (int y = 0; y <= 9; y++)
        {
            for (int x = 0; x <= 9; x++)
            {
                Tripoint p(x, y, z);
            }
        }
    }
}

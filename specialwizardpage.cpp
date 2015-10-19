#include "specialwizardpage.h"
#include "ui_specialwizardpage.h"

SpecialWizardPage::SpecialWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::SpecialWizardPage)
{
    ui->setupUi(this);

    connect(ui->rotate, SIGNAL(toggled(bool)), ui->layout, SLOT(RotateToggled(bool)));
    connect(ui->specialId, SIGNAL(textChanged(QString)), this, SIGNAL(completeChanged()));
    connect(ui->layout, SIGNAL(LayoutChanged()), this, SIGNAL(completeChanged()));
    connect(ui->occurrencesMax, SIGNAL(valueChanged(int)), this, SIGNAL(completeChanged()));
}

SpecialWizardPage::~SpecialWizardPage()
{
    delete ui;
}

void SpecialWizardPage::initializePage()
{
    ui->layout->SetZLevelsEnabled(field("PositiveZLevels").toBool());
}

bool SpecialWizardPage::isComplete() const
{
    // required fields: ID, max occurrences > 0, at least one true in layout
    if ((!ui->layout->GetLayout().contains(true)) || ui->specialId->text().isEmpty() || ui->occurrencesMax->value() < 1)
    {
        return false;
    }
    return true;
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
                int index = (z * 9 * 9) + (y * 9) + x;
                if (ui->layout->GetLayout()[index])
                {
                    OMTData omtData = ui->layout->GetOvermapsData()[index];
                    data.AddLayoutEntry(Tripoint(x, y, z), omtData.GetID(), "");
                }
            }
        }
    }
    data.SetRotate(ui->rotate->isChecked());
    data.SetMinCityDistance(ui->cityDistanceMin->value());
    data.SetMaxCityDistance(ui->cityDistanceMax->value());
    data.SetMinOccurrences(ui->occurrencesMin->value());
    data.SetMaxCityDistance(ui->occurrencesMax->value());
    data.SetUnique(ui->unique->isChecked());
    // TODO flags and location

    return data;
}

#include "specialwizardpage.h"
#include "ui_specialwizardpage.h"

#include <QDebug>

SpecialWizardPage::SpecialWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::SpecialWizardPage)
{
    ui->setupUi(this);

    connect(ui->rotate, SIGNAL(toggled(bool)), ui->layout, SLOT(RotateToggled(bool)));
    connect(ui->specialId, SIGNAL(textChanged(QString)), this, SIGNAL(completeChanged()));
    connect(ui->layout, SIGNAL(LayoutChanged()), this, SIGNAL(completeChanged()));
    connect(ui->occurrencesMax, SIGNAL(valueChanged(int)), this, SIGNAL(completeChanged()));
    connect(ui->forestLocation, SIGNAL(toggled(bool)), this, SIGNAL(completeChanged()));
    connect(ui->highwayLocation, SIGNAL(toggled(bool)), this, SIGNAL(completeChanged()));
    connect(ui->landLocation, SIGNAL(toggled(bool)), this, SIGNAL(completeChanged()));
    connect(ui->wildernessLocation, SIGNAL(toggled(bool)), this, SIGNAL(completeChanged()));

    setFinalPage(true);
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
    // required fields: ID, max occurrences > 0, at least one true in layout, at least one location checked
    if ((!ui->layout->GetLayout().contains(true)) || ui->specialId->text().isEmpty() ||
        (ui->occurrencesMax->value() < 1) ||
        (!ui->wildernessLocation->isChecked() && !ui->highwayLocation->isChecked() &&
         !ui->landLocation->isChecked() && !ui->forestLocation->isChecked()))
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
    QString specialID = ui->specialId->text();
    data.SetID(specialID);
    data.SetRotate(ui->rotate->isChecked());
    qDebug() << "before loop" << ui->layout->GetLayout().size();
    for (int z = 10; z >= -10; z--)
    {
        for (int y = 0; y < 9; y++)
        {
            for (int x = 0; x < 9; x++)
            {
                int index = ((10 - z) * 9 * 9) + (y * 9) + x;
                if (ui->layout->GetLayout()[index])
                {
                    OMTData omtData = ui->layout->GetOvermapsData()[index];
                    QString pattern = "%1_%2_%3_%4";
                    omtData.SetID(pattern.arg(specialID).arg(QString::number(z).replace('-', 'b')).arg(x).arg(y));
                    omtData.SetRotate(data.GetRotates());
                    data.AddOMTData(omtData);
                    QString layoutID = omtData.GetID();
                    if (data.GetRotates())
                    {
                        layoutID = layoutID.append("_north");
                    }
                    data.AddLayoutEntry(Tripoint(x, y, z), layoutID, "");
                }
                else
                {
                    // this is a necessary evil right now.  i need to refactor how this whole thing works eventually
                    data.AddOMTData(OMTData());
                }
            }
        }
    }
    qDebug() << "after loop";
    data.SetMinCityDistance(ui->cityDistanceMin->value());
    data.SetMaxCityDistance(ui->cityDistanceMax->value());
    data.SetMinOccurrences(ui->occurrencesMin->value());
    data.SetMaxOccurrences(ui->occurrencesMax->value());
    data.SetUnique(ui->unique->isChecked());
    if (ui->landLocation->isChecked())
    {
        data.AddLocation("land");
    }
    if (ui->forestLocation->isChecked())
    {
        data.AddLocation("forest");
    }
    if (ui->highwayLocation->isChecked())
    {
        data.AddLocation("by_hiway");
    }
    if (ui->wildernessLocation->isChecked())
    {
        data.AddLocation("wilderness");
    }

    return data;
}

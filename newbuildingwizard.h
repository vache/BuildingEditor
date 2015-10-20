#ifndef NEWBUILDINGWIZARD_H
#define NEWBUILDINGWIZARD_H

#include "overmapspecialdata.h"
#include "omtdata.h"

#include <QWizard>
#include <QVector>

namespace Ui {
class NewBuildingWizard;
}

class NewBuildingWizard : public QWizard
{
    Q_OBJECT
public:
    enum Page : int { GENERAL_PAGE, SPECIAL_PAGE, OMT_PAGE };

    explicit NewBuildingWizard(QWidget *parent = 0);
    ~NewBuildingWizard();

    bool IsExistingOMT();
    bool IsNewOMT();
    bool IsNewSpecial();

    QVector<bool> GetLayout();
    OvermapSpecialData GetSpecialData();
    OMTData GetOMTData();

private:
    Ui::NewBuildingWizard *ui;

private slots:
    void Finalize();
};

#endif // NEWBUILDINGWIZARD_H

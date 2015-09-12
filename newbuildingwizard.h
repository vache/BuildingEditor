#ifndef NEWBUILDINGWIZARD_H
#define NEWBUILDINGWIZARD_H

#include <QWizard>

namespace Ui {
class NewBuildingWizard;
}

class NewBuildingWizard : public QWizard
{
    Q_OBJECT

public:
    explicit NewBuildingWizard(QWidget *parent = 0);
    ~NewBuildingWizard();

private:
    Ui::NewBuildingWizard *ui;
};

#endif // NEWBUILDINGWIZARD_H

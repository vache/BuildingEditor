#ifndef NEWBUILDINGWIZARD_H
#define NEWBUILDINGWIZARD_H

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

    QVector<bool> GetLayout();

private:
    Ui::NewBuildingWizard *ui;
};

#endif // NEWBUILDINGWIZARD_H

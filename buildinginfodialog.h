#ifndef BUILDINGINFODIALOG_H
#define BUILDINGINFODIALOG_H

#include <QDialog>
#include "buildinginfo.h"

namespace Ui {
class BuildingInfoDialog;
}

class BuildingInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuildingInfoDialog(QWidget *parent = 0);
    ~BuildingInfoDialog();

private:
    Ui::BuildingInfoDialog *ui;

    BuildingInfo* info;
};

#endif // BUILDINGINFODIALOG_H

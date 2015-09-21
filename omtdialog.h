#ifndef OMTDIALOG_H
#define OMTDIALOG_H

#include <QDialog>
#include "colors.h"

namespace Ui {
class OMTDialog;
}

class OMTDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OMTDialog(QWidget *parent = 0);
    ~OMTDialog();

private:
    Ui::OMTDialog *ui;

    void InitColorList();
};

#endif // OMTDIALOG_H

#include "omtdialog.h"
#include "ui_omtdialog.h"

OMTDialog::OMTDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OMTDialog)
{
    ui->setupUi(this);

    InitColorList();
}

OMTDialog::~OMTDialog()
{
    delete ui;
}

void OMTDialog::InitColorList()
{
    ui->color->clear();
    int index = 0;
    foreach (QString colorName, colorList)
    {
        ui->color->insertItem(index, colorName.replace("_", " "), colorName);
        ui->color->setItemData(index, QBrush(color_from_string(colorName).fg), Qt::ForegroundRole);
        ui->color->setItemData(index, QBrush(color_from_string(colorName).bg), Qt::BackgroundRole);
        index++;
    }
}

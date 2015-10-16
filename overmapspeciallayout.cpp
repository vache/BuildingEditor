#include "overmapspeciallayout.h"
#include "ui_overmapspeciallayout.h"

#include <QDebug>

QVariant LayoutModel::data(const QModelIndex &index, int role) const
{
    bool activeIndex = _activeOvermaps[Index(index)];

    switch (role)
    {
    case Qt::DisplayRole:
        return (activeIndex) ? "X" : " ";
    case Qt::UserRole:
        return activeIndex;
    default:
        break;
    }

    //return activeIndex;
    return QVariant();
}

bool LayoutModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::UserRole)
    {
        _activeOvermaps[Index(index)] = value.toBool();
        emit dataChanged(index, index);
    }
    return true;
}

OvermapSpecialLayout::OvermapSpecialLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OvermapSpecialLayout)
{
    ui->setupUi(this);

    _layoutModel = new LayoutModel();
    ui->layoutTable->setModel(_layoutModel);

    connect(ui->zLevelSlider, SIGNAL(valueChanged(int)), this, SLOT(ZLevelChanged(int)));
    connect(ui->layoutTable, SIGNAL(clicked(QModelIndex)), this, SLOT(ModelClicked(QModelIndex)));
    connect(ui->zLevelSlider, SIGNAL(valueChanged(int)), _layoutModel, SLOT(ZLevelChanged(int)));
}

OvermapSpecialLayout::~OvermapSpecialLayout()
{
    delete ui;
}

void OvermapSpecialLayout::ZLevelChanged(int zLevel)
{
    ui->zLevelValue->setText(QString::number(zLevel));
}

void OvermapSpecialLayout::ModelClicked(QModelIndex index)
{
    bool enabled = _layoutModel->data(index, Qt::UserRole).toBool();
    _layoutModel->setData(index, !enabled, Qt::UserRole);
}

void OvermapSpecialLayout::DumpLayout()
{
    QVector<bool> layout = _layoutModel->GetLayout();

    for (int z = 10; z >= -10; z--)
    {
        for (int y = 0; y <= 9; y++)
        {
            QString row = "";
            for (int x = 0; x <= 9; x++)
            {
                int index = ((10 - z) * 9 * 9) + (9 * y) + x;

                row.append((layout[index]) ? "X" : " ");
            }
            qDebug() << row;
        }
        qDebug() << "-----------------------";
    }
}

void OvermapSpecialLayout::SetZLevelsEnabled(bool enabled)
{
    _layoutModel->EnablePositiveZ(enabled);
    if (enabled)
    {
        ui->zLevelSlider->setMaximum(10);
    }
    else
    {
        ui->zLevelSlider->setMaximum(0);
    }
}

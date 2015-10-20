#include "overmapspeciallayout.h"
#include "ui_overmapspeciallayout.h"

#include "common.h"
#include <QDebug>

LayoutModel::LayoutModel()
{
    int size = 21 * rowCount() * columnCount();
    _overmapsData.fill(OMTData(), size);
    _activeOvermaps.fill(false, size);
    _z = 0;
}

QVariant LayoutModel::data(const QModelIndex &index, int role) const
{
    bool activeIndex = _activeOvermaps[Index(index)];
    OMTData data = _overmapsData.at(Index(index));

    switch (role)
    {
    case Qt::DisplayRole:
    {
        //return (activeIndex) ? "X" : " ";
        int sym = data.GetSymbols()[0];
        QChar displayChar(sym);
        if (sym >= 4194410)
        {
            displayChar = lineDrawingChars.at(lineDrawingSyms.indexOf(sym));
        }
        return displayChar;
    }
    case Qt::BackgroundRole:
        return QBrush(color_from_string(data.GetColor()).bg);
    case Qt::ForegroundRole:
        return QBrush(color_from_string(data.GetColor()).fg);
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
        _activeOvermaps[Index(index)] = true;
        _overmapsData[Index(index)] = value.value<OMTData>();
        emit dataChanged(index, index);
    }
    return true;
}

bool LayoutModel::eraseData(const QModelIndex &index, int role)
{
    if (role == Qt::UserRole)
    {
        _activeOvermaps[Index(index)] = false;
        _overmapsData[Index(index)] = OMTData();
        emit dataChanged(index, index);
    }
    return true;
}

// set +Z overmap terrains as false/default
void LayoutModel::EnablePositiveZ(bool enabled)
{
    if (!enabled)
    {
        for (int index = 0; index < 10 * 9 * 9; index++)
        {
            _activeOvermaps.replace(index, false);
            _overmapsData.replace(index, OMTData());
        }
    }
}

OvermapSpecialLayout::OvermapSpecialLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OvermapSpecialLayout)
{
    ui->setupUi(this);

    _layoutModel = new LayoutModel();
    ui->layoutTable->setModel(_layoutModel);

    connect(ui->zLevelSlider, SIGNAL(valueChanged(int)), this, SLOT(ZLevelChanged(int)));
    //connect(ui->layoutTable, SIGNAL(clicked(QModelIndex)), this, SLOT(ModelClicked(QModelIndex)));
    connect(ui->zLevelSlider, SIGNAL(valueChanged(int)), _layoutModel, SLOT(ZLevelChanged(int)));

    connect(ui->apply, SIGNAL(clicked(bool)), this, SLOT(OnApply()));
    connect(ui->reset, SIGNAL(clicked(bool)), this, SLOT(OnReset()));

    ui->omtWidget->SetMini(true);
}

OvermapSpecialLayout::~OvermapSpecialLayout()
{
    delete ui;
}

void OvermapSpecialLayout::ZLevelChanged(int zLevel)
{
    ui->zLevelValue->setText(QString::number(zLevel));
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
        qDebug() << "---------";
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

void OvermapSpecialLayout::OnApply()
{
    foreach(QModelIndex index, ui->layoutTable->selectionModel()->selectedIndexes())
    {
        _layoutModel->setData(index, QVariant::fromValue<OMTData>(ui->omtWidget->GetOMTData()), Qt::UserRole);
    }
    emit LayoutChanged();
}

void OvermapSpecialLayout::OnReset()
{
    foreach(QModelIndex index, ui->layoutTable->selectionModel()->selectedIndexes())
    {
        _layoutModel->eraseData(index, Qt::UserRole);
    }
    emit LayoutChanged();
}

void OvermapSpecialLayout::RotateToggled(bool rotate)
{
    ui->omtWidget->OnRotateClicked(rotate);
}

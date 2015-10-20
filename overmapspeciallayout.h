#ifndef OVERMAPSPECIALLAYOUT_H
#define OVERMAPSPECIALLAYOUT_H

#include <QWidget>
#include <QAbstractTableModel>
#include <QVector>

#include "omtwidget.h"
#include "omtdata.h"

// TODO magic numbers.
class LayoutModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    LayoutModel();
    ~LayoutModel() {}
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool eraseData(const QModelIndex &index, int role);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override { Q_UNUSED(parent); return 9; }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { Q_UNUSED(parent); return 9; }

    QVector<bool> GetLayout() const { return _activeOvermaps; }
    QVector<OMTData> GetOvermapsData() const { return _overmapsData; }
    void EnablePositiveZ(bool enabled);

public slots:
    void ZLevelChanged(int zLevel) { _z = zLevel; emit dataChanged(index(0,0), index(9,9)); }
private:
    int Index(const QModelIndex &index) const
        { return ((10 - _z) * rowCount() * columnCount()) + index.row() * columnCount() + index.column(); }
    QVector<bool> _activeOvermaps;
    QVector<OMTData> _overmapsData;
    int _z;
};

namespace Ui {
class OvermapSpecialLayout;
}

class OvermapSpecialLayout : public QWidget
{
    Q_OBJECT

public:
    explicit OvermapSpecialLayout(QWidget *parent = 0);
    ~OvermapSpecialLayout();
    void DumpLayout();
    void SetZLevelsEnabled(bool enabled);
    QVector<bool> GetLayout() const { return _layoutModel->GetLayout(); }
    QVector<OMTData> GetOvermapsData() const { return _layoutModel->GetOvermapsData(); }

public slots:
    void RotateToggled(bool rotate);

private slots:
    void ZLevelChanged(int zLevel);
    void OnApply();
    void OnReset();

private:
    Ui::OvermapSpecialLayout *ui;
    LayoutModel* _layoutModel;

signals:
    void LayoutChanged();
};

#endif // OVERMAPSPECIALLAYOUT_H

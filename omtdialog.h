#ifndef OMTDIALOG_H
#define OMTDIALOG_H

#include <QDialog>
#include <QString>
#include "colors.h"
#include "omtdata.h"
#include "buildingmodel.h"

namespace Ui {
class OMTDialog;
}

class OMTDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OMTDialog(QWidget *parent = 0);
    ~OMTDialog();

    void SetOMTData(OMTData omtData);
    OMTData GetOMTData() const { return _data; }
    void SetModel(BuildingModel* model) { _model = model; }

public slots:
    void AddOMTData(OMTData data);

private slots:
    void OnOMTListChanged();
    void SetReadOnly(bool readOnly);

    void OnIDChanged(QString id) { _data.SetID(id); }
    void OnNameChanged(QString name) { _data.SetName(name); }
    void OnRotateChanged(bool rotate) { _data.SetRotate(rotate); }
    void OnKnownUpChanged(bool knownUp) { _data.SetKnownUp(knownUp); }
    void OnKnownDownChanged(bool knownDown) { _data.SetKnownDown(knownDown); }
    void OnExtrasChanged(QString extras) { _data.SetExtras(extras); }
    void OnSeeCostChanged(int seeCost) { _data.SetSeeCost(seeCost); }
    void OnColorIndexChanged();
    void OnSidewalkChanged(bool sidewalk) { _data.SetSidewalk(sidewalk); }
    void OnAllowRoadChanged(bool allowRoad) { _data.SetAllowRoads(allowRoad); }
    void OnSymbolChanged();

    void ApplyDataToModel();

    void OnPrevOMT();
    void OnNextOMT();

private:
    Ui::OMTDialog *ui;

    void InitColorList();
    void InitSymList();

    OMTData _data;

    // TODO fix all the naked pointers.  use shared pointers for the models?
    BuildingModel* _model;
    int _currentOmtIndex;
};

#endif // OMTDIALOG_H

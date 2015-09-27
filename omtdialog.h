#ifndef OMTDIALOG_H
#define OMTDIALOG_H

#include <QDialog>
#include <QString>
#include "colors.h"
#include "omtdata.h"

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

private:
    Ui::OMTDialog *ui;

    void InitColorList();

    OMTData _data;
};

#endif // OMTDIALOG_H

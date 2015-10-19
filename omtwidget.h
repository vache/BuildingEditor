#ifndef OMTWIDGET_H
#define OMTWIDGET_H

#include <QWidget>
#include "omtdata.h"

namespace Ui {
class OMTWidget;
}

class OMTWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OMTWidget(QWidget *parent = 0);
    ~OMTWidget();

    void SetMini(bool mini);
    bool GetMini() const { return _mini; }

    void SetOMTData(OMTData data);
    OMTData GetOMTData() const;

public slots:
    void OnRotateClicked(bool rotate);

private:
    Ui::OMTWidget *ui;

    bool _mini;

    void InitSymList();
    void InitColorList();

signals:
    void OMTModified();
};

#endif // OMTWIDGET_H

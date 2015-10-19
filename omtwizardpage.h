#ifndef OMTWIZARDPAGE_H
#define OMTWIZARDPAGE_H

#include <QWizardPage>
#include "omtdata.h"

namespace Ui {
class OMTWizardPage;
}

class OMTWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit OMTWizardPage(QWidget *parent = 0);
    ~OMTWizardPage();

    OMTData GetOMTData() const;

private:
    Ui::OMTWizardPage *ui;

    bool isComplete() const override;
};

#endif // OMTWIZARDPAGE_H

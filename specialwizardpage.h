#ifndef SPECIALWIZARDPAGE_H
#define SPECIALWIZARDPAGE_H

#include <QWizardPage>
#include "overmapspecialdata.h"

namespace Ui {
class SpecialWizardPage;
}

class SpecialWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit SpecialWizardPage(QWidget *parent = 0);
    ~SpecialWizardPage();

    QVector<bool> GetLayout();
    OvermapSpecialData GetData();

private:
    Ui::SpecialWizardPage *ui;

    void initializePage() override;
};

#endif // SPECIALWIZARDPAGE_H

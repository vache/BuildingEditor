#ifndef SPECIALWIZARDPAGE_H
#define SPECIALWIZARDPAGE_H

#include <QWizardPage>

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

private:
    Ui::SpecialWizardPage *ui;

    void initializePage() override;
};

#endif // SPECIALWIZARDPAGE_H

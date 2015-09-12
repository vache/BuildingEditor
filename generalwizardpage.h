#ifndef GENERALWIZARDPAGE_H
#define GENERALWIZARDPAGE_H

#include <QWizardPage>

namespace Ui {
class GeneralWizardPage;
}

class GeneralWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit GeneralWizardPage(QWidget *parent = 0);
    ~GeneralWizardPage();

private:
    Ui::GeneralWizardPage *ui;
};

#endif // GENERALWIZARDPAGE_H

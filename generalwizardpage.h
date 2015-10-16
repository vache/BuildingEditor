#ifndef GENERALWIZARDPAGE_H
#define GENERALWIZARDPAGE_H

#include <QWizardPage>
#include <QListWidgetItem>

namespace Ui {
class GeneralWizardPage;
}

class GeneralWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit GeneralWizardPage(QWidget *parent = 0);
    ~GeneralWizardPage();

    int nextId() const override;
    bool isComplete() const override;
    bool isFinalPage() const;

private slots:
    void SetLastPage(bool last);
    void OnBrowse();

    void LoadModList(QString);
    void EnableSelectedMods();
    void DisableSelectedMods();
    void EnableSelectedMod(QListWidgetItem*);
    void DisableSelectedMod(QListWidgetItem*);

private:
    void initializePage() override;

    Ui::GeneralWizardPage *ui;
};

#endif // GENERALWIZARDPAGE_H

#include "omtwidget.h"
#include "ui_omtwidget.h"

#include "common.h"
#include "colors.h"

OMTWidget::OMTWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OMTWidget)
{
    ui->setupUi(this);

    InitSymList();
    InitColorList();

    connect(ui->rotate, SIGNAL(toggled(bool)), this, SLOT(OnRotateClicked(bool)));

    connect(ui->omtID, SIGNAL(textChanged(QString)), this, SIGNAL(OMTModified()));
    connect(ui->omtName, SIGNAL(textChanged(QString)), this, SIGNAL(OMTModified()));
    connect(ui->symbol1, SIGNAL(currentIndexChanged(int)), this, SIGNAL(OMTModified()));
}

OMTWidget::~OMTWidget()
{
    delete ui;
}

void OMTWidget::SetMini(bool mini)
{
    ui->label_3->setHidden(mini);
    ui->rotate->setHidden(mini);
    ui->label_9->setHidden(mini);
    ui->knownDown->setHidden(mini);
    ui->label_10->setHidden(mini);
    ui->knownUp->setHidden(mini);
    ui->label_13->setHidden(mini);
    ui->allowRoad->setHidden(mini);
    ui->label_2->setHidden(mini);
    ui->omtID->setHidden(mini);
}

// sets all the ui values to match the data
void OMTWidget::SetOMTData(OMTData data)
{
    ui->omtID->setText(data.GetID());
    ui->omtName->setText(data.GetName());
    ui->color->setCurrentIndex(ui->color->findData(data.GetColor()));
    ui->allowRoad->setChecked(data.GetAllowedRoad());
    ui->extras->setCurrentText(data.GetExtras());
    ui->knownDown->setChecked(data.GetKnownDown());
    ui->knownUp->setChecked(data.GetKnownUp());
    ui->rotate->setChecked(data.GetRotates());
    ui->seeCost->setValue(data.GetSeeCost());
    ui->sidewalk->setChecked(data.GetSidewalk());
    if (data.GetSymbols().size() == 4)
    {
        ui->symbol1->setCurrentIndex(ui->symbol1->findData(data.GetSymbols()[0]));
        ui->symbol2->setCurrentIndex(ui->symbol2->findData(data.GetSymbols()[1]));
        ui->symbol3->setCurrentIndex(ui->symbol3->findData(data.GetSymbols()[2]));
        ui->symbol4->setCurrentIndex(ui->symbol4->findData(data.GetSymbols()[3]));
    }
    else
    {
        ui->symbol1->setCurrentIndex(ui->symbol1->findData(data.GetSymbols()[0]));
        ui->symbol2->setCurrentIndex(0);
        ui->symbol3->setCurrentIndex(0);
        ui->symbol4->setCurrentIndex(0);
    }
}

// pulls all ui values into data object
OMTData OMTWidget::GetOMTData() const
{
    OMTData data;
    data.SetID(ui->omtID->text());
    data.SetName(ui->omtName->text());
    data.SetAllowRoads(ui->allowRoad->isChecked());
    data.SetRotate(ui->rotate->isChecked());
    data.SetKnownDown(ui->knownDown->isChecked());
    data.SetKnownUp(ui->knownUp->isChecked());
    data.SetSidewalk(ui->sidewalk->isChecked());
    data.SetExtras(ui->extras->currentText());
    data.SetSeeCost(ui->seeCost->value());
    data.SetColor(ui->color->currentData().toString());
    QList<int> symbols;
    int symbol1 = ui->symbol1->currentData().toInt();
    int symbol2 = ui->symbol2->currentData().toInt();
    int symbol3 = ui->symbol3->currentData().toInt();
    int symbol4 = ui->symbol4->currentData().toInt();
    if (data.GetRotates() && symbol1 != 32 && symbol2 != 32 &&
        symbol3 != 32 && symbol4 != 32)
    {
        symbols.append(symbol1);
        symbols.append(symbol2);
        symbols.append(symbol3);
        symbols.append(symbol4);
    }
    else
    {
        symbols.append(symbol1);
    }
    data.SetSymbols(symbols);

    return data;
}

void OMTWidget::OnRotateClicked(bool rotate)
{
    ui->symbol2->setEnabled(rotate);
    ui->symbol3->setEnabled(rotate);
    ui->symbol4->setEnabled(rotate);
}

void OMTWidget::InitSymList()
{
    ui->symbol1->clear();
    ui->symbol2->clear();
    ui->symbol3->clear();
    ui->symbol4->clear();

    for (int i = 32; i < 127; i++)
    {
        ui->symbol1->addItem(QChar(i), i);
        ui->symbol2->addItem(QChar(i), i);
        ui->symbol3->addItem(QChar(i), i);
        ui->symbol4->addItem(QChar(i), i);
    }
    for (int i = 0; i < lineDrawingChars.count(); i++)
    {
        ui->symbol1->addItem(lineDrawingChars[i], lineDrawingSyms[i]);
        ui->symbol2->addItem(lineDrawingChars[i], lineDrawingSyms[i]);
        ui->symbol3->addItem(lineDrawingChars[i], lineDrawingSyms[i]);
        ui->symbol4->addItem(lineDrawingChars[i], lineDrawingSyms[i]);
    }
}

void OMTWidget::InitColorList()
{
    ui->color->clear();
    int index = 0;
    foreach (QString colorName, colorList)
    {
        ui->color->insertItem(index, colorName.replace("_", " "), colorName);
        ui->color->setItemData(index, QBrush(color_from_string(colorName).fg), Qt::ForegroundRole);
        ui->color->setItemData(index, QBrush(color_from_string(colorName).bg), Qt::BackgroundRole);
        index++;
    }
}

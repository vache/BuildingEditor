#include "omtdialog.h"
#include "ui_omtdialog.h"

OMTDialog::OMTDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OMTDialog), _data(OMTData()), _currentOmtIndex(0)
{
    ui->setupUi(this);

    ui->omtList->addItem("New OMT", QVariant::fromValue(OMTData()));

    connect(ui->rotate, SIGNAL(clicked(bool)), ui->symbol2, SLOT(setEnabled(bool)));
    connect(ui->rotate, SIGNAL(clicked(bool)), ui->symbol3, SLOT(setEnabled(bool)));
    connect(ui->rotate, SIGNAL(clicked(bool)), ui->symbol4, SLOT(setEnabled(bool)));

    connect(ui->omtID, SIGNAL(textChanged(QString)), this, SLOT(OnIDChanged(QString)));
    connect(ui->omtName, SIGNAL(textChanged(QString)), this, SLOT(OnNameChanged(QString)));
    connect(ui->rotate, SIGNAL(toggled(bool)), this, SLOT(OnRotateChanged(bool)));
    connect(ui->knownDown, SIGNAL(toggled(bool)), this, SLOT(OnKnownDownChanged(bool)));
    connect(ui->knownUp, SIGNAL(toggled(bool)), this, SLOT(OnKnownUpChanged(bool)));
    connect(ui->extras, SIGNAL(currentTextChanged(QString)), this, SLOT(OnExtrasChanged(QString)));
    connect(ui->seeCost, SIGNAL(valueChanged(int)), this, SLOT(OnSeeCostChanged(int)));
    connect(ui->color, SIGNAL(currentIndexChanged(int)), this, SLOT(OnColorIndexChanged()));
    connect(ui->sidewalk, SIGNAL(toggled(bool)), this, SLOT(OnSidewalkChanged(bool)));
    connect(ui->allowRoad, SIGNAL(toggled(bool)), this, SLOT(OnAllowRoadChanged(bool)));
    connect(ui->symbol1, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSymbolChanged()));
    connect(ui->symbol2, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSymbolChanged()));
    connect(ui->symbol3, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSymbolChanged()));
    connect(ui->symbol4, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSymbolChanged()));

    connect(ui->omtList, SIGNAL(currentIndexChanged(int)), this, SLOT(OnOMTListChanged()));

    connect(ui->prev, SIGNAL(clicked(bool)), this, SLOT(OnPrevOMT()));
    connect(ui->next, SIGNAL(clicked(bool)), this, SLOT(OnNextOMT()));

    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked(bool)),
        this, SLOT(ApplyDataToModel()));
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)),
        this, SLOT(ApplyDataToModel()));

    InitColorList();
    InitSymList();
}

OMTDialog::~OMTDialog()
{
    delete ui;
}

void OMTDialog::SetOMTData(OMTData omtData)
{
    _data = omtData;

    SetReadOnly(_data.IsReadOnly());

    ui->omtID->setText(_data.GetID());
    ui->omtName->setText(_data.GetName());
    ui->rotate->setChecked(_data.GetRotates());
    ui->extras->setCurrentText(_data.GetExtras());
    ui->knownDown->setChecked(_data.GetKnownDown());
    ui->knownUp->setChecked(_data.GetKnownUp());
    ui->color->setCurrentIndex(ui->color->findData(_data.GetColor()));
    ui->sidewalk->setChecked(_data.GetSidewalk());
    ui->allowRoad->setCheckable(_data.GetAllowedRoad());
    ui->symbol1->setCurrentIndex(ui->symbol1->findData(_data.GetSymbols()[0]));
    if (_data.GetSymbols().count() == 4)
    {
        ui->symbol2->setCurrentIndex(ui->symbol1->findData(_data.GetSymbols()[1]));
        ui->symbol3->setCurrentIndex(ui->symbol1->findData(_data.GetSymbols()[2]));
        ui->symbol4->setCurrentIndex(ui->symbol1->findData(_data.GetSymbols()[3]));
    }
    else
    {
        ui->symbol2->setCurrentIndex(0);
        ui->symbol3->setCurrentIndex(0);
        ui->symbol4->setCurrentIndex(0);
    }

}

void OMTDialog::AddOMTData(OMTData data)
{
    ui->omtList->addItem(data.GetID(), QVariant::fromValue(data));
}

void OMTDialog::OnOMTListChanged()
{
    SetOMTData(ui->omtList->currentData().value<OMTData>());
}

void OMTDialog::SetReadOnly(bool readOnly)
{
    ui->omtID->setDisabled(readOnly);
    ui->omtName->setDisabled(readOnly);
    ui->rotate->setDisabled(readOnly);
    ui->color->setDisabled(readOnly);
    ui->extras->setDisabled(readOnly);
    ui->seeCost->setDisabled(readOnly);
    ui->knownDown->setDisabled(readOnly);
    ui->knownUp->setDisabled(readOnly);
    ui->allowRoad->setDisabled(readOnly);
    ui->sidewalk->setDisabled(readOnly);
    ui->symbol1->setDisabled(readOnly);
    ui->symbol2->setDisabled(readOnly);
    ui->symbol3->setDisabled(readOnly);
    ui->symbol4->setDisabled(readOnly);
}

void OMTDialog::OnColorIndexChanged()
{
    QString color = ui->color->currentData().toString();
    _data.SetColor(color);
}

void OMTDialog::OnSymbolChanged()
{
    QList<int> symbols;
    int symbol1 = ui->symbol1->currentData().toInt();
    int symbol2 = ui->symbol2->currentData().toInt();
    int symbol3 = ui->symbol3->currentData().toInt();
    int symbol4 = ui->symbol4->currentData().toInt();

    // first symbol is required
    if (symbol1 == 32)
    {
        return;
    }
    symbols.append(symbol1);

    // if it rotates, it can either have 1 or 4 symbols
    if (_data.GetRotates() && symbol2 != 32 && symbol3 != 32 && symbol4 != 32)
    {
        symbols.append(symbol2);
        symbols.append(symbol3);
        symbols.append(symbol4);
    }
    _data.SetSymbols(symbols);
}

void OMTDialog::InitColorList()
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
/*
line drawing values:
SE: 4194412
NE: 4194413
SW: 4194411
NW: 4194410
horizontal line: 4194417
vertical line: 4194424
cross: 4194414
NSW: 4194421
NES: 4194420
WES: 4194423
NEW: 4194422
*/
void OMTDialog::InitSymList()
{
    for (int i = 32; i < 127; i++)
    {
        ui->symbol1->addItem(QChar(i), i);
        ui->symbol2->addItem(QChar(i), i);
        ui->symbol3->addItem(QChar(i), i);
        ui->symbol4->addItem(QChar(i), i);
    }
    // drawing characters
    static QList<QChar> lineDrawingChars = { 0x2502, 0x2500, 0x2514, 0x2518, 0x250C, 0x2510, 0x251C, 0x2524, 0x2534, 0x252C, 0x253C };
    // values needed for the sym entry in overmap_terrain
    static QList<int> lineDrawingSyms = { 4194424, 4194417, 4194413, 4194410, 4194412, 4194411, 4194420, 4194421, 4194422, 4194423, 4194414 };
    for (int i = 0; i < lineDrawingChars.count(); i++)
    {
        ui->symbol1->addItem(lineDrawingChars[i], lineDrawingSyms[i]);
        ui->symbol2->addItem(lineDrawingChars[i], lineDrawingSyms[i]);
        ui->symbol3->addItem(lineDrawingChars[i], lineDrawingSyms[i]);
        ui->symbol4->addItem(lineDrawingChars[i], lineDrawingSyms[i]);
    }
}

void OMTDialog::ApplyDataToModel()
{
    _model->GetActiveOvermapTerrains()[_currentOmtIndex]->SetData(GetOMTData());
}

void OMTDialog::OnPrevOMT()
{
    int count = _model->GetActiveOvermapTerrains().count();

    ApplyDataToModel();

    _currentOmtIndex--;
    if (_currentOmtIndex == -1)
    {
        _currentOmtIndex = count - 1;
    }
    ui->currentOMT->setText(QString("(%1/%2)").arg(_currentOmtIndex + 1).arg(count));

    SetOMTData(_model->GetActiveOvermapTerrains().at(_currentOmtIndex)->GetData());
}

void OMTDialog::OnNextOMT()
{
    int count = _model->GetActiveOvermapTerrains().count();

    ApplyDataToModel();

    _currentOmtIndex++;
    if (_currentOmtIndex == count)
    {
        _currentOmtIndex = 0;
    }
    ui->currentOMT->setText(QString("(%1/%2)").arg(_currentOmtIndex + 1).arg(count));

    SetOMTData(_model->GetActiveOvermapTerrains().at(_currentOmtIndex)->GetData());
}

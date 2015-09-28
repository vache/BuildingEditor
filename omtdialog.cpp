#include "omtdialog.h"
#include "ui_omtdialog.h"

OMTDialog::OMTDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OMTDialog), _data(OMTData()), _currentOmtIndex(0)
{
    ui->setupUi(this);

    ui->omtList->addItem("New OMT", QVariant::fromValue(OMTData()));

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

    connect(ui->omtList, SIGNAL(currentIndexChanged(int)), this, SLOT(OnOMTListChanged()));

    connect(ui->prev, SIGNAL(clicked(bool)), this, SLOT(OnPrevOMT()));
    connect(ui->next, SIGNAL(clicked(bool)), this, SLOT(OnNextOMT()));

    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked(bool)),
        this, SLOT(OnApplyClicked()));
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)),
        this, SLOT(OnApplyClicked()));

    InitColorList();
}

OMTDialog::~OMTDialog()
{
    delete ui;
}

void OMTDialog::SetOMTData(OMTData omtData)
{
    _data = omtData;

    SetReadOnly(_data.IsReadOnly());

    if (_data.IsReadOnly())
    {
        ui->omtList->setCurrentText(_data.GetID());
    }

    ui->omtID->setText(_data.GetID());
    ui->omtName->setText(_data.GetName());
    ui->rotate->setChecked(_data.GetRotates());
    ui->extras->setCurrentText(_data.GetExtras());
    ui->knownDown->setChecked(_data.GetKnownDown());
    ui->knownUp->setChecked(_data.GetKnownUp());
    ui->color->setCurrentIndex(ui->color->findData(_data.GetColor()));
    ui->sidewalk->setChecked(_data.GetSidewalk());
    ui->allowRoad->setCheckable(_data.GetAllowedRoad());
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
}

void OMTDialog::OnApplyClicked()
{
    _model->GetActiveOvermapTerrains()[_currentOmtIndex]->SetData(GetOMTData());
}

void OMTDialog::OnColorIndexChanged()
{
    QString color = ui->color->currentData().toString();
    _data.SetColor(color);
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

void OMTDialog::OnPrevOMT()
{
    int count = _model->GetActiveOvermapTerrains().count();

    _model->GetActiveOvermapTerrains()[_currentOmtIndex]->SetData(GetOMTData());

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

    _model->GetActiveOvermapTerrains()[_currentOmtIndex]->SetData(GetOMTData());

    _currentOmtIndex++;
    if (_currentOmtIndex == count)
    {
        _currentOmtIndex = 0;
    }
    ui->currentOMT->setText(QString("(%1/%2)").arg(_currentOmtIndex + 1).arg(count));

    SetOMTData(_model->GetActiveOvermapTerrains().at(_currentOmtIndex)->GetData());
}

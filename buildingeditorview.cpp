#include "buildingeditorview.h"
#include <QDebug>
#include "buildingeditor.h"

BuildingEditorView::BuildingEditorView(QWidget *parent) :
    QTableView(parent)
{
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(OnClicked(QModelIndex)));
    connect(this, SIGNAL(entered(QModelIndex)), this, SLOT(OnClicked(QModelIndex)));
}

void BuildingEditorView::SetTool(Tool tool)
{
    _currentTool = tool;
}

void BuildingEditorView::SetFeature(Feature featureType, QString feature)
{
    _currentFeatureType = featureType;
    _currentFeature = feature;
}

void BuildingEditorView::OnClicked(const QModelIndex &index)
{
    // perform tool checking actions here
    // for now... perform a simple action:
    Terrain t("test", "test", QChar(0x253C), color_from_string("red"));
    model()->setData(index, _currentFeature, _currentFeatureType);
    switch(_currentFeatureType)
    {
    case Ter:
        qDebug() << Features::GetFeature(_currentFeature, _currentFeatureType).value<Terrain>().GetID();
        break;
    case Furn:
        qDebug() << Features::GetFeature(_currentFeature, _currentFeatureType).value<Furniture>().GetID();
        break;
    }
}

void BuildingEditorView::FeatureSelected(QListWidgetItem* item)
{
    _currentFeature = item->data(Qt::UserRole).toString();
    _currentFeatureType = item->data(FeatureTypeRole).value<Feature>();
}

#include "buildingeditorview.h"
#include <QDebug>
#include <QAction>
#include "buildingeditor.h"

BuildingEditorView::BuildingEditorView(QWidget *parent) :
    QTableView(parent), _currentTool(Pen), _currentFeature ("t_null"), _currentFeatureType(F_Terrain)
{
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(OnClicked(QModelIndex)));
    connect(this, SIGNAL(entered(QModelIndex)), this, SLOT(OnClicked(QModelIndex)));
}

void BuildingEditorView::SetTool(Tool tool)
{
    _currentTool = tool;
    qDebug() << ((_currentTool == FilledRectangle) ? "Rectangle" : "Other");
}

void BuildingEditorView::SetFeature(Feature featureType, QString feature)
{
    _currentFeatureType = featureType;
    _currentFeature = feature;
}

void BuildingEditorView::OnClicked(const QModelIndex &index)
{
    // perform tool checking actions here

    if (_currentTool == Pen)
    {
        model()->setData(index, _currentFeature, _currentFeatureType);
    }
}

void BuildingEditorView::FeatureSelected(QListWidgetItem* item)
{
    _currentFeature = item->data(Qt::UserRole).toString();
    _currentFeatureType = item->data(FeatureTypeRole).value<Feature>();
}

void BuildingEditorView::ToolChanged()
{
    QAction* s = (QAction*)sender();
    _currentTool = s->data().value<Tool>();
}

void BuildingEditorView::mousePressEvent(QMouseEvent *event)
{
    switch (_currentTool)
    {
    case Pen:
        break;
    case FilledRectangle:
    case HollowRectangle:
    {
        _rubberBandOrigin = event->pos();
        if (!_rubberBand)
        {
            _rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        }
        QRect geometry = QRect(_rubberBandOrigin, QSize());
        int headerHeight = this->horizontalHeader()->height();
        int headerWidth = this->verticalHeader()->width();
        _rubberBand->setGeometry(geometry.adjusted(headerWidth, headerHeight, headerWidth, headerWidth));
        _rubberBand->show();
        break;
    }
    case Line:
        break;
    default:
        break;
    }
}

void BuildingEditorView::mouseMoveEvent(QMouseEvent *event)
{
    if (this->rect().contains(event->pos()))
    {
        switch (_currentTool)
        {
        case Pen:
            model()->setData(indexAt(event->pos()), _currentFeature, _currentFeatureType);
            break;
        case FilledRectangle:
        case HollowRectangle:
        {
            QRect geometry = QRect(_rubberBandOrigin, event->pos()).normalized();
            int headerHeight = this->horizontalHeader()->height();
            int headerWidth = this->verticalHeader()->width();
            _rubberBand->setGeometry(geometry.adjusted(headerWidth, headerHeight, headerWidth, headerHeight));
            break;
        }
        case Line:
            break;
        default:
            break;
        }
    }
}

void BuildingEditorView::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    switch (_currentTool)
    {
    case Pen:
        model()->setData(indexAt(event->pos()), _currentFeature, _currentFeatureType);
        break;
    case FilledRectangle:
    case HollowRectangle:
    {
        int headerHeight = this->horizontalHeader()->height();
        int headerWidth = this->verticalHeader()->width();

        _rubberBand->hide();

        // rubber band draws based on the displays 0,0 as origin
        // indexes use inside corner of the headers as 0,0
        //
        // v-- this is 0,0 for rubber band
        // []=================
        // ||+<-- this is 0,0 for table fields
        // ||
        QRect selection = _rubberBand->geometry().adjusted(-headerWidth, -headerHeight, -headerWidth, -headerHeight);
        QModelIndex topLeft = this->indexAt(selection.topLeft());
        QModelIndex bottomRight = this->indexAt(selection.bottomRight());

        if (_currentTool == FilledRectangle)
        {
            for (int i = topLeft.column(); i <= bottomRight.column(); i++)
            {
                for (int j = topLeft.row(); j <= bottomRight.row(); j++)
                {
                    model()->setData(model()->index(j, i), _currentFeature, _currentFeatureType);
                }
            }
        }
        else if (_currentTool == HollowRectangle)
        {
            for (int i = topLeft.column(); i <= bottomRight.column(); i++)
            {
                model()->setData(model()->index(topLeft.row(), i), _currentFeature, _currentFeatureType);
                model()->setData(model()->index(bottomRight.row(), i), _currentFeature, _currentFeatureType);
            }
            for (int j = topLeft.row(); j <= bottomRight.row(); j++)
            {
                model()->setData(model()->index(j, topLeft.column()), _currentFeature, _currentFeatureType);
                model()->setData(model()->index(j, bottomRight.column()), _currentFeature, _currentFeatureType);
            }
        }
        break;
    }
    case Line:
        break;
    default:
        break;
    }
}
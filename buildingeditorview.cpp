#include "buildingeditorview.h"
#include <QDebug>
#include <QAction>
#include "buildingeditor.h"
#include <QMenu>

BuildingEditorView::BuildingEditorView(QWidget *parent) :
    QTableView(parent), _currentTool(Pen), _currentFeature ("t_null"), _currentFeatureType(F_Terrain),
    _rubberBand(NULL), _rubberBandOrigin(QPoint()), _eraseMode(false)
{

}

void BuildingEditorView::SetTool(Tool tool)
{
    _currentTool = tool;
}

void BuildingEditorView::SetFeature(Feature featureType, QVariant feature)
{
    _currentFeatureType = featureType;
    _currentFeature = feature;
}

void BuildingEditorView::FeatureSelected(QListWidgetItem* item)
{
    _currentFeature = item->data(Qt::UserRole);
    _currentFeatureType = item->data(FeatureTypeRole).value<Feature>();

    switch(_currentFeatureType)
    {
    case F_ItemGroup:
        qDebug() << "Feature Set To:" << _currentFeature.value<ItemGroup>().GetID() << " Type:" << _currentFeatureType;
        break;
    case F_MonsterGroup:
        qDebug() << "Feature Set To:" << _currentFeature.value<MonsterGroup>().GetID() << " Type:" << _currentFeatureType;
        break;
    case F_Vehicle:
        qDebug() << "Feature Set To:" << _currentFeature.value<Vehicle>().GetID() << " Type:" << _currentFeatureType;
        break;
    default:
        qDebug() << "Feature Set To:" << _currentFeature.toString() << " Type:" << _currentFeatureType;
    }
}

void BuildingEditorView::ToolChanged()
{
    QAction* s = (QAction*)sender();
    _currentTool = s->data().value<Tool>();
}

void BuildingEditorView::SetEraseMode(bool erase)
{
    _eraseMode = erase;
}

void BuildingEditorView::OnSelect()
{
    setCurrentIndex(_menuIndex);
    emit SelectedIndex(_menuIndex);
}

void BuildingEditorView::OnErase()
{
    emit EraseIndex(_menuIndex);
}

void BuildingEditorView::contextMenuEvent(QContextMenuEvent *event)
{
    static QMenu* menu = NULL;
    if (menu == NULL)
    {
        menu = new QMenu(this);
        //menu->addAction("Select", this, SLOT(OnSelect()));
        menu->addAction("Erase All Features", this, SLOT(OnErase()));
    }
    // select passes index to model, model passes tile back to editor
    _menuIndex = indexAt(event->pos());
    menu->popup(event->globalPos());
}

void BuildingEditorView::mousePressEvent(QMouseEvent *event)
{
    // reset the selection
    setCurrentIndex(QModelIndex());

    if (event->buttons().testFlag(Qt::RightButton))
    {
        return;
    }

    switch (_currentTool)
    {
    case Pen:
    {
        if (!_eraseMode)
        {
            model()->setData(indexAt(event->pos()), _currentFeature, _currentFeatureType);
        }
        else
        {
            BuildingModel* m = dynamic_cast<BuildingModel*>(model());
            if (m != NULL)
            {
                m->Erase(indexAt(event->pos()), _currentFeatureType);
            }
        }
        break;
    }
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
    if (event->buttons().testFlag(Qt::RightButton))
    {
        return;
    }

    if (this->rect().contains(event->pos()))
    {
        switch (_currentTool)
        {
        case Pen:
        {
            if (!_eraseMode)
            {
                model()->setData(indexAt(event->pos()), _currentFeature, _currentFeatureType);
            }
            else
            {
                BuildingModel* m = dynamic_cast<BuildingModel*>(model());
                if (m != NULL)
                {
                    m->Erase(indexAt(event->pos()), _currentFeatureType);
                }
            }
            break;
        }
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
    if (event->buttons().testFlag(Qt::RightButton))
    {
        return;
    }

    switch (_currentTool)
    {
    case Pen:
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

        BuildingModel* m = NULL;
        if (_eraseMode)
        {
            m = dynamic_cast<BuildingModel*>(model());
        }

        if (_currentTool == FilledRectangle)
        {
            for (int i = topLeft.column(); i <= bottomRight.column(); i++)
            {
                for (int j = topLeft.row(); j <= bottomRight.row(); j++)
                {
                    if (!_eraseMode)
                    {
                        model()->setData(model()->index(j, i), _currentFeature, _currentFeatureType);
                    }
                    else if (m != NULL)
                    {
                        m->Erase(model()->index(j, i), _currentFeatureType);
                    }
                }
            }
        }
        else if (_currentTool == HollowRectangle)
        {
            for (int i = topLeft.column(); i <= bottomRight.column(); i++)
            {
                if (!_eraseMode)
                {
                    model()->setData(model()->index(topLeft.row(), i), _currentFeature, _currentFeatureType);
                    model()->setData(model()->index(bottomRight.row(), i), _currentFeature, _currentFeatureType);
                }
                else if (m != NULL)
                {
                    m->Erase(model()->index(topLeft.row(), i), _currentFeatureType);
                    m->Erase(model()->index(bottomRight.row(), i), _currentFeatureType);
                }
            }
            for (int j = topLeft.row(); j <= bottomRight.row(); j++)
            {
                if (!_eraseMode)
                {
                    model()->setData(model()->index(j, topLeft.column()), _currentFeature, _currentFeatureType);
                    model()->setData(model()->index(j, bottomRight.column()), _currentFeature, _currentFeatureType);
                }
                else if (m != NULL)
                {
                    m->Erase(model()->index(j, topLeft.column()), _currentFeatureType);
                    m->Erase(model()->index(j, bottomRight.column()), _currentFeatureType);
                }
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

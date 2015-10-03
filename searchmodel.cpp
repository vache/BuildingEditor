#include "searchmodel.h"
#include "features.h"

#include <QDebug>

SearchModel::SearchModel(QObject *parent) : QAbstractTableModel(parent)
{

}

SearchModel::~SearchModel()
{

}

int SearchModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return _searchResults.count();
}

int SearchModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 2;
}

QVariant SearchModel::data(const QModelIndex &index, int role) const
{
    QListWidgetItem* item = _searchResults[index.row()];

    switch(role)
    {
    case Qt::DisplayRole:
    {
        QString display = "";
        if (index.column() == 0)
        {
            display = item->text();
        }
        else
        {
            display = Features::TypeName(item->data(FeatureTypeRole).value<Feature>());
        }
        return display;
    }
    case Qt::ForegroundRole:
        return QBrush(Qt::black);
    case Qt::BackgroundRole:
        return QBrush(Qt::white);
    default:
        return QVariant();
    }
}

QVariant SearchModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            if (section == 0)
            {
                return "Name";
            }
            else if (section == 1)
            {
                return "Type";
            }
        }
    }
    else if (orientation == Qt::Vertical)
    {
        if (role == Qt::DisplayRole)
        {
            return QString::number(section + 1);
        }
    }
    return QVariant();
}

QListWidgetItem* SearchModel::GetItem(const QModelIndex &index) const
{
    return _searchResults[index.row()];
}

void SearchModel::SetSearchResults(QList<QListWidgetItem *> results)
{
    emit beginResetModel();
    _searchResults.clear();
    emit endResetModel();

    emit beginInsertRows(QModelIndex(), 0, results.count()- 1);
    _searchResults = results;
    emit endInsertRows();
}

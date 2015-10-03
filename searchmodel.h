#ifndef SEARCHMODEL_H
#define SEARCHMODEL_H

#include <QAbstractTableModel>
#include <QListWidgetItem>
#include <QList>

class SearchModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    SearchModel(QObject* parent = 0);
    ~SearchModel() override;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QListWidgetItem* GetItem(const QModelIndex &index) const;

signals:

public slots:
    void SetSearchResults(QList<QListWidgetItem*> results);

private:
    QList<QListWidgetItem*> _searchResults;
};

#endif // SEARCHMODEL_H

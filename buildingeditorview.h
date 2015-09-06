#ifndef BUILDINGEDITORVIEW_H
#define BUILDINGEDITORVIEW_H

#include <QTableView>
#include <QListWidgetItem>
#include "buildingmodel.h"
#include "features.h"

enum Tool { Pen, FilledRectangle, HollowRectangle, Line };
Q_DECLARE_METATYPE(Tool)

class BuildingEditorView : public QTableView
{
    Q_OBJECT
public:
    explicit BuildingEditorView(QWidget *parent = 0);

signals:

public slots:
    void SetTool(Tool tool);
    void SetFeature(Feature featureType, QString feature);
    void FeatureSelected(QListWidgetItem* item);

private slots:
    void OnClicked(const QModelIndex & index);

private:
    Tool _currentTool;
    Feature _currentFeatureType;
    QString _currentFeature;
};

#endif // BUILDINGEDITORVIEW_H

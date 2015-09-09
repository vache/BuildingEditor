#ifndef BUILDINGEDITORVIEW_H
#define BUILDINGEDITORVIEW_H

#include <QTableView>
#include <QListWidgetItem>
#include <QRubberBand>
#include <QMouseEvent>
#include <QRect>
#include <QPoint>
#include <QHeaderView>
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
    void ToolChanged();

private slots:
    void OnClicked(const QModelIndex & index);

private:
    Tool _currentTool;
    QString _currentFeature;
    Feature _currentFeatureType;

    QRubberBand* _rubberBand;
    QPoint _rubberBandOrigin;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // BUILDINGEDITORVIEW_H

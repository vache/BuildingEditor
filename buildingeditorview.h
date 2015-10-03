#ifndef BUILDINGEDITORVIEW_H
#define BUILDINGEDITORVIEW_H

#include <QTableView>
#include <QListWidgetItem>
#include <QRubberBand>
#include <QMouseEvent>
#include <QRect>
#include <QPoint>
#include <QHeaderView>
#include <QVariant>
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
    void SetFeature(Feature featureType, QVariant feature);
    void FeatureSelected(QListWidgetItem* item);
    void ToolChanged();
    void SetEraseMode(bool erase);

private slots:

private:
    Tool _currentTool;
    QVariant _currentFeature;
    Feature _currentFeatureType;

    QRubberBand* _rubberBand;
    QPoint _rubberBandOrigin;

    bool _eraseMode;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // BUILDINGEDITORVIEW_H

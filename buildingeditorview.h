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
    void EraseIndex(QModelIndex);
    void SelectedIndex(QModelIndex);

public slots:
    void SetTool(Tool tool);
    void SetFeature(Feature featureType, QVariant feature);
    void FeatureSelected(QListWidgetItem* item);
    void ToolChanged();
    void SetEraseMode(bool erase);

private slots:
    void OnSelect();
    void OnErase();

private:
    Tool _currentTool;
    QVariant _currentFeature;
    Feature _currentFeatureType;

    QRubberBand* _rubberBand;
    QPoint _rubberBandOrigin;

    // TODO i dont like this implementation, revisit at some point
    QModelIndex _menuIndex;

    bool _eraseMode;

    void contextMenuEvent(QContextMenuEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // BUILDINGEDITORVIEW_H

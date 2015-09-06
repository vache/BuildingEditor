#ifndef DRAWABLEITEM_H
#define DRAWABLEITEM_H

#include <QChar>
#include <QColor>
#include <QList>
#include "colors.h"

class DrawableItem
{
public:
    DrawableItem(QString id, QString desc, QChar sym, nc_color color);
    inline QChar GetSymbol() { return _symbol; }
    inline QString GetDescription() { return _description; }
    inline QString GetID() { return _id; }
    inline QColor GetBackground() { return _color.bg; }
    inline QColor GetForeground() { return _color.fg; }
    inline QList<QChar>& GetExportSymbols() { return _exportSymbols; }

private:
    QList<QChar> _exportSymbols;

    QString _id;
    QString _description;
    QChar _symbol;

    nc_color _color;
};

#endif // DRAWABLEITEM_H

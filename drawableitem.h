#ifndef DRAWABLEITEM_H
#define DRAWABLEITEM_H

#include <QChar>
#include <QColor>
#include <QList>
#include <QSet>
#include "colors.h"

class DrawableItem
{
public:
    DrawableItem();
    DrawableItem(QString id, QString desc, QChar sym, nc_color color, QSet<QString> flags);
    inline QChar GetSymbol() const { return _symbol; }
    inline QString GetDescription() const { return _description; }
    inline QString GetID() const { return _id; }
    inline QColor GetBackground() const { return _color.bg; }
    inline QColor GetForeground() const { return _color.fg; }
    inline QList<QChar> GetExportSymbols() const { return _exportSymbols; }
    inline bool HasFlag(QString flag) const { return _flags.contains(flag); }

private:
    QList<QChar> _exportSymbols;

    QString _id;
    QString _description;
    QChar _symbol;

    nc_color _color;

    QSet<QString> _flags;
};

typedef DrawableItem Terrain;
typedef DrawableItem Furniture;
typedef DrawableItem Trap;

Q_DECLARE_METATYPE(DrawableItem)

#endif // DRAWABLEITEM_H

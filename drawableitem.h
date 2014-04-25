#ifndef DRAWABLEITEM_H
#define DRAWABLEITEM_H

#include <QChar>
#include <QColor>
#include <QList>

class DrawableItem
{
public:
    DrawableItem();

    QChar _symbol;
    QList<QChar> _exportSymbols;

    QString _description;
    QString _id;

    QColor _foreground;
    QColor _background;
};

#endif // DRAWABLEITEM_H

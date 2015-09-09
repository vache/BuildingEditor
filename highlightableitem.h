#ifndef HIGHLIGHTABLEITEM_H
#define HIGHLIGHTABLEITEM_H

#include <QString>
#include <QColor>

class HighlightableItem
{
public:
    HighlightableItem(QString id, QColor background);

    inline QString GetID() const { return _id; }
    inline QColor GetBackground() const { return _background; }

protected:
    QString _id;
    QColor _background;
};

#endif // HIGHLIGHTABLEITEM_H

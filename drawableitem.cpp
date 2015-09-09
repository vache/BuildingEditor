#include "drawableitem.h"

DrawableItem::DrawableItem() : _id(""), _description(""), _symbol(' '), _color(nc_color()),
    _flags(QSet<QString>())
{

}

DrawableItem::DrawableItem(QString id, QString desc, QChar sym, nc_color color, QSet<QString> flags)
    : _id(id), _description(desc), _symbol(sym), _color(color), _flags(flags)
{
}

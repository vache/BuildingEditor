#include "drawableitem.h"

DrawableItem::DrawableItem(QString id, QString desc, QChar sym, nc_color color)
    : _id(id), _description(desc), _symbol(sym), _color(color)
{
}

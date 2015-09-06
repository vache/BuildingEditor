#include "furniture.h"

Furniture::Furniture() : DrawableItem("f_null", "invalid", QChar(' '), nc_color())
{
}

Furniture::Furniture(QString id, QString desc, QChar sym, nc_color color) :
    DrawableItem(id, desc, sym, color)
{
}

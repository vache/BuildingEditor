#include "field.h"

Field::Field() : _fieldName("fd_null"), _age(0), _density(1)
{

}

Field::Field(QString fieldName, int age, int density)
    : _fieldName(fieldName), _age(age), _density(density)
{

}

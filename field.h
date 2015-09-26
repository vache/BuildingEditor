#ifndef FIELD_H
#define FIELD_H

#include <QString>
#include <QMetaType>

class Field
{
public:
    Field();
    Field(QString fieldName, int age, int density);

    inline QString GetName() const { return _fieldName; }
    inline void SetName(QString fieldName) { _fieldName = fieldName; }

    inline int GetAge() const { return _age; }
    inline void SetAge(int age) { _age = age; }

    inline int GetDensity() const { return _density; }
    inline void SetDensity(int density) { _density = density; }

private:
    QString _fieldName;
    int _age;
    int _density;
};

Q_DECLARE_METATYPE(Field)

static Field null_field();

#endif // FIELD_H

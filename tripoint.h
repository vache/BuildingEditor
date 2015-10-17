#ifndef TRIPOINT_H
#define TRIPOINT_H

#include <QJsonArray>

class Tripoint
{
public:
    Tripoint() : _x(-1), _y(-1), _z(-1) {}
    Tripoint(int x, int y, int z);
    bool operator<(const Tripoint& other) const;
    inline int x() const { return _x; }
    inline int y() const { return _y; }
    inline int z() const { return _z; }
    inline void setX(int x) { _x = x; }
    inline void setY(int y) { _y = y; }
    inline void setZ(int z) { _z = z; }
    bool operator==(const Tripoint& other) const;
    QJsonArray ToJson() const;
private:
    int _x;
    int _y;
    int _z;
};

#endif // TRIPOINT_H

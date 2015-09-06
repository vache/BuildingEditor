#ifndef TRIPOINT_H
#define TRIPOINT_H

class Tripoint
{
public:
    Tripoint(int x, int y, int z);
    bool operator<(const Tripoint& other) const;
    inline int x() const { return _x; }
    inline int y() const { return _y; }
    inline int z() const { return _z; }
    inline void setX(int x) { _x = x; }
    inline void setY(int y) { _y = y; }
    inline void setZ(int z) { _z = z; }
private:
    int _x;
    int _y;
    int _z;
};

#endif // TRIPOINT_H

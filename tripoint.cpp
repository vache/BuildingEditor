#include "tripoint.h"

Tripoint::Tripoint(int x, int y, int z) : _x(x), _y(y), _z(z)
{
}

bool Tripoint::operator <(const Tripoint& other) const
{
    // For iterating over a qmap, (such as when exporting the omts, we want to start at the top left
    // So, top left corner should always be smallest.  Ideally, topleftmost corner, which conflicts
    // with current implementation.  Final implementation should have highest z level be smallest
    // value (for export purposes only, though im not sure what other context would need < )

    // could be simplified as:
    // if ( this.y != that.y ) return this.y < that.y
    // else if ( this.x != that.x ) return this.x < that.x
    // else return this.z < that.z

    if ( _y < other.y())
    {
        return true;
    }
    else if ( _y > other.y())
    {
        return false;
    }
    // _y == other.y()
    else if ( _x < other.x())
    {
        return true;
    }
    else if ( _x > other.x())
    {
        return false;
    }
    // _y == other.y() && _x == other.x()
    else if ( _z < other.z())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Tripoint::operator==(const Tripoint& other) const
{
    return (_x == other.x()) && (_y == other.y()) && (_z == other.z());
}

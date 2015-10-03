#ifndef COMMON_H
#define COMMON_H

#include <QList>

// NS, EW, NE, NW, ES, SW, NES, NSW, NEW, ESW, NESW
static QList<QChar> lineDrawingChars = { 0x2502, 0x2500, 0x2514, 0x2518, 0x250C, 0x2510, 0x251C, 0x2524, 0x2534, 0x252C, 0x253C };
static QList<int> lineDrawingSyms = { 4194424, 4194417, 4194413, 4194410, 4194412, 4194411, 4194420, 4194421, 4194422, 4194423, 4194414 };
// Used to index the line drawing character array
enum DirectionalLine { NS = 0, EW, NE, NW, SE, SW, NES, NSW, NEW, ESW, NESW };

/*
line drawing values:
SE: 4194412
NE: 4194413
SW: 4194411
NW: 4194410
EW: 4194417
NS: 4194424
NESW: 4194414
NSW: 4194421
NES: 4194420
WES: 4194423
NEW: 4194422
*/

#endif // COMMON_H

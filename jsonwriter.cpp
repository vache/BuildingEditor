#include "jsonwriter.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

JsonWriter::JsonWriter()
{
}

void JsonWriter::Write(BuildingModel *model)
{
    // loop through the OMTs in model
    foreach (OvermapTerrain omt, model->GetOvermapTerrains())
    {
        if (omt.IsActive())
        {
            WriteOMT(omt);
        }
    }
}

void JsonWriter::WriteOMT(OvermapTerrain t)
{
    // this is a single 24x24 OMT.  we want to loop through, determine the pairs of items, and
    // create the json, then save to file.
    // sanity check to make sure we dont process inactive OMTs
    if (!t.IsActive())
    {
        return;
    }
    // TODO verify all ids are valid (check for t_null)

    QJsonDocument doc;
    QFile jsonFile;

    QJsonObject mapgenObject;
    mapgenObject["type"] = QString("mapgen");
    mapgenObject["om_terrain"] = QString("house"); // TODO pull this from settings
    mapgenObject["method"] = QString("json");
    mapgenObject["weight"] = 100; // TODO pull this from settings

    QJsonObject object;
    QJsonArray rowsObject;

    // TODO this ENTIRE business can be moved to a method under Tile
    QList<QChar> availableChars;
    QString chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-=_+[]\{}|;',./:<>? ";
    for (int i = 0; i < chars.size(); i++)
    {
        availableChars.append(chars[i]);
    }

    /* basic idea here: tile.getexportchar should return a list instead of a single char.  should look
     * something like...
     * Tile: t_floor, f_counter
     * Desired Export Chars: '#', 'c', 'C'
     * Look for tag AUTO_WALL_SYMBOL or WALL to determine which tiles get - or |
     * Count number of tiles w/specific ter/floor/trap combinations, combos with the biggest # get
     * first pick from the available chars.  If preferred char not available, pick next in list.
     * If list is empty, just pick the next char in the available list.
     */

    // Make a list of all the tiles we've got, and make a count of the # of instances of each
    QVector<Tile> tiles;
    QVector<int> tileCount;
    QVector<Tile> sortedTiles;
    for (int row = 0; row < OVERMAP_TERRAIN_WIDTH; row++)
    {
        for (int col = 0; col < OVERMAP_TERRAIN_WIDTH; col++)
        {
            Tile tile = t.GetTile(Tripoint(col, row, 0));

            int tileIndex = tiles.indexOf(tile);
            if (tileIndex != -1)
            {
                tileCount[tileIndex]++;
            }
            else
            {
                tiles.append(tile);
                tileCount.append(1);
            }
        }
    }

    qDebug() << "Found" << tileCount.size() << "tile combinations";

    for (int i = 0; i < tileCount.size(); i++)
    {
        qDebug() << "Display Char:" << tiles[i].GetDisplayChar() << "count:" << tileCount[i];
    }

    // make a list of tiles sorted by which ones occur the most
    while (!tileCount.isEmpty())
    {
        int max = 0;
        int maxIndex = -1;
        for (int i = 0; i < tileCount.size(); i++)
        {
            if (tileCount[i] > max)
            {
                max = tileCount[i];
                maxIndex = i;
            }
        }
        sortedTiles.append(tiles[maxIndex]);
        tileCount.remove(maxIndex);
        tiles.remove(maxIndex);
    }

    for (int i = 0; i < sortedTiles.size(); i++)
    {
        qDebug() << i << ":" << sortedTiles[i].GetDisplayChar();
        qDebug() << "Preferred Characters:";
        foreach (QChar c, sortedTiles[i].GetExportChars())
        {
            qDebug() << c;
        }
    }

    // step through the list of tiles and assign export chars
    QMap<QChar, Tile> exportMap;
    for (int i = 0; i < sortedTiles.size(); i++)
    {
        bool inserted = false;
        foreach (QChar c, sortedTiles[i].GetExportChars())
        {
            if (availableChars.contains(c) && !inserted)
            {
                qDebug() << c << "is available";
                exportMap[c] = sortedTiles[i];
                availableChars.removeAll(c);
                inserted = true;

                qDebug() << "Assigned" << c << "to" << sortedTiles[i].GetTerrainID() << "," << sortedTiles[i].GetFurnitureID();
            }
        }
        if (!inserted)
        {
            if (!availableChars.isEmpty())
            {
                exportMap[availableChars[0]] = sortedTiles[i];

                qDebug() << "Assigned" << availableChars[0] << "to" << sortedTiles[i].GetTerrainID() << "," << sortedTiles[i].GetFurnitureID();

                availableChars.pop_front();
                inserted = true;
            }
        }
        if (!inserted)
        {
            qDebug() << "Error finding available character";
            return;
        }
    }

    // create the "rows"
    QStringList rows;
    for (int row = 0; row < OVERMAP_TERRAIN_WIDTH; row++)
    {
        QString rowString = "";
        for (int col = 0; col < OVERMAP_TERRAIN_WIDTH; col++)
        {
            Tile tile = t.GetTile(Tripoint(col, row, 0));

            QChar exportChar = exportMap.key(tile);

            rowString.append(exportChar);
        }
        qDebug() << rowString;
        rows.append(rowString);
    }
    rowsObject = QJsonArray::fromStringList(rows);
    object["rows"] = rowsObject;
    // TODO all the way down to about here...

    // Get list of char->id maps for terrain and furniture
    QList<QPair<QChar, QString>> terrainMappings;
    QList<QPair<QChar, QString>> furnitureMappings;
    foreach (QChar key, exportMap.keys())
    {
        terrainMappings.append(QPair<QChar, QString>(key, exportMap[key].GetTerrainID()));
        furnitureMappings.append(QPair<QChar, QString>(key, exportMap[key].GetFurnitureID()));
        qDebug() << key << ":" << exportMap[key].GetTerrainID();
        qDebug() << key << ":" << exportMap[key].GetFurnitureID();
    }

    QJsonObject jsonTerrainMap;
    QPair<QChar, QString> mapping;
    foreach (mapping, terrainMappings)
    {
        jsonTerrainMap.insert(QString(mapping.first), mapping.second);
    }
    object["terrain"] = jsonTerrainMap;

    QJsonObject jsonFurnitureMap;
    foreach (mapping, furnitureMappings)
    {
        jsonFurnitureMap.insert(QString(mapping.first), mapping.second);
    }
    object["furniture"] = jsonFurnitureMap;

    mapgenObject["object"] = object;
    doc.setObject(mapgenObject);

    qDebug() << doc.toJson();

    QString filename = QFileDialog::getSaveFileName();

    if (filename.isEmpty())
    {
        return;
    }

    jsonFile.setFileName(filename);
    jsonFile.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream ts(&jsonFile);
    ts << doc.toJson();
    ts.flush();
    jsonFile.flush();
    jsonFile.close();
}

#include "jsonwriter.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QInputDialog>
#include <QSettings>
#include <QHash>
#include <QListIterator>

int index(Tripoint p)
{
    return p.y() * OVERMAP_TERRAIN_WIDTH + p.x();
}

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

    bool ok;
    QJsonObject mapgenObject;
    mapgenObject["type"] = QString("mapgen");
    QString omter = QInputDialog::getText(0, "Enter Overmap Terrain", "Enter the ID of the overmap terrain this mapgen is for", QLineEdit::Normal, "house", &ok); // TODO pull this from settings
    if (!ok)
    {
        return;
    }
    mapgenObject["om_terrain"] = (!omter.isEmpty()) ? omter : "house";
    mapgenObject["method"] = QString("json");
    mapgenObject["weight"] = QInputDialog::getInt(0, "Enter Weight", "Enter the relative weight of this mapgen", 100, 1, 10000, 100, &ok); // TODO pull this from settings
    if (!ok)
    {
        return;
    }

    QJsonObject object;
    QJsonArray rowsObject;

    // TODO this ENTIRE business can be moved to a method under OMT
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
    // Use those two lists to make a list of tile sorted by the most common
    QVector<Tile> sortedTiles;
    // Also while in this loop, get the arrays for just about everything else...:
    QJsonArray traps;
    QJsonArray monsterGroups;
    QJsonArray itemGroups;
    QJsonArray monsters;
    QJsonArray items;
    QJsonArray vehicles;
    QJsonArray toilets;
    QJsonArray npcs;
    QJsonArray signs;
    // TODO in this loop, form the lists of monster/item groups, and possibly their respective locations?
    QHash<MonsterGroup, QVector<bool>> monsterGroupCollection;
    QHash<ItemGroup, QVector<bool>> itemGroupCollection;
    for (int row = 0; row < OVERMAP_TERRAIN_WIDTH; row++)
    {
        for (int col = 0; col < OVERMAP_TERRAIN_WIDTH; col++)
        {
            Tripoint p = Tripoint(col, row, 0);
            Tile tile = t.GetTile(p);

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

            if (tile.GetTrapID() != "tr_null")
            {
                QJsonObject trap;
                trap["y"] = row;
                trap["x"] = col;
                trap["trap"] = tile.GetTrapID();
                traps.append(trap);
            }
            if (tile.GetMonsterGroup().GetID() != "")
            {
                // this looks hideous.
                if (monsterGroupCollection.contains(tile.GetMonsterGroup()))
                {
                    monsterGroupCollection[tile.GetMonsterGroup()][index(p)] = true;
                }
                else
                {
                    monsterGroupCollection[tile.GetMonsterGroup()].resize(OVERMAP_TERRAIN_WIDTH * OVERMAP_TERRAIN_WIDTH);
                    monsterGroupCollection[tile.GetMonsterGroup()].fill(false);
                    monsterGroupCollection[tile.GetMonsterGroup()][index(p)] = true;
                }

//                QJsonObject monsterGroup;
//                monsterGroup["y"] = row;
//                monsterGroup["x"] = col;
//                monsterGroup["monster"] = tile.GetMonsterGroup().GetID();
//                monsterGroup["chance"] = tile.GetMonsterGroup().GetChance();
//                monsterGroup["density"] = tile.GetMonsterGroup().GetDensity();
//                monsterGroups.append(monsterGroup);
            }
            if (tile.GetItemGroup().GetID() != "")
            {
                // this looks hideous.
                if (itemGroupCollection.contains(tile.GetItemGroup()))
                {
                    itemGroupCollection[tile.GetItemGroup()][index(p)] = true;
                }
                else
                {
                    itemGroupCollection[tile.GetItemGroup()].resize(OVERMAP_TERRAIN_WIDTH * OVERMAP_TERRAIN_WIDTH);
                    itemGroupCollection[tile.GetItemGroup()].fill(false);
                    itemGroupCollection[tile.GetItemGroup()][index(p)] = true;
                }

//                QJsonObject itemGroup;
//                itemGroup["y"] = row;
//                itemGroup["x"] = col;
//                itemGroup["item"] = tile.GetItemGroup().GetID();
//                itemGroup["chance"] = tile.GetItemGroup().GetChance();
//                itemGroups.append(itemGroup);
            }
            if (!tile.GetItems().isEmpty())
            {
                QMap<QString, int> itemCount;
                foreach (QString i, tile.GetItems())
                {
                    if (itemCount.contains(i))
                    {
                        itemCount[i]++;
                    }
                    else
                    {
                        itemCount[i] = 1;
                    }
                }
                foreach (QString i, itemCount.keys())
                {
                    QJsonObject item;
                    item["x"] = col;
                    item["y"] = row;
                    item["item"] = i;
                    item["repeat"] = itemCount[i];
                    items.append(item);
                }
            }
            if (tile.GetMonster() != "")
            {
                QJsonObject monster;
                monster["x"] = col;
                monster["y"] = row;
                monster["monster"] = tile.GetMonster();
                //monster["friendly"] = tile.GetMonster().GetFriendly();
                //monster["name"] = tile.GetMonster().GetName();
                monsters.append(monster);
            }
            if (tile.GetVehicle().GetID() != "")
            {
                QJsonObject vehicle;
                vehicle["x"] = col;
                vehicle["y"] = row;
                vehicle["vehicle"] = tile.GetVehicle().GetID();
                vehicle["chance"] = tile.GetVehicle().GetChance();
                vehicle["status"] = tile.GetVehicle().GetStatus();
                vehicle["fuel"] = tile.GetVehicle().GetFuel();
                int direction = tile.GetVehicle().GetDirection();
                if (direction != -1)
                {
                    vehicle["rotation"] = direction;
                }
                else
                {
                    QJsonArray rotation;
                    rotation.append(0);
                    rotation.append(359);
                    vehicle["rotation"] = rotation;
                }

                vehicles.append(vehicle);
            }
            if (tile.GetToilet())
            {
                QJsonObject toilet;
                toilet["x"] = col;
                toilet["y"] = row;
                toilets.append(toilet);
            }
            if (tile.GetNPC() != "")
            {
                QJsonObject npc;
                npc["x"] = col;
                npc["y"] = row;
                npc["class"] = tile.GetNPC();
                npcs.append(npc);
            }
            if (tile.GetSignage() != "")
            {
                qDebug() << tile.GetSignage();
                QJsonObject sign;
                sign["x"] = col;
                sign["y"] = row;
                sign["signage"] = tile.GetSignage();
                signs.append(sign);
            }
        }
    }
    if (!traps.empty())
    {
        object["place_traps"] = traps;
    }
    if (!monsters.empty())
    {
        object["place_monster"] = monsters;
    }
    if (!items.empty())
    {
        object["add"] = items;
    }
    if (!vehicles.empty())
    {
        object["place_vehicles"] = vehicles;
    }
    if (!toilets.empty())
    {
        object["place_toilets"] = toilets;
    }
    if (!npcs.empty())
    {
        object["place_npcs"] = npcs;
    }
    if (!signs.empty())
    {
        object["place_signs"] = signs;
    }

    QHash<MonsterGroup, QRect> finalizedMonsterGroups;
    foreach (MonsterGroup mg, monsterGroupCollection.keys())
    {
        QVector<bool> mgLocs = monsterGroupCollection[mg];

        while (mgLocs.contains(true))
        {
            QRect currentSection;
            int currentIndex = mgLocs.indexOf(true);
            int starty = currentIndex / OVERMAP_TERRAIN_WIDTH;
            int startx = currentIndex % OVERMAP_TERRAIN_WIDTH;
            currentSection.setLeft(startx);
            currentSection.setTop(starty);

            int x = startx;
            while (x < OVERMAP_TERRAIN_WIDTH && mgLocs[index(Tripoint(x+1, starty, 0))])
            {
                x++;
            }
            currentSection.setRight(x);

            int y = starty;
            bool keepGoing = true;
            while(y < OVERMAP_TERRAIN_WIDTH && keepGoing)
            {
                for (int i = startx; i <= x; i++)
                {
                    keepGoing = mgLocs[index(Tripoint(i, y+1, 0))];
                    if (!keepGoing)
                    {
                        break;
                    }
                }
                if (!keepGoing)
                {
                    break;
                }
                y++;
            }
            currentSection.setBottom(y);

            for (y = currentSection.top(); y <= currentSection.bottom(); y++)
            {
                for (x = currentSection.left(); x <= currentSection.right(); x++)
                {
                    mgLocs[index(Tripoint(x,y,0))] = false;
                }
            }
            finalizedMonsterGroups.insertMulti(mg, currentSection);
        }
    }

    foreach (MonsterGroup mg, finalizedMonsterGroups.uniqueKeys())
    {
        foreach (QRect r, finalizedMonsterGroups.values(mg))
        {
            qDebug() << mg.GetID() << r.left() << r.top() << "->" << r.right() << r.bottom();
            QJsonObject monsterGroup;

            if (r.left() == r.right())
            {
                monsterGroup["x"] = r.left();
            }
            else
            {
                QJsonArray xArray;
                xArray.append(r.left());
                xArray.append(r.right());
                monsterGroup["x"] = xArray;
            }
            if (r.top() == r.bottom())
            {
                monsterGroup["y"] = r.top();
            }
            else
            {
                QJsonArray yArray;
                yArray.append(r.top());
                yArray.append(r.bottom());
                monsterGroup["y"] = yArray;
            }
            monsterGroup["monster"] = mg.GetID();
            monsterGroup["chance"] = mg.GetChance();
            monsterGroup["density"] = mg.GetDensity();

            monsterGroups.append(monsterGroup);
        }
    }

    if (!monsterGroups.empty())
    {
        object["place_monsters"] = monsterGroups;
    }

    QHash<ItemGroup, QRect> finalizedItemGroups;
    foreach (ItemGroup ig, itemGroupCollection.keys())
    {
        QVector<bool> igLocs = itemGroupCollection[ig];

        while (igLocs.contains(true))
        {
            QRect currentSection;
            int currentIndex = igLocs.indexOf(true);
            int starty = currentIndex / OVERMAP_TERRAIN_WIDTH;
            int startx = currentIndex % OVERMAP_TERRAIN_WIDTH;
            currentSection.setLeft(startx);
            currentSection.setTop(starty);

            int x = startx;
            while (x < OVERMAP_TERRAIN_WIDTH && igLocs[index(Tripoint(x+1, starty, 0))])
            {
                x++;
            }
            currentSection.setRight(x);

            int y = starty;
            bool keepGoing = true;
            while(y < OVERMAP_TERRAIN_WIDTH && keepGoing)
            {
                for (int i = startx; i <= x; i++)
                {
                    keepGoing = igLocs[index(Tripoint(i, y+1, 0))];
                    if (!keepGoing)
                    {
                        break;
                    }
                }
                if (!keepGoing)
                {
                    break;
                }
                y++;
            }
            currentSection.setBottom(y);

            for (y = currentSection.top(); y <= currentSection.bottom(); y++)
            {
                for (x = currentSection.left(); x <= currentSection.right(); x++)
                {
                    igLocs[index(Tripoint(x,y,0))] = false;
                }
            }
            finalizedItemGroups.insertMulti(ig, currentSection);
        }
    }

    foreach (ItemGroup ig, finalizedItemGroups.uniqueKeys())
    {
        foreach (QRect r, finalizedItemGroups.values(ig))
        {
            qDebug() << ig.GetID() << r.left() << r.top() << "->" << r.right() << r.bottom();
            QJsonObject itemGroup;

            if (r.left() == r.right())
            {
                itemGroup["x"] = r.left();
            }
            else
            {
                QJsonArray xArray;
                xArray.append(r.left());
                xArray.append(r.right());
                itemGroup["x"] = xArray;
            }
            if (r.top() == r.bottom())
            {
                itemGroup["y"] = r.top();
            }
            else
            {
                QJsonArray yArray;
                yArray.append(r.top());
                yArray.append(r.bottom());
                itemGroup["y"] = yArray;
            }
            itemGroup["item"] = ig.GetID();
            itemGroup["chance"] = ig.GetChance();

            itemGroups.append(itemGroup);
        }
    }

    if (!itemGroups.empty())
    {
        object["place_items"] = itemGroups;
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

    for (int y = 0; y < OVERMAP_TERRAIN_WIDTH; y++)
    {
        for (int x = 0; x < OVERMAP_TERRAIN_WIDTH; x++)
        {
            Tile tile = t.GetTile(Tripoint(x, y, 0));
        }
    }

    mapgenObject["object"] = object;
    doc.setObject(mapgenObject);

    qDebug() << doc.toJson();

    QSettings settings;
    QString dataDir = settings.value("cataclysm_dir", "").toString();
    QString filename = QFileDialog::getSaveFileName(0, "Save As...", dataDir, "JSON (*.json)");

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

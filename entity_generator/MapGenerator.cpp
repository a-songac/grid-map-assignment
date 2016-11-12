#include "MapGenerator.h"
#include "../entity/Cell.h"

Map* MapGenerator::map1() {

    Coordinate entryDoor = {3,0};
    Coordinate exitDoor = {3,6};

    Map* map = new Map(7, 7,entryDoor, exitDoor);

    map->setName("DefaultMap1");

    map->setCellType(2, 3, Cell::TYPE_WALL);
    map->setCellType(2, 4, Cell::TYPE_WALL);
    map->setCellType(2, 5, Cell::TYPE_WALL);
    map->setCellType(2, 6, Cell::TYPE_WALL);

    map->fillCell(6, 6, Cell::OCCUPANT_CHEST);
    map->fillCell(5, 5, Cell::OCCUPANT_OPPONENT);

    return map;
}



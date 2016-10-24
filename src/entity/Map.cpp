#include <iostream>
#include <iostream>
#include "Map.h"
#include "../service/MapValidator.h"
#include "../utils/ArrayUtils.h"
#include "../view/MapView.h"

using namespace std;


Map::Map() {
    height = 7;
    width = 7;

    grid = new Cell* [height];
    initialize2DArray(grid, height, width);

    entryDoor = {0,0};
    exitDoor = {height-1, width-1};

    grid[entryDoor.row][entryDoor.column].setType(Cell::TYPE_DOOR_ENTRY);
    grid[exitDoor.row][exitDoor.column].setType(Cell::TYPE_DOOR_EXIT);

}


Map::Map(int height, int width) {
    this->height = height;
    this->width = width;

    grid = new Cell* [height];
    initialize2DArray(grid, height, width);
}

Map::Map(int height, int width, Coordinate entryDoor, Coordinate exitDoor) {
    this->height = height;
    this->width = width;

    grid = new Cell* [height];
    initialize2DArray(grid, height, width);

    this->entryDoor.column = entryDoor.column;
    this->entryDoor.row = entryDoor.row;

    this->exitDoor.column = exitDoor.column;
    this->exitDoor.row = exitDoor.row;

    grid[entryDoor.row][entryDoor.column].setType(Cell::TYPE_DOOR_ENTRY);
    grid[exitDoor.row][exitDoor.column].setType(Cell::TYPE_DOOR_EXIT);

}


Map::~Map() {

    destroy2DArray(grid, height, width);

}


void Map::initDoors(Coordinate entryDoor, Coordinate exitDoor) {

    this->entryDoor.column = entryDoor.column;
    this->entryDoor.row = entryDoor.row;

    this->exitDoor.column = exitDoor.column;
    this->exitDoor.row = exitDoor.row;

    grid[entryDoor.row][entryDoor.column].setType(Cell::TYPE_DOOR_ENTRY);
    grid[exitDoor.row][exitDoor.column].setType(Cell::TYPE_DOOR_EXIT);
}



char Map::getOccupant(int row, int column) {
    if (isWall(row, column)) {
        return '0';
    }
    return grid[row][column].getOccupant();
}


bool Map::fillCell(int row, int column, char occupant) {
    if (isWall(row, column)) {
        return false;
    }
    grid[row][column].setOccupant(occupant);
    notify();
    return true;
}

bool Map::isOccupied(int row, int column) {
    return getOccupant(row, column) != ' ';
}

bool Map::validate() {
    MapValidator validator(this);
    return validator.validateMap();
}

void Map::render() {
    notify();
}





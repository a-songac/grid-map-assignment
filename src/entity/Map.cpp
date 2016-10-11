#include <iostream>
#include "Map.h"
#include "../view/MapView.h"
#include "../service/MapValidator.h"

using namespace std;


Map::Map() {
    height = 7;
    width = 7;

    grid = new Cell* [height];
    initializeGrid(grid, height, width);

    entryDoor = {0,0};
    exitDoor = {height-1, width-1};

    grid[entryDoor.row][entryDoor.column].setType(Cell::TYPE_DOOR_ENTRY);
    grid[exitDoor.row][exitDoor.column].setType(Cell::TYPE_DOOR_EXIT);

}


Map::Map(int height, int width) {
    this->height = height;
    this->width = width;

    grid = new Cell* [height];
    initializeGrid(grid, height, width);
}

Map::Map(int height, int width, Coordinate entryDoor, Coordinate exitDoor) {
    this->height = height;
    this->width = width;

    grid = new Cell* [height];
    initializeGrid(grid, height, width);

    this->entryDoor.column = entryDoor.column;
    this->entryDoor.row = entryDoor.row;

    this->exitDoor.column = exitDoor.column;
    this->exitDoor.row = exitDoor.row;

    grid[entryDoor.row][entryDoor.column].setType(Cell::TYPE_DOOR_ENTRY);
    grid[exitDoor.row][exitDoor.column].setType(Cell::TYPE_DOOR_EXIT);

}


Map::~Map() {

    for(int i = 0; i < height; ++i) {
        delete [] grid[i];
    }
    delete [] grid;

}

void initializeGrid(Cell** grid, int height, int width) {

    for(int i = 0; i < height; ++i) {
        grid[i] = new Cell[width];
    }
}

void Map::initDoors(Coordinate entryDoor, Coordinate exitDoor) {

    this->entryDoor.column = entryDoor.column;
    this->entryDoor.row = entryDoor.row;

    this->exitDoor.column = exitDoor.column;
    this->exitDoor.row = exitDoor.row;

    grid[entryDoor.row][entryDoor.column].setType(Cell::TYPE_DOOR_ENTRY);
    grid[exitDoor.row][exitDoor.column].setType(Cell::TYPE_DOOR_EXIT);
}

int Map::getHeight() {
    return height;
}

int Map::getWidth() {
    return width;
}

Coordinate Map::getEntryDoorCoordinate() {
    return entryDoor;
}

void Map::setEntryDoor(Coordinate entryDoor) {
    this->entryDoor = entryDoor;
}

Coordinate Map::getExitDoorCoordinate() {
    return exitDoor;
}

void Map::setExitDoor(Coordinate exitDoor) {
    this->exitDoor = exitDoor;
}

bool Map::isFloor(int row, int column) {
    return grid[row][column].getType() == Cell::TYPE_FLOOR;
}

bool Map::isWall(int row, int column) {
    return grid[row][column].getType() == Cell::TYPE_WALL;
}

bool Map::isEntryDoor(int row, int column) {
    return grid[row][column].getType() == Cell::TYPE_DOOR_ENTRY;
}

bool Map::isExitDoor(int row, int column) {
    return grid[row][column].getType() == Cell::TYPE_DOOR_EXIT;
}

bool Map::isDoor(int row, int column) {

    return grid[row][column].getType() == Cell::TYPE_DOOR_ENTRY
        || grid[row][column].getType() == Cell::TYPE_DOOR_EXIT;
}

char Map::getOccupant(int row, int column) {
    if (isWall(row, column)) {
        return '0';
    }
    return grid[row][column].getOccupant();
}

void Map::setCellType(int row, int column, char type) {
    grid[row][column].setType(type);
}

bool Map::fillCell(int row, int column, char occupant) {
    if (isWall(row, column)) {
        return false;
    }
    grid[row][column].setOccupant(occupant);
    return true;
}

bool Map::isOccupied(int row, int column) {
    return getOccupant(row, column) != ' ';
}

void Map::render() {
    MapView::renderMap(this);
}

bool Map::validate() {
    MapValidator validator(this);
    return validator.validateMap();
}

bool Map::isInbound(int row, int column) {
    return row >= 0 && row < height && column >= 0 && column < width;

}






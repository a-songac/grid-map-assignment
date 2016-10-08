#include <iostream>
#include "Map.h"
#include "../service/MapRenderer.h"
#include "../service/MapValidator.h"

using namespace std;

void initializeGrid(Cell** grid, int height, int width) {

    for(int i = 0; i < height; ++i) {
        grid[i] = new Cell[width];
        for (int j = 0; j < width; j++) {
            (grid[i][j]).setType(Cell::FLOOR);
            (grid[i][j]).setOccupant(' ');
        }
    }
}

Map::Map() {
    height = 7;
    width = 7;

    grid = new Cell* [height];
    initializeGrid(grid, height, width);

    entryDoor = {0,0};
    nbExitDoors = 1;
    exitDoors = new Coordinate[nbExitDoors];
    exitDoors[0] = {height-1, width-1};

    grid[entryDoor.row][entryDoor.column].setType(Cell::DOOR_ENTRY);
    grid[exitDoors[0].row][exitDoors[0].column].setType(Cell::DOOR_EXIT);

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

    nbExitDoors = 1;
    exitDoors = new Coordinate[nbExitDoors];
    exitDoors[0].column = exitDoor.column;
    exitDoors[0].row = exitDoor.row;

    grid[entryDoor.row][entryDoor.column].setType(Cell::DOOR_ENTRY);
    grid[exitDoors[0].row][exitDoors[0].column].setType(Cell::DOOR_EXIT);

}

void Map::initDoors(Coordinate entryDoor, Coordinate exitDoor) {
    nbExitDoors = 1;

    this->entryDoor.column = entryDoor.column;
    this->entryDoor.row = entryDoor.row;

    exitDoors = new Coordinate[nbExitDoors];
    exitDoors[0].column = exitDoor.column;
    exitDoors[0].row = exitDoor.row;

    grid[entryDoor.row][entryDoor.column].setType(Cell::DOOR_ENTRY);
    grid[exitDoors[0].row][exitDoors[0].column].setType(Cell::DOOR_EXIT);
}

int Map::getHeight() {
    return height;
}

int Map::getWidth() {
    return width;
}

Cell** Map::getGrid() {
    return grid;
}

Coordinate Map::getEntryDoor() {
    return entryDoor;
}

void Map::setEntryDoor(Coordinate entryDoor) {
    this->entryDoor = entryDoor;
}

Coordinate* Map::getExitDoors() {
    return exitDoors;
}

int Map::getNbExitDoors() {
    return nbExitDoors;
}

void Map::setExitDoors(Coordinate* exitDoors) {
    this->exitDoors = exitDoors;
}

bool Map::isFloor(int row, int column) {
    return grid[row][column].getType() == Cell::FLOOR;
}

bool Map::isWall(int row, int column) {
    return grid[row][column].getType() == Cell::WALL;
}

bool Map::isEntryDoor(int row, int column) {
    return grid[row][column].getType() == Cell::DOOR_ENTRY;
}

bool Map::isExitDoor(int row, int column) {
    return grid[row][column].getType() == Cell::DOOR_EXIT;
}

bool Map::isDoor(int row, int column) {

    return grid[row][column].getType() == Cell::DOOR_ENTRY
        || grid[row][column].getType() == Cell::DOOR_EXIT;
}

char Map::getOccupant(int row, int column) {
    if (isWall(row, column)) {
        cerr << "Error, this is a wall!" << endl;
        return '0';
    }
    return grid[row][column].getOccupant();
}

void Map::setCellType(int row, int column, char type) {
    grid[row][column].setType(type);
}

void Map::fillCell(int row, int column, char occupant) {
    if (isWall(row, column)) {
        cerr << "Error, cannot occupy a wall!" << endl;
    }
    grid[row][column].setOccupant(occupant);
}

bool Map::isOccupied(int row, int column) {
    return getOccupant(row, column) != ' ';
}

std::ostream& operator<<(std::ostream &strm, const Map &map) {
    return strm << map.height << " by " << map.width << " map." << endl;
}

void Map::render() {
    MapRenderer::renderMap(this);
}

bool Map::validate() {
    MapValidator validator(this);
    return validator.validateMap();
}

bool Map::isInbound(int row, int column) {
    return row >= 0 && row < height && column >= 0 && column < width;

}


Map::~Map() {

    for(int i = 0; i < height; ++i) {
        delete [] grid[i];
    }
    delete [] grid;

    delete [] exitDoors;
}




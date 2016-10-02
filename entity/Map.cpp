#include <iostream>
#include "Map.h"

using namespace std;

void initializeGrid(Cell** grid, int height, int width) {

    for(int i = 0; i < height; ++i) {
        grid[i] = new Cell[width];
        for (int j = 0; j < width; j++) {
            (grid[i][j]).setType(Cell::FLOOR);
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

    grid[entryDoor.row][entryDoor.column].setType(Cell::DOOR_IN);
    grid[exitDoors[0].row][exitDoors[0].column].setType(Cell::DOOR_OUT);

}

Map::Map(int height, int width) {
    this->height = height;
    this->width = width;

    grid = new Cell* [height];
    initializeGrid(grid, height, width);

    entryDoor = {0,0};
    nbExitDoors = 1;
    exitDoors = new Coordinate[nbExitDoors];
    exitDoors[0] = {height-1, width-1};

    grid[entryDoor.row][entryDoor.column].setType(Cell::DOOR_IN);
    grid[exitDoors[0].row][exitDoors[0].column].setType(Cell::DOOR_OUT);


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
    return row == entryDoor.row && column == entryDoor.column;
}

bool Map::isDoor(int row, int column) {

    return grid[row][column].getType() == Cell::DOOR_IN
        || grid[row][column].getType() == Cell::DOOR_OUT;
}



std::ostream& operator<<(std::ostream &strm, const Map &map) {
    return strm << map.height << " by " << map.width << " map." << endl;
}

void Map::destroyMap() {

    for(int i = 0; i < height; ++i) {
        delete [] grid[i];
    }
    delete [] grid;
}




#include <iostream>
#include "Map.h"
#include "../service/MapValidator.h"
#include "../utils/ArrayUtils.h"
#include "../view/MapView.h"


using namespace std;


Map::Map() {
    height = 7;
    width = 7;
    playerPosition = {-1, -1};


    //grid = new Cell* [height];
    std::vector<std::vector<Cell> > g(height, std::vector<Cell>(width));
    this->grid = g;
    //initialize2DArray(this->grid, height, width);

    Coordinate entryDoor = {0,0};
    Coordinate exitDoor = {height-1, width-1};

    grid.at(entryDoor.row).at(entryDoor.column).setType(Cell::TYPE_DOOR_ENTRY);
    grid.at(exitDoor.row).at(exitDoor.column).setType(Cell::TYPE_DOOR_EXIT);

}


Map::Map(int height, int width) {
    this->height = height;
    this->width = width;
    playerPosition = {-1, -1};

    std::vector<std::vector<Cell> > g(height, std::vector<Cell>(width));
    this->grid = g;

    //initialize2DArray(grid, height, width);
}

Map::Map(int height, int width, Coordinate entryDoor, Coordinate exitDoor) {
    this->height = height;
    this->width = width;
    playerPosition = {-1, -1};

    //grid = new Cell* [height];
    std::vector<std::vector<Cell> > g(height, std::vector<Cell>(width));
    this->grid = g;

    //initialize2DArray(grid, height, width);

    this->entryDoor.column = entryDoor.column;
    this->entryDoor.row = entryDoor.row;

    this->exitDoor.column = exitDoor.column;
    this->exitDoor.row = exitDoor.row;

    grid.at(entryDoor.row).at(entryDoor.column).setType(Cell::TYPE_DOOR_ENTRY);
    grid.at(exitDoor.row).at(exitDoor.column).setType(Cell::TYPE_DOOR_EXIT);

}

/**
Map::~Map() {

    destroy2DArray(grid, height, width);

}
*/

void Map::initDoors(Coordinate entryDoor, Coordinate exitDoor) {

    this->entryDoor.column = entryDoor.column;
    this->entryDoor.row = entryDoor.row;

    this->exitDoor.column = exitDoor.column;
    this->exitDoor.row = exitDoor.row;

    grid.at(entryDoor.row).at(entryDoor.column).setType(Cell::TYPE_DOOR_ENTRY);
    grid.at(exitDoor.row).at(exitDoor.column).setType(Cell::TYPE_DOOR_EXIT);
}



char Map::getOccupant(int row, int column) {
    if (isWall(row, column)) {
        return '0';
    }
    return grid.at(row).at(column).getOccupant();
}


bool Map::fillCell(int row, int column, char occupant) {
    if (isWall(row, column)) {
        return false;
    }
    grid.at(row).at(column).setOccupant(occupant);
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
    MapView::renderMap(this);
}




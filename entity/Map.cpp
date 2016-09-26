#include <iostream>
#include "Map.h"

using namespace std;

void initializeGrid(Cell** grid, int height, int width) {
    grid = new Cell*[height];

    for(int i = 0; i < height; ++i) {
        grid[i] = new Cell[width];
        for (int j = 0; j < width; j++) {
            (grid[i][j]).setType(Cell::FLOOR);
        }
    }
}

Map::Map() {
    height = 10;
    width = 10;
//    initializeGrid(grid, height, width);
    grid = new Cell* [height];

    for(int i = 0; i < height; ++i) {
        grid[i] = new Cell[width];
        for (int j = 0; j < width; j++) {
            (grid[i][j]).setType(Cell::FLOOR);
        }
    }
}

Map::Map(int height, int width) {
    this->height = height;
    this->width = width;
    initializeGrid(grid, height, width);
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

std::ostream& operator<<(std::ostream &strm, const Map &map) {
    return strm << map.height << " by " << map.width << " map." << endl;
}

void Map::destroyMap() {

    for(int i = 0; i < height; ++i) {
        delete [] grid[i];
    }
    delete [] grid;
}




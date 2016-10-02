#include <iostream>

#include "MapValidator.h"
#include "../entity/Map.h"
#include "../entity/Cell.h"
#include "../utils/ArrayUtils.h"

using namespace std;


MapValidator::MapValidator(Map* map) {

    this->map = map;

    reachable = new int*[map->getHeight()];
    visited = new bool*[map->getHeight()];
    initialize2DArray(reachable, map->getHeight(), map->getWidth());
    initialize2DArray(visited, map->getHeight(), map->getWidth());

}

MapValidator::~MapValidator() {
    destroy2DArray(reachable, map->getHeight(), map->getWidth());
    destroy2DArray(visited, map->getHeight(), map->getWidth());
}

bool MapValidator::validateMap() {

    bool invalid = false;
    int height = map->getHeight();
    int width = map->getWidth();

    reset2DArray(reachable, height, width);

    cout << "Start map validation" << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            cout << "Start validation of cell [" << i << "][" <<j <<"]" << endl;


            if ( map->isWall(i, j) || map->isEntryDoor(i, j)) {
                continue;
            }
            if (reachable[i][j] > 0) {
                cout << "Skip; cell was tested and is reachable" << endl;
            }

            cout << "Validate for entry door" << endl;
            if (!validateForDoor(i, j, map->getEntryDoor())) {
                invalid = true;
                break;
            }
        }
        if (invalid)
            break;
    }

    return !invalid;

}

bool MapValidator::validateForDoor(int row, int column, Coordinate door) {
    reset2DArray(visited, map->getHeight(), map->getWidth());
    return backTrack(row, column, door.row, door.column);
}

bool MapValidator::backTrack(int row, int column, int doorRow, int doorColumn) {

    int height = map->getHeight();
    int width = map->getWidth();
    Cell **grid = map->getGrid();

    visited[row][column] = true;

    if (row == doorRow && column == doorColumn)
        return true;

    // NORTH
    if (inbound(row+1, column, height, width)
            && !visited[row+1][column]
            && grid[row +1][column].getType() != Cell::WALL) {

        if (backTrack(row+1, column, doorRow, doorColumn)) {
            reachable[row][column]++;
            return true;
        }
    }

    // SOUTH
    if (inbound(row-1, column, height, width)
            && !visited[row-1][column]
            && grid[row -1][column].getType() != Cell::WALL) {

        if (backTrack(row-1, column, doorRow, doorColumn)) {
            reachable[row][column]++;
            return true;
        }
    }

    // EAST
    if (inbound(row, column+1, height, width)
            && !visited[row][column+1]
            && grid[row][column+1].getType() != Cell::WALL) {

        if (backTrack(row, column+1, doorRow, doorColumn)) {
            reachable[row][column]++;
            return true;
        }
    }

    // WEST
    if (inbound(row, column-1, height, width)
            && !visited[row][column-1]
            && grid[row][column-1].getType() != Cell::WALL) {

        if (backTrack(row, column-1, doorRow, doorColumn)) {
            reachable[row][column]++;
            return true;
        }
    }
    return false;
}



bool inbound(int i, int j, int height, int width) {

    return i >= 0 && j >= 00 && i < height && j < width;

}



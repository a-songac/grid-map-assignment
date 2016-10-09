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

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            if ( map->isWall(i, j) || map->isEntryDoor(i, j) || reachable[i][j] > 0) {
                continue;
            }

            if (!validateForDoor(i, j, map->getEntryDoorCoordinate())) {
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

    visited[row][column] = true;

    if (row == doorRow && column == doorColumn)
        return true;

    // NORTH
    if (map->isInbound(row+1, column)
            && !visited[row+1][column]
            && !map->isWall(row+1, column)) {

        if (backTrack(row+1, column, doorRow, doorColumn)) {
            reachable[row][column]++;
            return true;
        }
    }

    // SOUTH
    if (map->isInbound(row-1, column)
            && !visited[row-1][column]
            && !map->isWall(row-1, column)) {

        if (backTrack(row-1, column, doorRow, doorColumn)) {
            reachable[row][column]++;
            return true;
        }
    }

    // EAST
    if (map->isInbound(row, column+1)
            && !visited[row][column+1]
            &&!map->isWall(row, column+1)) {

        if (backTrack(row, column+1, doorRow, doorColumn)) {
            reachable[row][column]++;
            return true;
        }
    }

    // WEST
    if (map->isInbound(row, column-1)
            && !visited[row][column-1]
            && !map->isWall(row, column-1)) {

        if (backTrack(row, column-1, doorRow, doorColumn)) {
            reachable[row][column]++;
            return true;
        }
    }
    return false;
}




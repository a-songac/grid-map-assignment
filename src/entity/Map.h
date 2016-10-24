/// @file
/// @brief Header file containing class declaration for Map.class
///        and struct declaration for Coordinate.struct
/// @details  1. Game Rules: The Map enforces that a cell of type wall cannot be occupied \n\n
/// 2. Model class from the MVP pattern. The Map keeps the state of the map, which consists of a 2D array of cells. The coordinate struct helps represent locations on the map. \n
/// The map also implements the Observer pattern and consists of the Subject (Observable)
/// 3. Libraries: The map does not use any specific library.

#pragma once
#include "Cell.h"
#include "../core/Subject.h"

/// Struct that represents a map coordinate
struct Coordinate {
    int row;
    int column;

};
/// Class to implement the game map
class Map : public Subject {
    public:

        Map(int h, int w, Coordinate entry, Coordinate exit);
        Map(int h, int w);
        Map();
        ~Map();

        int getHeight();
        int getWidth();

        Coordinate getEntryDoorCoordinate();
        Coordinate getExitDoorCoordinate();
        void setEntryDoor(Coordinate entryDoor);
        void setExitDoor(Coordinate exitDoors);
        void initDoors(Coordinate entryDoor, Coordinate exitDoor);
        bool isDoor(int row, int column);
        bool isEntryDoor(int row, int column);
        bool isExitDoor(int row, int column);

        bool isWall(int row, int column);
        bool isFloor(int row, int column);
        bool isOccupied(int row, int column);
        bool fillCell(int row, int column, char occupant);
        char getOccupant(int row, int column);

        void render();
        bool validate();
        void setCellType(int row, int column, char type);
        bool isInbound(int row, int column);

    private:
        Cell **grid;
        int height;
        int width;
        Coordinate entryDoor;
        Coordinate exitDoor;

};






inline int Map::getHeight() {
    return height;
}

inline int Map::getWidth() {
    return width;
}

inline Coordinate Map::getEntryDoorCoordinate() {
    return entryDoor;
}

inline void Map::setEntryDoor(Coordinate entryDoor) {
    this->entryDoor = entryDoor;
    notify();
}

inline Coordinate Map::getExitDoorCoordinate() {
    return exitDoor;
}

inline void Map::setExitDoor(Coordinate exitDoor) {
    this->exitDoor = exitDoor;
    notify();
}

inline bool Map::isFloor(int row, int column) {
    return grid[row][column].getType() == Cell::TYPE_FLOOR;
}

inline bool Map::isWall(int row, int column) {
    return grid[row][column].getType() == Cell::TYPE_WALL;
}

inline bool Map::isEntryDoor(int row, int column) {
    return grid[row][column].getType() == Cell::TYPE_DOOR_ENTRY;
}

inline bool Map::isExitDoor(int row, int column) {
    return grid[row][column].getType() == Cell::TYPE_DOOR_EXIT;
}

inline bool Map::isDoor(int row, int column) {

    return grid[row][column].getType() == Cell::TYPE_DOOR_ENTRY
        || grid[row][column].getType() == Cell::TYPE_DOOR_EXIT;
}

inline bool Map::isInbound(int row, int column) {
    return row >= 0 && row < height && column >= 0 && column < width;

}

inline void Map::setCellType(int row, int column, char type) {
    grid[row][column].setType(type);
    notify();
}


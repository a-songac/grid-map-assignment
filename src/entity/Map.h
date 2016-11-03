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

        Map(string name, int h, int w, Coordinate entry, Coordinate exit);
        Map(string name, int h, int w);
        Map();
        Map(string name);
        ~Map();

        int getHeight();
        int getWidth();

        void setName(string name);
        string getName();

        Coordinate getEntryDoorCoordinate();
        Coordinate getExitDoorCoordinate();
        void setEntryDoor(Coordinate entryDoor);
        void setExitDoor(Coordinate exitDoors);
        void initDoors(Coordinate entryDoor, Coordinate exitDoor);
        bool isDoor(int row, int column);
        bool isEntryDoor(int row, int column);
        bool isExitDoor(int row, int column);

        void movePlayer(int rowm, int column);
        bool hasPlayer(int row, int colum);
        void setPlayer(int row, int column, bool yes);
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
        Coordinate playerPosition;
        string name;

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

inline void Map::setName(string name) {
    this->name = name;
}

inline string Map::getName() {
    return this->name;
}

inline bool Map::hasPlayer(int row, int column) {
    return grid[row][column].hasPlayer();
}

inline void Map::setPlayer(int row, int column, bool yes) {
    grid[row][column].setPlayer(yes);
}

inline void Map::movePlayer(int row, int column) {
    if (-1 != this->playerPosition.column && -1 != this->playerPosition.row){
       grid[playerPosition.row][playerPosition.column].setPlayer(false);
    }
    playerPosition.row = row;
    playerPosition.column = column;
    grid[playerPosition.row][playerPosition.column].setPlayer(true);
    notify();
}


/// @file
/// @brief Header file containing class declaration for Map.class
///        and struct declaration for Coordinate.struct
/// @details  No specific game rule enforced by the class except that a wall cannot be occupied.
/// Design wise, the Map class is a container of a 2D array of Cell objects.
/// The map does not use any specific library.

#pragma once
#include <iostream>
#include "Cell.h"

/// Struct that represents a map coordinate
struct Coordinate {
    int row;
    int column;

};
/// Class to implement the game map
class Map {
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


/// @file
/// @brief Header file containing class declaration for Cell.class
/// @details  No specific game rule enforced by the class.
/// Simple object to informs a bout the type of a cell and its occupant
/// No specific library used.

#pragma once
#include <iostream>

using namespace std;

/// Class to implement a cell
class Cell {
    public:
        static const char TYPE_WALL = 'w';
        static const char TYPE_DOOR_ENTRY = 'e';
        static const char TYPE_DOOR_EXIT = 'x';
        static const char TYPE_FLOOR = 'f';
        static const char OCCUPANT_CHEST = 'c';
        static const char OCCUPANT_OPPONENT = 'o';
        static const char OCCUPANT_FRIEND = 'r';
        static const char OCCUPANT_EMPTY = ' ';

        Cell();
        Cell(char type);

        char getType();
        void setType(char type);
        char getOccupant();
        void setOccupant(char occupant);

    private:
        char type;
        char occupant;
};
        void initializeGrid(Cell** grid, int height, int width);

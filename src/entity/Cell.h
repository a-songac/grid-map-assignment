#pragma once
#include <iostream>

using namespace std;

class Cell {
    public:
        static const char WALL = 'w';
        static const char DOOR_ENTRY = 'e';
        static const char DOOR_EXIT = 'x';
        static const char FLOOR = 'f';
        static const char CHEST = 'c';
        static const char OPONENT = 'o';
        static const char FRIEND = 'r';

        Cell();
        Cell(char type);

        char getType();
        void setType(char type);
        char getOccupant();
        void setOccupant(char occupant);

        friend std::ostream& operator<<(std::ostream &strm, const Cell &cell);
    private:
        char type;
        char occupant;


};

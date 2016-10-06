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

        Cell();
        Cell(char type);

        char getType();
        void setType(char type);

        friend std::ostream& operator<<(std::ostream &strm, const Cell &cell);
    private:
        char type;


};

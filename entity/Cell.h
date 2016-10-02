#pragma once
#include <iostream>

using namespace std;

class Cell {
    public:
        static const char WALL = 'w';
        static const char DOOR_IN = 'i';
        static const char DOOR_OUT = 'o';
        static const char FLOOR = 'f';

        Cell();
        Cell(char type);

        char getType();
        void setType(char type);

        friend std::ostream& operator<<(std::ostream &strm, const Cell &cell);
    private:
        char type;


};

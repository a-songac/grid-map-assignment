#include <iostream>

#include "Cell.h"

using namespace std;


Cell::Cell() {
    type = Cell::FLOOR;
}

Cell::Cell(char type) {
    this->type = type;
}

char Cell::getType() {
    return type;
}

void Cell::setType(char type) {
    this->type = type;
}

string getCellTypeName(char type) {
    switch(type) {
    case Cell::WALL:
        return "Wall";
    case Cell::DOOR:
        return "Door";
    case Cell::FLOOR:
        return "Floor";
    }
    return "Unknown";
}

std::ostream& operator<<(std::ostream &strm, const Cell &cell) {
    return strm << "Cell of type " << getCellTypeName(cell.type) << " ";
}




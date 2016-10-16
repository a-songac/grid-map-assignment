#include "Cell.h"

using namespace std;


Cell::Cell() {
    type = Cell::TYPE_FLOOR;
    occupant = Cell::OCCUPANT_EMPTY;
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

char Cell::getOccupant() {
    return occupant;
}

void Cell::setOccupant(char occupant) {
    this->occupant = occupant;
}





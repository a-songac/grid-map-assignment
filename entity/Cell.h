/// @file
/// @brief Header file containing class declaration for Cell.class
/// @details  1. Game Rules: A cell can be of type and/or contain game specific items: door, wall, friend or enemy character, and a chest \n\n
/// 2. Design: Modlel class from the MVC pattern.  Keeps the state of a cell by providing a type and an occupant \n\n
/// 3. Libraries: No specific library used.

#pragma once
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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
        static const char OCCUPANT_PLAYER = 'p';

        Cell();
        Cell(char type);

        char getType();
        void setType(char type);
        char getOccupant();
        void setOccupant(char occupant);
        bool hasPlayer();
        void setPlayer(bool player);
        void setOriginalOccupant(char originalOccupant);
        char getOriginalOccupant();

    private:
        char type;
        char originalOccupant;
        char occupant;
        bool player;

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & type;
            ar & occupant;
            ar & originalOccupant;

        }
};

inline Cell::Cell(char type) {
    this->type = type;
}

inline char Cell::getType() {
    return type;
}

inline void Cell::setType(char type) {
    this->type = type;
}

inline char Cell::getOccupant() {
    return occupant;
}

inline void Cell::setOccupant(char occupant) {
    this->occupant = occupant;
}

inline void Cell::setPlayer(bool player) {
    this->player = player;
}

inline bool Cell::hasPlayer() {
    return this->player;
}

inline void Cell::setOriginalOccupant(char originalOccupant) {
    this->originalOccupant = originalOccupant;
}
inline char Cell::getOriginalOccupant() {
    return this->originalOccupant;
}



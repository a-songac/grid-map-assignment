/// @file
/// @brief Header file containing class declaration for Map.class
///        and struct declaration for Coordinate.struct
/// @details  1. Game Rules: The Map enforces that a cell of type wall cannot be occupied \n\n
/// 2. Model class from the MVP pattern. The Map keeps the state of the map, which consists of a 2D array of cells. The coordinate struct helps represent locations on the map. \n\n
/// 3. Libraries: The map uses the boost archive libraries in order for its state to be saved/loaded.

#pragma once

#include "Cell.h"
#include "Coordinate.h"
#include "../core/Subject.h"
#include <vector>
#include "GameElement.h"
#include "GameItem.h"
#include "GamePlayer.h"


#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/serialization.hpp>

/// Class to implement the game map
class Map : public Subject{
    public:

        Map(int h, int w, Coordinate entry, Coordinate exit);
        Map(int h, int w);
        Map();
        Map(Map* mapToCopy);
        ~Map();

        void setName(std::string name);
        std::string getName();

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

        bool movePlayer(int rowm, int column);
        bool hasPlayer(int row, int colum);
        void setPlayer(int row, int column, bool yes);
        bool isWall(int row, int column);
        bool isFloor(int row, int column);
        bool isOccupied(int row, int column);
        bool fillCell(int row, int column, char occupant);
        char getOccupant(int row, int column);
        bool isPlayerAdjacent(int row, int column);

        void render();
        bool validate();
        void setCellType(int row, int column, char type);
        char getCellType(int row, int column);
        bool isInbound(int row, int column);

        std::vector<GameItem*>* getGameItems();
        std::vector<GamePlayer*>* getGamePlayers();

        // Wanted to use a helperfor the following 2 methods since
        // all that changes is the subtype of the collection.  Issues of casting
        // and object slicing tho.
        bool removeGameItem(Coordinate location);
        bool removeGamePlayer(Coordinate location);

    private:
        std::vector<std::vector <Cell> > grid;
        int height;
        int width;
        Coordinate entryDoor;
        Coordinate exitDoor;
        Coordinate playerPosition;
        std::string name;
        std::vector<GameItem*>* gameItems;
        std::vector<GamePlayer*>* gamePlayers;

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & grid;
            ar & height;
            ar & width;
            ar & entryDoor;
            ar & exitDoor;
            ar & name;
            ar & gameItems;
            ar & gamePlayers;

        }

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
    Notify();
}

inline Coordinate Map::getExitDoorCoordinate() {
    return exitDoor;
}

inline void Map::setExitDoor(Coordinate exitDoor) {
    this->exitDoor = exitDoor;
    Notify();
}

inline bool Map::isFloor(int row, int column) {
    return grid.at(row).at(column).getType() == Cell::TYPE_FLOOR;
}

inline bool Map::isWall(int row, int column) {
    return grid.at(row).at(column).getType() == Cell::TYPE_WALL;
}

inline bool Map::isEntryDoor(int row, int column) {
    return grid.at(row).at(column).getType() == Cell::TYPE_DOOR_ENTRY;
}

inline bool Map::isExitDoor(int row, int column) {
    return grid.at(row).at(column).getType() == Cell::TYPE_DOOR_EXIT;
}

inline bool Map::isDoor(int row, int column) {

    return grid.at(row).at(column).getType() == Cell::TYPE_DOOR_ENTRY
        || grid.at(row).at(column).getType() == Cell::TYPE_DOOR_EXIT;
}

inline bool Map::isInbound(int row, int column) {
    return row >= 0 && row < height && column >= 0 && column < width;

}

inline void Map::setCellType(int row, int column, char type) {
    grid.at(row).at(column).setType(type);
    Notify();
}

inline char Map::getCellType(int row, int column) {
    return grid.at(row).at(column).getType();
}


inline void Map::setName(string name) {
    this->name = name;
}

inline string Map::getName() {
    return this->name;
}

inline bool Map::hasPlayer(int row, int column) {
    return grid.at(row).at(column).hasPlayer();
}

inline void Map::setPlayer(int row, int column, bool yes) {
    grid.at(row).at(column).setPlayer(yes);
}

inline bool Map::movePlayer(int row, int column) {

    if (isWall(row, column)) {
        cout << "OUCH! You hit a wall! Please retry" << endl;
        return false;
    }
    if (Cell::OCCUPANT_FRIEND == getOccupant(row, column)) {
        cout << "Stepping on your friend's toes! Please retry" << endl;
        return false;
    }
    if (Cell::OCCUPANT_OPPONENT == getOccupant(row, column)) {
        cout << "You wish you could crush him hein?! Please retry" << endl;
        return false;
    }
    if (!isPlayerAdjacent(row, column)
        && (-1 != this->playerPosition.column && -1 != this->playerPosition.row)) {
        cout << "Trying to teleport my friend?! Please retry" << endl;
        return false;
    }

    if (-1 != this->playerPosition.column && -1 != this->playerPosition.row){
       grid[playerPosition.row][playerPosition.column].setPlayer(false);
    }
    playerPosition.row = row;
    playerPosition.column = column;
    grid.at(row).at(column).setPlayer(true);
    this->render(); // TODO change to notify

    return true;
}

inline bool Map::isPlayerAdjacent(int row, int column) {
    int currentRow = playerPosition.row;
    int currentColumn = playerPosition.column;

    return (row == currentRow + 1 && column == currentColumn)
            || (row == currentRow - 1 && column == currentColumn)
            || (row == currentRow && column == currentColumn + 1)
            || (row == currentRow - 1 && column == currentColumn - 1);
}

inline std::vector<GameItem*>* Map::getGameItems() {
    return this->gameItems;
}
inline std::vector<GamePlayer*>* Map::getGamePlayers() {
    return this->gamePlayers;
}


#pragma once
#include <iostream>
#include "Cell.h"

struct Coordinate {
    int row;
    int column;

};

class Map {
    public:

        Map(int h, int w, Coordinate entry, Coordinate exit);
        Map(int h, int w);
        Map();
        ~Map();


        int getHeight();
        int getWidth();
        Cell** getGrid();
        Coordinate getEntryDoor();
        void setEntryDoor(Coordinate entryDoor);
        Coordinate* getExitDoors();
        void setExitDoors(Coordinate* exitDoors);
        void setExitDoor(Coordinate* exitDoors);
        int getNbExitDoors();

        void initDoors(Coordinate entryDoor, Coordinate exitDoor);


        void destroyMap();
        bool isDoor(int row, int column);
        bool isEntryDoor(int row, int column);
        bool isExitDoor(int row, int column);
        bool isWall(int row, int column);
        bool isFloor(int row, int column);
        bool isOccupied(int row, int column);
        bool isInbound(int row, int column);

        void setCellType(int row, int column, char type);
        void fillCell(int row, int column, char occupant);
        char getOccupant(int row, int column);
        void render();
        bool validate();


        Cell **grid;
    private:
        int height;
        int width;
        Coordinate entryDoor;
        int nbExitDoors;
        Coordinate* exitDoors;


        friend std::ostream& operator<<(std::ostream &strm, const Map &map);

};


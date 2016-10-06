#pragma once
#include <iostream>
#include "Cell.h"

struct Coordinate {
    int row;
    int column;

};

class Map {
    public:

        Map(int h, int w);
        Map();
        ~Map();


        int getHeight();
        Map& setHeight(int height);
        int getWidth();
        Map& setWidth(int width);
        Cell** getGrid();
        Coordinate getEntryDoor();
        void setEntryDoor(Coordinate entryDoor);
        Coordinate* getExitDoors();
        void setExitDoors(Coordinate* exitDoors);
        int getNbExitDoors();

        void destroyMap();
        bool isDoor(int row, int column);
        bool isEntryDoor(int row, int column);
        bool isWall(int row, int column);
        bool isFloor(int row, int column);

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



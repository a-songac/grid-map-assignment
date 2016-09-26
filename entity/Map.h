#pragma once
#include <iostream>
#include "Cell.h"

class Map {
    public:

        Map(int h, int w);
        Map();

        int getHeight();
        Map& setHeight(int height);
        int getWidth();
        Map& setWidth(int width);
        Cell** getGrid();

        void destroyMap();

        Cell **grid;
    private:
        int height;
        int width;

        friend std::ostream& operator<<(std::ostream &strm, const Map &map);

};

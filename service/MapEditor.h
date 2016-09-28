#pragma once
#include <iostream>

#include "../entity/Map.h"

using namespace std;

class MapEditor {
    public:

        static const string ADD_WALL_PROMPT;
        static const string WALL_LOCATION_PROMPT;
        static const string CELL_LOCATION_REGEX;

        MapEditor(Map* map);

        void buildMapContent();
        void addWall();

    private:
        Map* map;


};

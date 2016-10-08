#pragma once

#include "../entity/Map.h"

using namespace std;

class MapEditor {
    public:

        static const string ADD_WALL_PROMPT;
        static const string ADD_OCCUPANT_PROMPT;
        static const string CELL_LOCATION_REGEX;

        MapEditor();
        MapEditor(Map* map);

        Map* createMap();

        void buildMapContent();
        void addWall();
        void addOccupant();
        Coordinate defineDoor(string message, Map* map, string defaultLocation);
        Coordinate promptForMapLocation(string message, string defaultLocation);
        char setOccupantOnMap();

    private:
        Map* map;


};

int readMapDimension(string message, int defaultValue, int min, int max);


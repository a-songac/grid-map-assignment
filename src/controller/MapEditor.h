/// @file
/// @brief Header file containing class declaration for MapEditor.class
/// @details  No specific game rule enforced by the class
/// Class that encapsulates all the logic to communicate with the user to create a map
/// No specific library used.

#pragma once

#include "../entity/Map.h"

using namespace std;

/// Class that implements the editor of the map
class MapEditor {
    public:
        MapEditor();
        MapEditor(Map* map);

        void buildMap();
        Map* createMap();

    private:
        void addWall();
        void addOccupant();
        Coordinate defineDoor(string message, Map* map, string defaultLocation);
        Coordinate promptForMapLocation(string message, string defaultLocation);
        char setOccupantOnMap();
        Map* map;
};

int readMapDimension(string message, int defaultValue, int min, int max);


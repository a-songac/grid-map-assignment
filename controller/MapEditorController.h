/// @file
/// @brief Header file containing class declaration for MapEditor.class
/// @details  1. Game Rules: The code allows the player to create a map and populate it with the elements
/// allowed by the game rules: friend character, enemy character, chest, door or wall. \n\n
/// 2. Design: Controller class from the MVC pattern. It encapsulates all the logic to communicate with the user to create a map \n\n
/// 3. Libraries: The implementation uses the string and regex libraries in order to parse the user input.
/// The regex allows to validate the user provided a valid input

#pragma once

#include "../entity/Map.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


using namespace std;

/// Class that implements the editor of the map
class MapEditorController {
    public:
        MapEditorController();
        MapEditorController(Map* map);

        void buildMap();
        void createMap();
        void addWall();
        void addOccupant();
        Map* loadMap();
        void editMap(Map* map);
        void setMap(Map* map);
        Map* getMap();

    private:

        Coordinate defineDoor(string message, Map* map, string defaultLocation);
        Coordinate promptForMapLocation(string message, string defaultLocation);
        char setOccupantOnMap();
        Map* map;

        friend class boost::serialization::access;

        template<typename Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & map;

        }
};

int readMapDimension(string message, int defaultValue, int min, int max);

inline void MapEditorController::setMap(Map* map){
    this->map = map;
}

inline Map* MapEditorController::getMap(){
    return map;
}

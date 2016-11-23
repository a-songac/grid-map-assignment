#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <fstream>

#include "../entity/Map.h"
#include "../view/MapElementsView.h"
#include "../entity/Cell.h"
#include "MapEditorController.h"
#include "CharacterInteractionHelper.h"
#include "ItemInteractionHelper.h"
#include "../service/MapValidator.h"
#include "../utils/IOUtils.h"
#include "../entity/repo/MapRepository.h"
#include "MapInteractionHelper.h"


using namespace std;
using namespace boost::archive;

const string ADD_WALL_PROMPT = "Do you want to add or remove a wall?[Y/n] ";
const string ADD_OCCUPANT_PROMPT = "Do you want to add or remove an occupant?[Y/n] ";
const string CELL_LOCATION_REGEX = "^([a-zA-Z]+)([0-9]+)$";


MapEditorController::MapEditorController(Map* map) {
    this->map = map;
}

MapEditorController::MapEditorController() {
    //this->map = nullptr;
}

void MapEditorController::buildMap() {
    cout << "It is now time to build the walls of your map..." << endl << endl;
    if (readYesNoInput(ADD_WALL_PROMPT, true))
        addWall();
    cout << "It is now time to add occupants on your map..." << endl << endl;
    if (readYesNoInput(ADD_OCCUPANT_PROMPT, true))
        addOccupant();
}

void MapEditorController::createMap() {

    bool error = false;
    int height, width, exitDefaultRow;
    stringstream ss;
    Coordinate entryDoor , exitDoor;
    string exitDefaultCoordinate, exitDoorMessage;
    char exitDefaultColumn;


    cout << "Let's create a map!" << endl;
    height = readMapDimension("Please provide the height of your map (between 2 and 15)[7]:", 7, 2, 15);
    width = readMapDimension("Please provide the width of your map (between 2 and 15)[7]:", 7, 2, 15);

    Map* map = new Map(height, width);
    MapView* mapView = new MapView(map);
    MapElementsView* mapElementsView = new MapElementsView(map);
     #ifdef DEBUG
        logInfo("Repository", "loadMap", "Attaching views to created map");
    #endif // DEBUG

    this->map = map;
    cout << "Your map will look like this: " << endl;
    map->render();

    cout << "Let's complete the map creation by adding the entry and exit doors." << endl;
    cout << "Note that doors have to be on the edges of the map." << endl;
    entryDoor = defineDoor("Please provide the location of the entry door[A1]:", map, "A1");

    exitDefaultColumn = (char) 'A' + map->getWidth()-1;
    exitDefaultRow = map->getHeight();
    ss << exitDefaultColumn << exitDefaultRow;
    exitDefaultCoordinate = ss.str();
    ss.str("");
    ss << "Please provide the location of the exit door[" << exitDefaultCoordinate << "]:";
    exitDoorMessage = ss.str();
    do {
        error = false;
        exitDoor = defineDoor(exitDoorMessage, map, exitDefaultCoordinate);

        if (entryDoor.column == exitDoor.column && entryDoor.row == exitDoor.row) {
            cout << "Error, entry door and exit door cannot be on the same cell, please choose another location for the exit door." << endl;
            error = true;
        }
    } while(error);

    map->initDoors(entryDoor, exitDoor);

    cout << "Here is the map created:" << endl << endl;
    map->render();


    this->buildMap();

    cout << "\n\nHere is the map created:" << endl << endl;
    map->render();

    bool save = readYesNoInput("Would you like to save this map?[Y/n] ", true);

    if(save){
        if(map->validate()){
            string filename = readStringInput("Enter a Name for the File: ", "userMap");
            map->setName(filename);
            MapRepository::instance()->save(filename, map);
            cout << "Map successfully saved." << endl;
        }
        else{
            cout << "Invalid Map, Please Try Again. (Map not Saved)" << endl;
        }
    } else {
        delete map;
    }

}


void MapEditorController::addWall() {

    bool addWall = true;
    string column, row;
    MapValidator validator(map);
    Coordinate location;

    while (addWall) {

        bool error;
        do {
            error = false;
            location = MapInteractionHelper::readMapLocation(map, "On which cell do you want to add or remove the wall?[A1]:", "A1");

            if (map->isDoor(location.row, location.column)) {
                cout << "This is a door, please retry" << endl;
                error = true;
            }
            else {

                if (map->isWall(location.row, location.column)) {
                    map->setCellType(location.row, location.column, Cell::TYPE_FLOOR);
                }
                else {
                    map->setCellType(location.row, location.column, Cell::TYPE_WALL);
                    error = !validator.validateMap();
                    if (error) {
                        cout << "Error, adding a wall at this position makes the map invalid, please add a wall elsewhere" << endl;
                        map->setCellType(location.row, location.column, Cell::TYPE_FLOOR);
                    }
                }
//                map->render();
            }
        } while(error);

        addWall = readYesNoInput(ADD_WALL_PROMPT, true);
    }
}

void MapEditorController::addOccupant() {
    bool addOccupant = true;
    string column, row;
    Coordinate location;

    while (addOccupant) {

        bool error;
        do {
            error = false;
            location = MapInteractionHelper::readMapLocation(map, "On which cell do you want to add or remove an item?[A1]:", "A1");

            if (map->isWall(location.row, location.column)) {
                cout << "This is a wall, please retry" << endl;
                error = true;
            }
            else if (map->isDoor(location.row, location.column)) {
                cout << "This is a door, please retry" << endl;
                error = true;
            }
            else {

                if (map->isOccupied(location.row, location.column)) {

                    if (readYesNoInput("You confirm to remove the occupant of this cell[Y/n]", true)) {

                        char oldItem = map->getOccupant(location.row, location.column);
                        switch (oldItem) {
                            case Cell::OCCUPANT_CHEST:
                                map->removeGameItem(location);
                                break;
                            case Cell::OCCUPANT_FRIEND:
                            case Cell::OCCUPANT_OPPONENT:
                                map->removeGamePlayer(location);
                                break;
                        }
                        map->fillCell(location.row, location.column, Cell::OCCUPANT_EMPTY);
                        map->setOriginalOccupant(location, Cell::OCCUPANT_EMPTY);
                    }
                }
                else {
                    try {
                        char occupant = setOccupantOnMap(location);
                        map->fillCell(location.row, location.column, occupant);
                        map->setOriginalOccupant(
                                location,
                                occupant);

                    } catch (std::runtime_error& e) {
                        cerr << e.what() << endl;
                        error = true;
                    }

                }
//                map->render();
            }
        } while(error);

        addOccupant = readYesNoInput(ADD_OCCUPANT_PROMPT, true);
    }

}


Coordinate MapEditorController::defineDoor(string message, Map* map, string defaultLocation) {

    bool error = false;
    string row, column;
    Coordinate location;

    do {
        error = false;
        location = MapInteractionHelper::readMapLocation(map, message, defaultLocation);

        if (!(location.row == 0 || location.row + 1 == map->getHeight() ||
                location.column == 0 || location.column + 1 == map->getWidth() )) {
                cout << "A door has to be on the edge of a map." << endl;
            error = true;
        }

    } while (error);

    return location;
}


char MapEditorController::setOccupantOnMap(Coordinate location) {

    int choice;

    cout << "Please choose occupant type based on the following:" << endl;
    cout << "Enemy: 1" << endl;
    cout << "Friend: 2" << endl;
    cout << "Chest: 3" << endl;
    choice = readIntegerInput("Your choice[1]:", 1);
    while (choice != 1 && choice != 2 && choice != 3) {
        cout << "This is not a choice, please retry" << endl;
        choice = readIntegerInput("Your choice[1]:", 1);
    }

    switch (choice) {
        case 1:
            this->addGamePlayer(location, Cell::OCCUPANT_OPPONENT);
            return Cell::OCCUPANT_OPPONENT;
        case 2:
            this->addGamePlayer(location, Cell::OCCUPANT_FRIEND);
            return Cell::OCCUPANT_FRIEND;
        case 3:
            this->addGameItem(location);
            return Cell::OCCUPANT_CHEST;
    }
    return Cell::OCCUPANT_OPPONENT;
}

void MapEditorController::addGamePlayer(Coordinate location, char occupantType) {

    Coordinate* playerLocation = new Coordinate(location.row, location.column);

    Character* character;
    character = CharacterInteractionHelper::selectCharacter();
    if (nullptr == character) {
        throw new std::runtime_error("Could not load character");
    }
    GamePlayer* gamePlayer = new GamePlayer(character->getName(), playerLocation, occupantType);
    map->getGamePlayers()->push_back(gamePlayer);

}

void MapEditorController::addGameItem(Coordinate location) {
    Coordinate* itemLocation = new Coordinate(location.row, location.column);
    Item* item;
    item = ItemInteractionHelper::selectItem();
    if (nullptr == item) {
        throw new std::runtime_error("Could not load item");
    }
    GameItem* gameItem = new GameItem(item->getName(), itemLocation);
    map->getGameItems()->push_back(gameItem);

}




int readMapDimension(string message, int defaultValue, int min, int max) {

    bool error = false;
    int result;

    do {
        error = false;
        result = readIntegerInput(message, defaultValue);
        if (result > max || result < min) {
            cout << "Out of range , please retry." << endl;
            error = true;
        }
    } while(error);
    return result;
}



void MapEditorController::editMap(Map *map) {
    if(map->validate()){
        this->setMap(map);

        bool done = false;

        do{
            map->render();

            cout << "What changes do you want to make to this map?:" << endl;
            cout << "1. Add/Remove Wall" << endl;
            cout << "2. Add/Remove Occupant" << endl;
            cout << "3. Save and Exit" << endl;
            cout << "4. Exit without saving" << endl;

            int choice = readIntegerInputWithRange("Your choice[1]: ", 1, 1, 4);

            switch (choice) {
                case 1:
                    this->addWall();
                    break;
                case 2:
                    this->addOccupant();
                    break;
                case 3:
                    done = true;
                    if(map->validate()){
                        MapRepository::instance()->save(map->getName(), map);
                        cout << "Map successfully saved." << endl;
                    }
                    else{
                        cout << "Invalid Map. (Map not Saved)" << endl;
                    }

                    break;
                case 4:
                    done = readYesNoInput("Do you really want to leave without saving your changes?[Y/n]: ", true);
                    if (done) {

                        MapRepository::instance()->clearEntity(map->getName());

                    }
                    break;
            }

        }while(!done);

    }
    else{
        cout << "Invalid Map." << endl;
    }
}



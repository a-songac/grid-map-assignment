#include <iostream>
#include <regex>
#include <sstream>
#include <string>

#include "../entity/Map.h"
#include "../entity/Cell.h"
#include "MapEditorController.h"
#include "../service/MapValidator.h"
#include "../utils/IOUtils.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <fstream>
#include "../entity/repo/MapRepository.h"

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
    addWall();
    cout << "It is now time to add occupants on your map..." << endl << endl;
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
 
//new
    this->buildMap();
    
    bool save = readYesNoInput("Would you like to save this map? (Y/n)", true);
    
    if(save){
        if(map->validate()){
            string filename = readStringInput("Enter a Name for the File: ", "userMap");
            map->setName(filename);
            MapRepository::instance()->save(map);
            cout << "Map successfully saved." << endl;
        }
        else{
            cout << "Invalid Map, Please Try Again. (Map not Saved)" << endl;
        }
    }

}


void MapEditorController::addWall() {

    bool addWall = false;
    string column, row;
    MapValidator validator(map);
    Coordinate location;


    addWall = readYesNoInput(ADD_WALL_PROMPT, true);

    while (addWall) {

        bool error;
        do {
            error = false;
            location = promptForMapLocation("On which cell do you want to add or remove the wall?[A1]:", "A1");

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
                map->render();
            }
        } while(error);

        addWall = readYesNoInput(ADD_WALL_PROMPT, true);
    }
}

void MapEditorController::addOccupant() {
    bool addOccupant = false;
    string column, row;
    Coordinate location;


    addOccupant = readYesNoInput(ADD_OCCUPANT_PROMPT, true);

    while (addOccupant) {

        bool error;
        do {
            error = false;
            location = promptForMapLocation("On which cell do you want to add or remove an item?[A1]:", "A1");

            if (map->isWall(location.row, location.column)) {
                cout << "This is a wall, please retry" << endl;
                error = true;
            }
            else if (map->isDoor(location.row, location.column)) {
                cout << "This is a door, please retry" << endl;
                error = true;
            }
            else {

                if (map->isOccupied(location.row, location.column)
                        && readYesNoInput("This cell is occupied, do you simply want to remove its occupant?[Y/n]", true)) {

                    map->fillCell(location.row, location.column, ' ');
                }
                else {

                    map->fillCell(location.row, location.column, setOccupantOnMap());

                }
                map->render();
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
        location = promptForMapLocation(message, defaultLocation);

        if (!(location.row == 0 || location.row + 1 == map->getHeight() ||
                location.column == 0 || location.column + 1 == map->getWidth() )) {
                cout << "A door has to be on the edge of a map." << endl;
            error = true;
        }

    } while (error);

    return location;
}



Coordinate MapEditorController::promptForMapLocation(string message, string defaultLocation) {

    bool error = false;
    string row, column;
    int rowIndex, columnIndex;

    do {
        error = false;
        string cellLocation = readStringInput(message, defaultLocation);
        regex regex (CELL_LOCATION_REGEX);
        smatch match;

        if (regex_search(cellLocation, match, regex)) {
            row = match.str(2);
            column = match.str(1);
            rowIndex = stoi(row, nullptr) - 1;
            columnIndex = column.at(0) - 'A'; //TODO Handle over 26 case
            if (columnIndex + 'A' >= 97 && columnIndex + 'A' <= 122) // if lowercase was given
                columnIndex -= 32;

            if (!map->isInbound(rowIndex, columnIndex)) {
                cout << "Out of range, please retry" << endl;
                error = true;
            }

        } else {
            error = true;
            cout << "Invalid input, please retry" << endl;
        }

    } while (error);

    Coordinate location = {rowIndex, columnIndex};
    return location;

}


char MapEditorController::setOccupantOnMap() {

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
            return Cell::OCCUPANT_OPPONENT;
        case 2:
            return Cell::OCCUPANT_FRIEND;
        case 3:
            return Cell::OCCUPANT_CHEST;
    }
    return Cell::OCCUPANT_OPPONENT;
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


Map* MapEditorController::loadMap(){
    //Load map for editing
    cout << "************** Map Editor **************" << endl << endl;
    
    Map* map;
    string filename;
    list<MapProxy*> mp = *(MapRepository::instance()->listAll());
    if(mp.empty()){
        cout << "No maps currently saved. Redirecting to editor menu." << endl;
    }
    else{
        int count = 0;
        for (std::list<MapProxy*>::const_iterator iterator = mp.begin(), end = mp.end(); iterator != end; ++iterator) {
            count++;
            cout << count << ":" <<(*iterator)->getFileName() << endl;
        }
        
        int index = readIntegerInput("Please enter the index of your chosen map[1]: ", 1);
        while (index < 1 || index > mp.size()) {
            index = readIntegerInput("Invalid input, please retry:[1]", 1);
        }
        std::list<MapProxy*>::iterator it = mp.begin();
        std::advance(it, index-1);
        map = (*it)->getMap();
    }
    
    if (map == nullptr) {
        cout << "Could not load map! Redirecting to editor menu." << endl;
    }
    
    return map;
}

void MapEditorController::editMap(Map *map){
    if(map->validate()){
        this->setMap(map);
        
        bool done = false;
        
        do{
            map->render();
            
            cout << "What changes do you want to make to this map?:" << endl;
            cout << "Add/Remove Wall: 1" << endl;
            cout << "Add Occupant: 2" << endl;
            
            int choice = readIntegerInput("Your choice[1]:", 1);
            while (choice != 1 && choice != 2) {
                cout << "This is not a choice, please retry" << endl;
                choice = readIntegerInput("Your choice[1]:", 1);
            }
            
            switch (choice) {
                case 1:
                    this->addWall();
                    break;
                case 2:
                    this->addOccupant();
                    break;
            }
            
            done = !(readYesNoInput("Do you wish to further edit this map?(Y/n)", true));
        }while(done!=true);
        
        
        bool saveEdit = readYesNoInput("Do you wish to save your changes?(Y/n)", true);
        if(saveEdit){
            if(map->validate()){
                MapRepository::instance()->save(map);
                cout << "Map successfully saved." << endl;
            }
            else{
                cout << "Invalid Map. (Map not Saved)" << endl;
            }
            
        }
        
    }
    else{
        cout << "Invalid Map." << endl;
    }
}



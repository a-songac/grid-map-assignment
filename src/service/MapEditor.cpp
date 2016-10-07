#include <iostream>
#include <regex>
#include <sstream>
#include <string>

#include "../entity/Map.h"
#include "../entity/Cell.h"
#include "MapEditor.h"
#include "MapRenderer.h"
#include "MapValidator.h"
#include "../utils/IOUtils.h"

using namespace std;

const string MapEditor::ADD_WALL_PROMPT = "Do you want to add or remove a wall?[Y/n] ";
const string MapEditor::WALL_LOCATION_PROMPT = "On which cell do you want to add or remove the wall?[A1] ";
const string MapEditor::CELL_LOCATION_REGEX = "^([A-Z]+)([0-9]+)$";


MapEditor::MapEditor(Map* map) {
    this->map = map;
}

MapEditor::MapEditor() {
    this->map = nullptr;
}

Map* MapEditor::createMap() {

    bool error = false;
    int height, width, entryCell, exitCell, entrySide, exitSide, maxi;
    stringstream ss;
    Coordinate entryDoor , exitDoor;

    cout << "Let's create a map!" << endl;
    height = readIntegerInput("Please provide the height of your map (between 2 and 15)[7]:", 7);
    if (height > 15 || height < 2) {
        cout << "Invalid input, 7 chosen." << endl;
        height = 7;
    }
    width = readIntegerInput("Please provide the width of your map (between 2 and 15)[7]:", 7);
    if (width > 15 || width < 2) {
        cout << "Invalid input, 7 chosen." << endl;
        width = 7;
    }

     Map* map = new Map(height, width);
    this->map = map;

    cout << "Your map will look like this: " << endl;
    map->render();
    cout << "Let's complete the map creation by adding the entry and exit doors." << endl;


    entrySide = readIntegerInput("Please provide the side on which the entry door is located; North (1), South (2), East(3) or West(4)[1]:", 1);
    if (entrySide > 4 || entrySide < 1) {
        cout << "Invalid input, 1 chosen." << endl;
        entrySide = 1;
    }
    cardinalChoiceConfirmation(entrySide);
    maxi = entrySide == 1 || entrySide == 2 ? width : height;
    ss << "Please provide the cell on which the entry door is located; between 1 and " << maxi << " from top if you chose East or West, or from left if you chose North or South[1]:";
    entryCell = readIntegerInput(ss.str(), 1);
    ss.str("");
    if (entryCell > maxi || entryCell < 1) {
        cout << "Invalid input, 1 chosen." << endl;
        entryCell = 1;
    }

    do {
        error = false;
        exitSide = readIntegerInput("Please provide the side on which the exit door is located; North (1), South (2), East(3) or West(4)[3]:", 3);
        if (exitSide > 4 || exitSide < 1) {
            cout << "Invalid input, 3 chosen." << endl;
            exitSide = 3;
        }
        cardinalChoiceConfirmation(exitSide);
        maxi = exitSide == 1 || exitSide == 2 ? width : height;

        ss.str("");
        ss << "Please provide the cell on which the exit door is located; between 1 and " << maxi << " from top if you chose East or West, or from left if you chose North or South[" << maxi << "]:";
        exitCell = readIntegerInput(ss.str(), maxi);
        if (exitCell > maxi || entryCell < 1) {
            cout << "Invalid input, " << maxi << " chosen." << endl;
            entryCell = maxi;
        }

        entryDoor = computeDoorCoordinate(entrySide, entryCell-1, width, height);
        exitDoor = computeDoorCoordinate(exitSide, exitCell-1, width, height);

        if (entryDoor.column == exitDoor.column && entryDoor.row == exitDoor.row) {
            cout << "Error, entry door and exit door cannot be on the same cell, please choose another location for the exit door." << endl;
            error = true;
        }
    } while(error);


    map->initDoors(entryDoor, exitDoor);

    cout << "Here the map created:" << endl;
    map->render();

    return map;

}


void MapEditor::buildMapContent() {

    cout << "It is now time to build the content of your map..." << endl << endl;


    this->addWall();

}

void MapEditor::addWall() {

    bool addWall = false;
    string column, row;
    int columnIndex, rowIndex;
    MapValidator validator(map);


    addWall = readYesNoInput(MapEditor::ADD_WALL_PROMPT, true);

    while (addWall) {

        bool error;
        do {
            error = false;
            string cellLocation = readStringInput(MapEditor::WALL_LOCATION_PROMPT, "A1");
            regex regex (MapEditor::CELL_LOCATION_REGEX);
            smatch match;
            if (regex_search(cellLocation, match, regex)) {
                row = match.str(2);
                column = match.str(1);

                rowIndex = stoi(row, nullptr) - 1;
                columnIndex = column.at(0) - 'A'; //TODO Handle over 26 case

                if (rowIndex >= map->getHeight()) {
                    cout << "Out of range, please retry" << endl;
                    error = true;
                }
                else if (columnIndex >= map->getWidth()) {
                    cout << "Out of range, please retry" << endl;
                    error = true;
                }
                else if (map->isDoor(rowIndex, columnIndex)) {
                    cout << "This is a door, please retry" << endl;
                    error = true;
                }
                else {

                    Cell *cell = &(map->getGrid()[rowIndex][columnIndex]);

                    if (cell->getType() == Cell::WALL)
                        cell->setType(Cell::FLOOR);
                    else {
                        cell->setType(Cell::WALL);
                        error = !validator.validateMap();
                        if (error) {
                            cout << "Error, adding a wall at this position makes the map invalid, please add a wall elsewhere" << endl;
                            cell->setType(Cell::FLOOR);
                        }
                    }

                    MapRenderer::renderMap(map);
                }
            }
            else {
                cout << "Erroneous input, please retry" << endl;
                error = true;
            }

        } while(error);

        addWall = readYesNoInput(MapEditor::ADD_WALL_PROMPT, true);
    }


}


Coordinate computeDoorCoordinate(int cardinal, int location, int width, int height) {
    Coordinate coor = {0,0};

    switch (cardinal) {
        case 1:
            coor.row = 0;
            coor.column = location;
            break;
        case 2:
            coor.row = height-1;
            coor.column = location;
            break;
        case 3:
            coor.row = location;
            coor.column = width-1;
            break;
        case 4:
            coor.row = location;
            coor.column = 0;
            break;
    }
        return coor;
}

void cardinalChoiceConfirmation(int choice) {
    switch (choice) {
        case 1:
            cout << "You chose North" << endl;
            break;
        case 2:
            cout << "You chose South" << endl;
            break;
        case 3:
            cout << "You chose East" << endl;
            break;
        case 4:
            cout << "You chose West" << endl;
            break;
    }

}



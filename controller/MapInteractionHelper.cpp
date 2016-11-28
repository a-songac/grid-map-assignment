#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

#include "../utils/IOUtils.h"
#include "MapInteractionHelper.h"
#include "../entity/repo/MapRepository.h"

using namespace std;

const string CELL_LOCATION_REGEX = "^([a-zA-Z]{1})([0-9]+)$";


Coordinate MapInteractionHelper::readMapLocation(Map* map, string message, string defaultLocation) {

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


string MapInteractionHelper::readMapLocationWhileInGame(Map* map, string message, string defaultLocation) {

    bool error = false;
    string row, column;
    int rowIndex, columnIndex;
	string input;
    do {
        error = false;
        input = readStringInput(message, defaultLocation);
        regex regex (CELL_LOCATION_REGEX);
        smatch match;

        if (regex_search(input, match, regex)) {
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

        } else if (input == "bp") {
            return input;
        } else if (input == "q") {
            return input;
        } else if (input == "i") {
            return input;
        } else if (input == "a") {
            return input;
        } else if (input == "s") {
            return input;
        } else if (input == "f") {
            return input;
        }
        else {
            error = true;
            cout << "Invalid input, please retry" << endl;
        }

    } while (error);

//    Coordinate location = {rowIndex, columnIndex};
    return input;

}



Coordinate MapInteractionHelper::convertToCoordinate(Map* map, string locationStr) {

    regex regex (CELL_LOCATION_REGEX);
    smatch match;
    int rowIndex, columnIndex;
    string row, column;

    if (regex_search(locationStr, match, regex)) {
        row = match.str(2);
        column = match.str(1);
        rowIndex = stoi(row, nullptr) - 1;
        columnIndex = column.at(0) - 'A'; //TODO Handle over 26 case
        if (columnIndex + 'A' >= 97 && columnIndex + 'A' <= 122) // if lowercase was given
            columnIndex -= 32;

        if (!map->isInbound(rowIndex, columnIndex)) {
            throw std::invalid_argument( "Map location out of range" );
        }

    } else {
        throw std::invalid_argument( "Not valid input for map location" );
    }
    Coordinate location = {rowIndex, columnIndex};
    return location;
}

string MapInteractionHelper::coordinateToString(Coordinate* point) {

    stringstream sstream;
    char column = 'A' + point->column;
    int row = point->row+1;
    sstream << "[" << column << row << "] ";
    return sstream.str();

}

string MapInteractionHelper::coordinateToString(Coordinate point) {

    stringstream sstream;
    char column = 'A' + point.column;
    int row = point.row+1;
    sstream << "[" << column << row << "] ";
    return sstream.str();

}

Map* MapInteractionHelper::selectMap() {
     Map* map = nullptr;

    bool confirm = false;
    string filename, name1;
    vector<string>* mapReferences = MapRepository::instance()->listAll();

    if(mapReferences->size() > 0){

        do {
            cout << "Please select a map: " << endl;
            for (size_t i = 0; i < mapReferences->size(); i++) {
                cout << i+1 << ". " << mapReferences->at(i) << endl;
            }
            int index = readIntegerInputWithRange("Your selection[1]: ", 1, 1, mapReferences->size());

            map = MapRepository::instance()->getEntity(index-1);

            if (nullptr == map) {

                cout << "Sorry, could not load map" << endl;
                confirm = true;

            } else {
                map->render();
                confirm = readYesNoInput("You confirm the selection of this map displayed above?[Y/n]: ", true);
            }

        } while (!confirm);

    } else {
        cout << "No maps to be loaded" << endl;
    }
    return map;

}



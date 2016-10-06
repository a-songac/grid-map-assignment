#include <iostream>
#include <regex>
#include <string>

#include "../entity/Map.h"
#include "../entity/Cell.h"
#include "MapEditor.h"
#include "MapRenderer.h"
#include "MapValidator.h"
#include "../utils/IOUtils.h"

using namespace std;

const string MapEditor::ADD_WALL_PROMPT = "Do you want to toggle a cell's type?[Y/n] ";
const string MapEditor::WALL_LOCATION_PROMPT = "On which cell do you want to add the wall?[A1] ";
const string MapEditor::CELL_LOCATION_REGEX = "^([A-Z]+)([0-9]+)$";


MapEditor::MapEditor(Map* map) {
    this->map = map;
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




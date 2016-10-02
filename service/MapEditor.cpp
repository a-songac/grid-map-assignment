#include <iostream>
#include <regex>
#include <string>

#include "../entity/Map.h"
#include "../entity/Cell.h"
#include "MapEditor.h"
#include "MapRenderer.h"
#include "../utils/IOUtils.h"

using namespace std;

const string MapEditor::ADD_WALL_PROMPT = "Do you want to toggle a cell's type?[Y/n] ";
const string MapEditor::WALL_LOCATION_PROMPT = "On which cell do you want to add the wall?[A1] ";
const string MapEditor::CELL_LOCATION_REGEX = "^([A-Z]+)([0-9]+)$";


MapEditor::MapEditor(Map* map) {
    this->map = map;
}

void initialize2DArray(bool** grid, int height, int width) {

    for(int i = 0; i < height; ++i) {
        grid[i] = new bool[width];
        for (int j = 0; j < width; j++) {
            grid[i][j] = false;
        }
    }
}

void reset2DArray(bool** grid, int height, int width) {

    for(int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = false;
        }
    }

}
// TODO How do I properly destroy the array
void destroy2DArray(bool** grid, int height, int width) {

    for(int i = 0; i < height; ++i) {
        delete [] grid[i];
    }
    delete [] grid;

}

void MapEditor::buildMapContent() {

    cout << "It is now time to build the content of your map..." << endl << endl;

    this->addWall();

}

void MapEditor::addWall() {

    bool addWall = false;
    string column, row;
    int columnIndex, rowIndex;

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
                else {

                    Cell *cell = &(map->getGrid()[rowIndex][columnIndex]);

                    if (cell->getType() == Cell::WALL)
                        cell->setType(Cell::FLOOR);
                    else {
                        cell->setType(Cell::WALL);
                        error = !validateMap();
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


bool MapEditor::validateMap() {

    bool invalid = false;

    // TODO TO BE PROVIDED FROM THE MAP
    int entryRow = 0;
    int entryColumn = 0;

    Cell **grid = map->getGrid();


    int height = map->getHeight();
    int width = map->getWidth();

    reachable = new bool*[height];
    visited = new bool*[height];

    initialize2DArray(reachable, height, width);
    initialize2DArray(visited, height, width);

    cout << "Start map validation" << endl;


    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            cout << "Start validation of cell [" << i << "][" <<j <<"]" << endl;


            if (grid[i][j].getType() == Cell::WALL
                || (i==entryRow && j==entryColumn)
                || reachable[i][j] == 1) {
                cout << "Skip; cell is a door or wall or was already tested and set as reachable." << endl;
                continue;
            }

            reset2DArray(visited, height, width);

            if (!backTrack(i, j, entryRow, entryColumn)) {
                invalid = true;
                break;
            }
        }
        if (invalid)
            break;
    }

    //TODO Deallocate reachable and visited arrays
    destroy2DArray(reachable, height, width);

    return !invalid;


}



bool MapEditor::backTrack(int row, int column, int entryRow, int entryColumn) {

    int height = map->getHeight();
    int width = map->getWidth();
    Cell **grid = map->getGrid();

    visited[row][column] = 1;

    if (row == entryRow && column == entryColumn)
        return true;

    // NORTH
    if (inbound(row+1, column, height, width)
            && !visited[row+1][column]
            && grid[row +1][column].getType() != Cell::WALL) {

        if (backTrack(row+1, column, entryRow, entryColumn)) {
            reachable[row][column] = true;
            return true;
        }
    }

    // SOUTH
    if (inbound(row-1, column, height, width)
            && !visited[row-1][column]
            && grid[row -1][column].getType() != Cell::WALL) {

        if (backTrack(row-1, column, entryRow, entryColumn)) {
            reachable[row][column] = true;
            return true;
        }
    }

    // EAST
    if (inbound(row, column+1, height, width)
            && !visited[row][column+1]
            && grid[row][column+1].getType() != Cell::WALL) {

        if (backTrack(row, column+1, entryRow, entryColumn)) {
            reachable[row][column] = true;
            return true;
        }
    }

    // WEST
    if (inbound(row, column-1, height, width)
            && !visited[row][column-1]
            && grid[row][column-1].getType() != Cell::WALL) {

        if (backTrack(row, column-1, entryRow, entryColumn)) {
            reachable[row][column] = true;
            return true;
        }
    }
    return false;
}

bool MapEditor::inbound(int i, int j, int height, int width) {

    return i >= 0 && j >= 00 && i < height && j < width;

}



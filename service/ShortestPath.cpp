#include "ShortestPath.h"

#include "../utils/ArrayUtils.h"
#include "../utils/LogUtils.h"
#include "../controller/MapInteractionHelper.h"

using namespace std;

ShortestPath::ShortestPath(Map* map)
{
    this->map = map;

    visited = new bool*[map->getHeight()];
    initialize2DArray(visited, map->getHeight(), map->getWidth());
    this->_currentPath = new vector<Coordinate>();
    this->_shortestPath = new vector<Coordinate>();

}

ShortestPath::~ShortestPath()
{
    destroy2DArray(visited, map->getHeight(), map->getWidth());
    delete this->_currentPath;
    delete this->_shortestPath;
}



vector<Coordinate> ShortestPath::computeShortestPath(Coordinate start , Coordinate destination, bool considerPlayers) {
    reset2DArray(visited, map->getHeight(), map->getWidth());
    *(this->_currentPath) = vector<Coordinate>();
    *(this->_shortestPath) = vector<Coordinate>();
    this->backTrack(start.row, start.column, destination.row, destination.column,  considerPlayers);
    return *(this->_shortestPath);
}


void ShortestPath::backTrack(int row, int column, int destinationRow, int destinationColumn, bool considerPlayers) {

    Coordinate c = {row, column};
    this->_currentPath->push_back(c);

    // if the current path is already longer than the actual best, go back
    if (0 != this->_shortestPath->size()
                && this->_currentPath->size() >= this->_shortestPath->size()) {
        this->_currentPath->pop_back();
        return;
    }

    #ifdef DEBUG_PATH
        logInfo("ShortestPath", "backTrack", "Visiting: " + MapInteractionHelper::coordinateToString(c));
    #endif // DEBUG_PATH

    // check if has arrived at destination
    if (row == destinationRow && column == destinationColumn) {
        #ifdef DEBUG_PATH
            cout << "Found a path: " << endl;
            cout << "    length: " << _currentPath->size() << endl;
            cout << "    path: ";
            for (size_t i = 0; i < _currentPath->size(); i++) {
                cout << MapInteractionHelper::coordinateToString(_currentPath->at(i));
            }
        cout << endl << endl;
        #endif

        if (0 == this->_shortestPath->size()
                || this->_currentPath->size() < this->_shortestPath->size()) {

            #ifdef DEBUG_PATH
                logInfo("ShortestPath", "backTrack", "The found path is shorter than current best, become the current best");
            #endif // DEBUG_PATH

            *(this->_shortestPath) = *(this->_currentPath);
        }

        this->_currentPath->pop_back();
        return;
    }


    // continue on your path

    this->visited[row][column] = true;
    // NORTH
    if (map->isInbound(row+1, column)
            && !visited[row+1][column]
            && !map->isWall(row+1, column)
            && (!considerPlayers || !map->isOccupiedByCharacter(row+1, column))) {

        backTrack(row+1, column, destinationRow, destinationColumn, considerPlayers);

    }

    // SOUTH
    if (map->isInbound(row-1, column)
            && !visited[row-1][column]
            && !map->isWall(row-1, column)
            && (!considerPlayers || !map->isOccupiedByCharacter(row-1, column))) {

        backTrack(row-1, column, destinationRow, destinationColumn, considerPlayers);
    }

    // EAST
    if (map->isInbound(row, column+1)
            && !visited[row][column+1]
            &&!map->isWall(row, column+1)
            && (!considerPlayers || !map->isOccupiedByCharacter(row, column+1))) {

        backTrack(row, column+1, destinationRow, destinationColumn, considerPlayers);
    }

    // WEST
    if (map->isInbound(row, column-1)
            && !visited[row][column-1]
            && !map->isWall(row, column-1)
            && (!considerPlayers || !map->isOccupiedByCharacter(row, column-1))) {

        backTrack(row, column-1, destinationRow, destinationColumn, considerPlayers);
    }

    this->visited[row][column] = false;
    this->_currentPath->pop_back();
}

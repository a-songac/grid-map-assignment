#include "CombatService.h"
#include "ShortestPath.h"

bool CombatService::isAdjacent(Coordinate origin, Coordinate destination) {

    return (destination.row == origin.row + 1 && destination.column == origin.column)
            || (destination.row == origin.row - 1 && destination.column == origin.column)
            || (destination.row == origin.row && destination.column == origin.column + 1)
            || (destination.row == origin.row && destination.column == origin.column - 1);

}


bool CombatService::canRangeAttack(Coordinate origin, Coordinate destination, int range, Map* gameMap) {
    ShortestPath shortestPath(gameMap);
    vector<Coordinate> pathToUser;
    pathToUser = shortestPath.computeShortestPath(origin, destination, false);

    return pathToUser.size() > 1 && (pathToUser.size() - 1) <= range;

}
